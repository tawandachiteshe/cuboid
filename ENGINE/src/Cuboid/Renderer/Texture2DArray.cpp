#include "Cuboidpch.h"
#include "Texture2DArray.h"
#include "Cuboid/Platform/DirectX/D3DTexture2DArray.h"

namespace Cuboid
{
	Ref<Texture2DArray> Texture2DArray::Create(const std::initializer_list<Ref<Texture2D>>& textures)
	{
		return CreateRef<D3DTexture2DArray>(textures);
	}


	Ref<Texture2DArray> Texture2DArray::Create(uint32_t arraySize)
	{
		return CreateRef<D3DTexture2DArray>(arraySize);
	}

}