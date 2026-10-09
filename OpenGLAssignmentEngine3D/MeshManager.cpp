#include "pch.h"
#include "MeshManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void MeshManager::init()
{
	// 사각형 버퍼세팅
	float vertices[]
	{
		 0.5f,  0.5f, // 우상단
		 0.5f, -0.5f, // 우하단
		-0.5f, -0.5f, // 좌하단
		-0.5f,  0.5f  // 좌상단
	};

	uint32_t indices[]
	{
		0, 3, 1, // 첫 번째 삼각형
		1, 3, 2  // 두 번째 삼각형
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadEBO);

	glBindVertexArray(quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 삼각형 버퍼세팅
	float triVertices[]
	{
		 0.0f,  0.5f, // 상단 꼭짓점
		-0.5f,  0.5f, // 좌측 하단
		 0.5f, -0.5f  // 우측 하단
	};

	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);

	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 바인딩 해제
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 선 버퍼 세팅
	float lineVertices[]
	{
		-0.5f, 0.0f, // 좌측 끝점
		 0.5f, 0.0f  // 우측 끝점
	};

	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);

	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 육면체 obj파일 로드
	loadOBJ("cube", "cube.obj");
}

bool MeshManager::loadOBJ(const std::string& name, const std::string& filePath)
{
	if (meshMap.find(name) != meshMap.end()) return true;

	std::ifstream file{ filePath };
	if (!file.is_open())
	{
		std::cerr << "OBJ 파일 열기 실패: " << filePath << '\n';
		return false;
	}

	std::vector<glm::vec3> tempPositions{};
	std::vector<float> finalVertices{};

	std::string line{};
	while (std::getline(file, line))
	{
		if (line.empty() || line[0] == '#') continue;

		std::stringstream ss{ line };
		std::string prefix{};
		ss >> prefix;

		if (prefix == "v")
		{
			glm::vec3 pos{};
			ss >> pos.x >> pos.y >> pos.z;
			tempPositions.push_back(pos);
		}
		else if (prefix == "f")
		{
			std::vector<std::string> faceTokens{};
			std::string token{};
			while (ss >> token)
			{
				faceTokens.push_back(token);
			}

			// N-gon(다각형)면을 삼각형으로 분할(Fan Triangulation)하여 정점 인덱스 추출
			for (size_t i{ 1 }; i + 1 < faceTokens.size(); ++i)
			{
				std::array<std::string, 3> triangleTokens{ faceTokens[0], faceTokens[i], faceTokens[i + 1] };

				for (const auto& t : triangleTokens)
				{
					std::stringstream tokenSS{ t };
					std::string vStr{};
					std::getline(tokenSS, vStr, '/'); // "v/vt/vn" 포맷에서 v만 추출

					if (!vStr.empty())
					{
						int vIdx{ std::stoi(vStr) };
						if (vIdx < 0) vIdx = static_cast<int>(tempPositions.size()) + vIdx + 1; // 음수 상대 인덱스 처리

						const glm::vec3& pos{ tempPositions[vIdx - 1] };
						finalVertices.push_back(pos.x);
						finalVertices.push_back(pos.y);
						finalVertices.push_back(pos.z);
					}
				}
			}
		}
	}

	file.close();

	if (finalVertices.empty()) return false;

	MeshData meshData{};
	meshData.vertexCount = static_cast<uint32_t>(finalVertices.size() / 3);
	meshData.useIndices = false;

	glGenVertexArrays(1, &meshData.VAO);
	glGenBuffers(1, &meshData.VBO);

	glBindVertexArray(meshData.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.VBO);
	glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(float), finalVertices.data(), GL_STATIC_DRAW);

	// 3D 위치 좌표 (x, y, z) 지정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	meshMap[name] = meshData;
	return true;
}

void MeshManager::drawMesh(const std::string& name, bool drawLine) const
{
	auto iter{ meshMap.find(name) };
	if (iter == meshMap.end()) return;

	const MeshData& mesh{ iter->second };

	glBindVertexArray(mesh.VAO);
	if (mesh.useIndices)
	{
		glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
	}
	glBindVertexArray(0);

}

void MeshManager::drawQuad(bool drawLine) const
{
	glBindVertexArray(quadVAO);
	if (drawLine) glDrawArrays(GL_LINE_LOOP, 0, 4);
	else glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshManager::drawTriangle(bool drawLine) const
{
	if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(triangleVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MeshManager::drawLine() const
{
	glBindVertexArray(lineVAO);

	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
}