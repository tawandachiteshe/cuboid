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
        return 0;
    }

    uint32_t D3DTexture::GetHeight() const
    {
        return 0;
    }

    void D3DTexture::SetData(void *data, uint32_t size)
    {

    }

    void D3DTexture::Bind(uint32_t slot) const
    {

    }

    bool D3DTexture::operator==(const Texture &other) const
    {
        return false;
    }

    D3DTexture::D3DTexture(uint32_t width, uint32_t height) :
            m_Width(width), m_Height(height)
    {


    }

    D3DTexture::D3DTexture(const char *filePath):
    m_FilePath(filePath)
    {

    }
}