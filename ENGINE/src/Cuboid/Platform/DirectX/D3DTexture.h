//
// Created by Jerry on 19/6/2020.
//

#ifndef CUBOID_D3DTEXTURE_H
#define CUBOID_D3DTEXTURE_H

#include <Cuboid/Renderer/Texture.h>



typedef struct ID3D11ShaderResourceView     ID3D11ShaderResourceView;
typedef struct ID3D11SamplerState           ID3D11SamplerState;
typedef struct ID3D11Texture2D              ID3D11Texture2D;

namespace Cuboid
{

    class D3DTexture : public Texture2D
    {
        public:

        D3DTexture(uint32_t width, uint32_t height, uint32_t textureArraySize = 1u);

        D3DTexture(const char* filePath, uint32_t textureArraySize = 1u);

        ~D3DTexture();

        ID3D11Texture2D* GetTexturePointer() { return m_pTexture2D; };

        uint32_t GetWidth() const override;

        uint32_t GetHeight() const override;

        void SetData(void *data, uint32_t size) override;

        void Bind(uint32_t slot) const override;

        bool operator==(const Texture &other) const override;

        void* GetTextureID() { return m_pRendererID;  }


        private:

        ID3D11ShaderResourceView* m_pTexResView;

        ID3D11SamplerState* m_pTextureSampler;

        ID3D11Texture2D *m_pTexture2D = NULL;

        uint32_t m_Width, m_Height, m_Channels = 0;

        const char* m_FilePath = nullptr;

        uint32_t m_uTextureArraySize = 1u;

        void* m_pRendererID = 0;
    };

}


#endif //CUBOID_D3DTEXTURE_H
