#pragma once
#include "ZZX.h"

namespace ZZX
{
	class Noise
	{
	public:
		static std::vector<std::vector<float>> GenerateNoiseMap(int mapWidth, int mapHeight, int seed, float scale, 
			int octaves, float persistance, float lacunarity, glm::vec2 offset)
		{
			return std::vector<std::vector<float>>();
		}
	};
}

