#pragma once
#include "ZZX.h"

namespace ZZX
{
	class MapGenerator
	{
	public:
		void GenerateMap()
		{
			return;
		}
	};


	class MeshData
	{
	public:
		MeshData(int meshWidth, int meshHeight);
		void AddTriangle(int a, int b, int c);
	private:
		int m_MeshWidth;
		int m_MeshHeight;
	};


	struct TerrainType
	{
		std::string Name;
		float Height;
		glm::vec3 Color;
	};
}

