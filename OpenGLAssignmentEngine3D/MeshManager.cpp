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
		 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // 우상단
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // 우하단
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // 좌하단
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f  // 좌상단
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 삼각형 버퍼세팅
	float triVertices[]
	{
		 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, // 상단 꼭짓점
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // 좌측 하단
		 0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // 우측 하단
	};

	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);

	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 바인딩 해제
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 선 버퍼 세팅
	float lineVertices[]
	{
		-0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // 좌측 끝점
		 0.5f, 0.0f, 1.0f, 1.0f, 1.0f  // 우측 끝점
	};

	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);

	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	loadOBJ("cube", "cube.obj", glm::vec3(1.0f, 1.0f, 1.0f));
	loadOBJ("pyramid", "pyramid.obj", glm::vec3(1.0f, 1.0f, 1.0f));
}

// MeshManager.cpp
bool MeshManager::loadOBJ(const std::string& name, const std::string& filePath, const glm::vec3& defaultColor)
{
	if (meshMap.find(name) != meshMap.end()) return true;

	std::ifstream file{ filePath };
	if (!file.is_open())
	{
		std::cerr << "OBJ 파일 열기 실패: " << filePath << '\n';
		return false;
	}

	struct VertexPosColor
	{
		glm::vec3 pos{};
		glm::vec3 color{};
	};

	std::vector<VertexPosColor> tempVertices{};
	std::vector<float> finalVertices{}; // GPU로 넘어갈 최종 배열 (x, y, z, r, g, b...)

	std::string line{};
	while (std::getline(file, line))
	{
		if (line.empty() || line[0] == '#') continue;

		std::stringstream ss{ line };
		std::string prefix{};
		ss >> prefix;

		if (prefix == "v")
		{
			VertexPosColor v{};
			ss >> v.pos.x >> v.pos.y >> v.pos.z;

			// OBJ 파일의 v 줄에 r, g, b 값이 추가로 존재하는지 확인 (확장 OBJ 포맷)
			if (ss >> v.color.r >> v.color.g >> v.color.b)
			{
				// 파일 자체 색상 사용
			}
			else
			{
				// 색상이 없으면 C++ 인자로 전달받은 기본 색상 적용
				v.color = defaultColor;
			}

			tempVertices.push_back(v);
		}
		else if (prefix == "f")
		{
			std::vector<std::string> faceTokens{};
			std::string token{};
			while (ss >> token)
			{
				faceTokens.push_back(token);
			}

			// 다각형 삼각 분할
			for (size_t i{ 1 }; i + 1 < faceTokens.size(); ++i)
			{
				std::array<std::string, 3> triangleTokens{ faceTokens[0], faceTokens[i], faceTokens[i + 1] };

				for (const auto& t : triangleTokens)
				{
					std::stringstream tokenSS{ t };
					std::string vStr{};
					std::getline(tokenSS, vStr, '/');

					if (!vStr.empty())
					{
						int vIdx{ std::stoi(vStr) };
						if (vIdx < 0) vIdx = static_cast<int>(tempVertices.size()) + vIdx + 1;

						const VertexPosColor& v{ tempVertices[vIdx - 1] };

						// 1개 정점당 6개 float 데이터 푸시 (x, y, z, r, g, b)
						finalVertices.push_back(v.pos.x);
						finalVertices.push_back(v.pos.y);
						finalVertices.push_back(v.pos.z);
						finalVertices.push_back(v.color.r);
						finalVertices.push_back(v.color.g);
						finalVertices.push_back(v.color.b);
					}
				}
			}
		}
	}

	file.close();

	if (finalVertices.empty()) return false;

	MeshData meshData{};
	// 정점 1개당 float 6개(위치 3 + 색상 3)이므로 6으로 나눔
	meshData.vertexCount = static_cast<uint32_t>(finalVertices.size() / 6);

	glGenVertexArrays(1, &meshData.VAO);
	glGenBuffers(1, &meshData.VBO);

	glBindVertexArray(meshData.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, meshData.VBO);
	glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(float), finalVertices.data(), GL_STATIC_DRAW);

	GLsizei stride{ 6 * sizeof(float) };

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(mesh.VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
	glBindVertexArray(0);

	if (drawLine) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MeshManager::updateMeshColors(const std::string& name, const std::vector<glm::vec3>& colors)
{
	auto iter{ meshMap.find(name) };
	if (iter == meshMap.end()) return;

	MeshData& mesh{ iter->second };
	if (colors.size() < mesh.vertexCount) return;

	// GPU VRAM 버퍼(VBO)의 데이터를 부분 갱신하여 즉각 반영
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	for (size_t i = 0; i < mesh.vertexCount; ++i)
	{
		GLintptr colorOffset{ static_cast<GLintptr>((i * 6 + 3) * sizeof(float)) };
		glBufferSubData(GL_ARRAY_BUFFER, colorOffset, 3 * sizeof(float), &colors[i]);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshManager::resetMeshColors(const std::string& name)
{
	auto iter{ meshMap.find(name) };
	if (iter == meshMap.end()) return;

	MeshData& mesh{ iter->second };

	glm::vec3 defaultColor{ 1.0f, 1.0f, 1.0f };
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	for (size_t i = 0; i < mesh.vertexCount; ++i)
	{
		GLintptr colorOffset{ static_cast<GLintptr>((i * 6 + 3) * sizeof(float)) };
		glBufferSubData(GL_ARRAY_BUFFER, colorOffset, 3 * sizeof(float), &defaultColor);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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