//
// Created by Jerry on 19/6/2020.
//

#include <d3gpch.h>
#include <D3NGINE/Renderer/Texture.h>
#include "D3DTexture.h"
#include "D3DGraphicsContext.h"
#include <d3d11.h>
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


        D3D11_MAPPED_SUBRESOURCE subMappedResource;
        D3DGraphicsContext::GetContext()->Map(m_Texture2D, 0, D3D11_MAP_WRITE_DISCARD, 0,&subMappedResource);

        void* pixels = subMappedResource.pData;
        memcpy(pixels, data, size);

        subMappedResource.RowPitch = m_Width * 4;
        subMappedResource.DepthPitch = 0;

        D3DGraphicsContext::GetContext()->Unmap(m_Texture2D, 0);

    }

    void D3DTexture::Bind(uint32_t slot) const
    {

        D3DGraphicsContext::GetContext()->PSSetSamplers(slot, 1, &m_TextureSampler);

    }

    bool D3DTexture::operator==(const Texture &other) const
    {
        return false;
    }

    D3DTexture::D3DTexture(uint32_t width, uint32_t height) :
            m_Width(width), m_Height(height)
    {

        D3D11_TEXTURE2D_DESC Texture2Ddesc;
        ZeroMemory(&Texture2Ddesc, sizeof(Texture2Ddesc));
        Texture2Ddesc.Width = width;
        Texture2Ddesc.Height = height;
        Texture2Ddesc.MipLevels = 1;
        Texture2Ddesc.ArraySize = 1;
        Texture2Ddesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
        Texture2Ddesc.SampleDesc.Count = 1;
        Texture2Ddesc.Usage = D3D11_USAGE_DEFAULT;
        Texture2Ddesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        Texture2Ddesc.CPUAccessFlags = 0;
        Texture2Ddesc.Usage = D3D11_USAGE_DYNAMIC;


        D3DGraphicsContext::GetDevice()->CreateTexture2D(&Texture2Ddesc, nullptr, &m_Texture2D);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;
        ZeroMemory(&ShaderResourceViewDesc, sizeof(ShaderResourceViewDesc));
        ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
        ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        ShaderResourceViewDesc.Texture2D.MipLevels = ShaderResourceViewDesc.Texture2D.MipLevels;
        ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

        D3DGraphicsContext::GetDevice()->CreateShaderResourceView(m_Texture2D, &ShaderResourceViewDesc, &m_TexResView);

        m_Texture2D->Release();


        D3D11_SAMPLER_DESC Samplerdesc;
        ZeroMemory(&Samplerdesc, sizeof(Samplerdesc));
        Samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        Samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.MipLODBias = 0.f;
        Samplerdesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        Samplerdesc.MinLOD = 0.f;
        Samplerdesc.MaxLOD = 0.f;
        Samplerdesc.MaxAnisotropy = 4;
        D3DGraphicsContext::GetDevice()->CreateSamplerState(&Samplerdesc, &m_TextureSampler);


    }

    D3DTexture::D3DTexture(const char *filePath):
    m_FilePath(filePath)
    {

        INT width, height, channels = 0;
        stbi_uc* pixels = stbi_load(filePath , &width, &height, &channels, 0);

        m_Width = (UINT)width;
        m_Height = (UINT)height;
        m_Channels = (UINT)channels;

        D3D11_TEXTURE2D_DESC Texture2Ddesc;
        ZeroMemory(&Texture2Ddesc, sizeof(Texture2Ddesc));
        Texture2Ddesc.Width = m_Width;
        Texture2Ddesc.Height = m_Height;
        Texture2Ddesc.MipLevels = 1;
        Texture2Ddesc.ArraySize = 1;
        Texture2Ddesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
        Texture2Ddesc.SampleDesc.Count = 1;
        Texture2Ddesc.Usage = D3D11_USAGE_DEFAULT;
        Texture2Ddesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        Texture2Ddesc.CPUAccessFlags = 0;
        Texture2Ddesc.Usage = D3D11_USAGE_IMMUTABLE;

        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = pixels;
        subResource.SysMemPitch = m_Width * m_Channels;
        subResource.SysMemSlicePitch = 0;

        D3DGraphicsContext::GetDevice()->CreateTexture2D(&Texture2Ddesc, &subResource, &m_Texture2D);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;
        ZeroMemory(&ShaderResourceViewDesc, sizeof(ShaderResourceViewDesc));
        ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
        ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        ShaderResourceViewDesc.Texture2D.MipLevels = ShaderResourceViewDesc.Texture2D.MipLevels;
        ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

        D3DGraphicsContext::GetDevice()->CreateShaderResourceView(m_Texture2D, &ShaderResourceViewDesc, &m_TexResView);

        m_RendererID = m_TexResView;

        m_Texture2D->Release();
        D3D11_SAMPLER_DESC Samplerdesc;
        ZeroMemory(&Samplerdesc, sizeof(Samplerdesc));
        Samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        Samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        Samplerdesc.MipLODBias = 0.f;
        Samplerdesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        Samplerdesc.MinLOD = 0.f;
        Samplerdesc.MaxLOD = 0.f;
        Samplerdesc.MaxAnisotropy = 4;

        D3DGraphicsContext::GetDevice()->CreateSamplerState(&Samplerdesc, &m_TextureSampler);

        if(pixels)
            stbi_image_free(pixels);
    }
}