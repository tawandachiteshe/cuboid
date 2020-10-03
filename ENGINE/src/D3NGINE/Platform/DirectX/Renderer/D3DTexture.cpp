//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include <D3NGINE/Renderer/Texture.h>
#include "D3DTexture.h"
#include "InitializeD3Devices.h"

#include <D3NGINE/utils/stb_image/stb_image.h>

namespace D3G
{


    uint32_t D3DTexture::GetWidth() const
    {
        return m_Width;
    }

    uint32_t D3DTexture::GetHeight() const
    {
        return m_Height;
    }

    void D3DTexture::SetData(void *data, uint32_t size)
    {

        HRESULT hr = S_OK;

        UINT rowPitch = (m_Width * 4) * sizeof(size);
        
        D3D11_MAPPED_SUBRESOURCE mappedTex2D;

         hr = GraphicsEngine()->GetContext()->Map(m_pTexture2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedTex2D);
       
        memcpy(mappedTex2D.pData, data, size);

        GraphicsEngine()->GetContext()->UpdateSubresource(m_pTexture2D, D3D11CalcSubresource(1, 1, 1), NULL, mappedTex2D.pData, rowPitch, 0);

        if (FAILED(hr))
        {
            D3G_CORE_ERROR("Failed to map texture");
        }

        GraphicsEngine()->GetContext()->Unmap(m_pTexture2D, 0);
    }

    void D3DTexture::Bind(uint32_t slot) const
    {
        GraphicsEngine()->GetContext()->PSSetSamplers(0, 1, &m_pTextureSampler);
        GraphicsEngine()->GetContext()->PSSetShaderResources(0, 1, &m_pTexResView);
    }

    bool D3DTexture::operator==(const Texture &other) const
    {
        return m_pRendererID == ((D3DTexture&)other).m_pRendererID;
    }

    D3DTexture::D3DTexture(uint32_t width, uint32_t height, uint32_t textureArraySize) :
            m_Width(width), m_Height(height), m_uTextureArraySize(textureArraySize)
    {
        HRESULT hr = S_OK;
        {

            D3D11_TEXTURE2D_DESC desc = {};
            desc.Width = (UINT)width;
            desc.Height = (UINT)height;
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.MipLevels = 1;
            desc.SampleDesc.Count = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.MiscFlags = 0;
            desc.ArraySize = m_uTextureArraySize;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


            hr = GraphicsEngine()->GetDevice()->CreateTexture2D(&desc, NULL, &m_pTexture2D);

            if (FAILED(hr))
            {
                D3G_CORE_ERROR("D3D FAILED TO CREATE TEXTURE");
            }


            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            if (true)
            {
                srvDesc.Texture2DArray.ArraySize = m_uTextureArraySize;
                srvDesc.Texture2DArray.MipLevels = desc.MipLevels;
                srvDesc.Texture2DArray.MostDetailedMip = 0;
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
            }
            else
            {
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                srvDesc.Texture2D.MipLevels = desc.MipLevels;
                srvDesc.Texture2D.MostDetailedMip = 0;

            }

            hr = GraphicsEngine()->GetDevice()->CreateShaderResourceView(m_pTexture2D, &srvDesc, &m_pTexResView);

            m_pRendererID = m_pTexResView;

            if (FAILED(hr))
            {
                D3G_CORE_ERROR("D3D FAILED TO CREATE SHADER RESOURCE VIEW");
            }


        }


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
                D3G_CORE_ERROR("Failed to create a sampler texture");
            }

        }

    }

    D3DTexture::D3DTexture(const char *filePath, uint32_t textureArraySize):
    m_FilePath(filePath)
    {
        

        HRESULT hr = S_OK;

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(m_FilePath, &width, &height, &channels, 0);

        {

            D3D11_TEXTURE2D_DESC desc = {};
            desc.Width = (UINT)width;
            desc.Height = (UINT)height;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.MipLevels = 1;
            desc.SampleDesc.Count = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.MiscFlags = 0;
            desc.ArraySize = m_uTextureArraySize;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

            D3D11_SUBRESOURCE_DATA pData = {};
            pData.pSysMem = (const void*)data;
            pData.SysMemPitch = desc.Width * 4;
            pData.SysMemSlicePitch = 0;


            hr = GraphicsEngine()->GetDevice()->CreateTexture2D(&desc, &pData, &m_pTexture2D);

            if (FAILED(hr))
            {
                D3G_CORE_ERROR("D3D FAILED TO CREATE TEXTURE");
            }


            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            if (true)
            {
                srvDesc.Texture2DArray.ArraySize = m_uTextureArraySize;
                srvDesc.Texture2DArray.MipLevels = desc.MipLevels;
                srvDesc.Texture2DArray.MostDetailedMip = 0;
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
            }
            else
            {
                srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                srvDesc.Texture2D.MipLevels = desc.MipLevels;
                srvDesc.Texture2D.MostDetailedMip = 0;

            }
           
            
            hr = GraphicsEngine()->GetDevice()->CreateShaderResourceView(m_pTexture2D, &srvDesc, &m_pTexResView);
            


            if (FAILED(hr))
            {
                D3G_CORE_ERROR("D3D FAILED TO CREATE SHADER RESOURCE VIEW");
            }

        }


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
               D3G_CORE_ERROR("Failed to create a sampler texture");
           }

        }

    }

    D3DTexture::~D3DTexture()
    {
        m_pTexture2D->Release();
    }
}