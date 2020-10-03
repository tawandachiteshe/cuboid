#pragma once

#include "D3NGINE/Renderer/Texture2DArray.h"
#include "cstdint"
#include "D3DTexture.h"

namespace D3G
{

	class D3DTexture2DArray : public Texture2DArray
	{
	public:
		D3DTexture2DArray(uint32_t arraySize);
		D3DTexture2DArray(const std::initializer_list<Ref<Texture2D>>& textures);

		// Inherited via Texture2DArray
		virtual void AddTexture(const Ref<Texture2D>& texture) override;
		virtual void RemoveTexture(size_t index) override;
		virtual Ref<Texture2D>& GetTexture(size_t index) override;

		~D3DTexture2DArray();

		virtual void Bind(uint32_t slot) override;

	private:

		std::vector<ID3D11ShaderResourceView*> m_vcTextures;

		std::vector<Ref<Texture2D>> m_vcTexture2D;

		ID3D11ShaderResourceView* m_srvTexArray = 0;

		ID3D11Texture2D* texArray = 0;

		ID3D11SamplerState* m_pTextureSampler = NULL;




		// Inherited via Texture2DArray
		

	public:

		// Inherited via Texture2DArray
		virtual std::vector<Ref<Texture2D>>::iterator Begin() override;

		virtual std::vector<Ref<Texture2D>>::iterator End() override;


		// Inherited via Texture2DArray
		virtual std::vector<Ref<Texture2D>> GetTextures() override;

	};

}