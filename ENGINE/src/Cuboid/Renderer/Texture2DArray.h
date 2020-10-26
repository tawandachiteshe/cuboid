#pragma once
#include "Texture.h"
#include <iterator>

namespace Cuboid
{
	class Texture2DArray
	{
	public:
		virtual void AddTexture(const Ref<Texture2D>& texture) = 0;
		virtual void Bind(uint32_t slot) = 0;

		static Ref<Texture2DArray> Create(const std::initializer_list<Ref<Texture2D>>& textures);
		static Ref<Texture2DArray> Create(uint32_t arraySize);

		virtual ~Texture2DArray() {};

	};

}

