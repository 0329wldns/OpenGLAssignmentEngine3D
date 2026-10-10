#pragma once
#include "pch.h"
#include "Singleton.h"

struct MeshData
{
	uint32_t VAO{};
	uint32_t VBO{};
	uint32_t EBO{};
	uint32_t vertexCount{};
	uint32_t indexCount{};
	bool useIndices{ false };
};

class MeshManager : public Singleton<MeshManager>
{
	friend class Singleton<MeshManager>;

public:
	void init();

	// OBJ 파일 로드 및 메쉬 등록
	bool loadOBJ(const std::string& name, const std::string& filePath);

	// 이름으로 등록된 OBJ 메쉬 그리기
	void drawMesh(const string& name, bool drawLine = false) const;

	void drawQuad(bool drawLine = false) const;
	void drawTriangle(bool drawLine = false) const;
	void drawLine() const;

	MeshData getMeshData(const std::string& name) const
	{
		auto iter{ meshMap.find(name) };
		if (iter == meshMap.end()) return MeshData{};
		return iter->second;
	}

private:
	MeshManager() = default;
	~MeshManager() = default;

private:
	// 사각형 공용 버퍼
	uint32_t quadVAO{};
	uint32_t quadVBO{};
	uint32_t quadEBO{};

	// 삼각형 공용 버퍼
	uint32_t triangleVAO{};
	uint32_t triangleVBO{};

	// 선 공용 버퍼
	uint32_t lineVAO{};
	uint32_t lineVBO{};

	// 동적 로드된 OBJ 메쉬 보관용 Map
	std::unordered_map<std::string, MeshData> meshMap{};
};