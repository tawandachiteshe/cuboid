#pragma once

#include "Cuboid/Renderer/Texture2DArray.h"
#include "cstdint"
#include "D3DTexture.h"

namespace Cuboid
{

	class D3DTexture2DArray : public Texture2DArray
	{
	public:
		D3DTexture2DArray(uint32_t arraySize);
		D3DTexture2DArray(const std::initializer_list<Ref<Texture2D>>& textures);

		// Inherited via Texture2DArray
		virtual void AddTexture(const Ref<Texture2D>& texture) override;

		~D3DTexture2DArray();

		virtual void Bind(uint32_t slot) override;

	private:

		std::unordered_map<uint32_t, ID3D11ShaderResourceView*> TextureMap;

		std::array<ID3D11ShaderResourceView*, 16> m_Textures;

		ID3D11ShaderResourceView* m_srvTexArray = 0;

		ID3D11Texture2D* texArray = 0;

		ID3D11SamplerState* m_pTextureSampler = NULL;
		uint32_t textureIndex = 0;




	};

}