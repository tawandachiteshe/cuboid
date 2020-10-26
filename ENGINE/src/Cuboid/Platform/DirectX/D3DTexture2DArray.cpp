#include "D3DTexture2DArray.h"
#include <d3d11.h>
#include "InitializeD3Devices.h"
#include "Cuboid/Renderer/RendererAPI.h"

namespace Cuboid
{



	D3DTexture2DArray::D3DTexture2DArray(uint32_t arraySize)
	{
		HRESULT hr = S_OK;
		if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{



			D3D11_SAMPLER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.MipLODBias = 0.f;
			desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			desc.MinLOD = 0.f;
			desc.MaxLOD = 0.f;

			hr = GraphicsEngine()->GetDevice()->CreateSamplerState(&desc, &m_pTextureSampler);

			if (FAILED(hr))
			{
				CUBOID_CORE_ERROR("Failed to create a sampler texture");
			}


		}
	}

	D3DTexture2DArray::D3DTexture2DArray(const std::initializer_list<Ref<Texture2D>>& textures) 
	{
		HRESULT hr = S_OK;
		if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{

			{

				D3D11_SAMPLER_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.MipLODBias = 0.f;
				desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				desc.MinLOD = 0.f;
				desc.MaxLOD = 0.f;

				hr = GraphicsEngine()->GetDevice()->CreateSamplerState(&desc, &m_pTextureSampler);

				if (FAILED(hr))
				{
					CUBOID_CORE_ERROR("Failed to create a sampler texture");
				}



				uint32_t i = 0;
				for (auto it = textures.begin(); it != textures.end(); it++)
				{

					m_Textures[i] = (ID3D11ShaderResourceView*)std::dynamic_pointer_cast<D3DTexture>(*it)->GetTextureID();
					++i;


				}

			}
		}

	}

	void D3DTexture2DArray::AddTexture(const Ref<Texture2D>& texture)
	{
		
		TextureMap.emplace(0,std::dynamic_pointer_cast<D3DTexture>(texture)->GetTextureID());
		
	}


	D3DTexture2DArray::~D3DTexture2DArray()
	{
	
	}

	void D3DTexture2DArray::Bind(uint32_t slot)
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::DirectX)
		{
			GraphicsEngine()->GetContext()->PSSetSamplers(0, 1, &m_pTextureSampler);
			GraphicsEngine()->GetContext()->PSSetShaderResources(0, m_Textures.size(), &m_Textures[0]);
		}
	}

}