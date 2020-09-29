//
// Created by Jerry on 19/6/2020.
//

#ifndef D3NGINE_D3DTEXTURE_H
#define D3NGINE_D3DTEXTURE_H

#include <D3NGINE/Renderer/Texture.h>



typedef struct ID3D11ShaderResourceView     ID3D11ShaderResourceView;
typedef struct ID3D11SamplerState           ID3D11SamplerState;
typedef struct ID3D11Texture2D              ID3D11Texture2D;

namespace D3G
{

    class D3DTexture : public Texture2D
    {
        public:

        D3DTexture(uint32_t width, uint32_t height);

        D3DTexture(const char* filePath);

        uint32_t GetWidth() const override;

        uint32_t GetHeight() const override;

        void SetData(void *data, uint32_t size) override;

        void Bind(uint32_t slot) const override;

        bool operator==(const Texture &other) const override;

        private:

        ID3D11ShaderResourceView* m_pTexResView;

        ID3D11SamplerState* m_pTextureSampler;

        ID3D11Texture2D *m_pTexture2D = NULL;

        uint32_t m_Width, m_Height, m_Channels = 0;

        const char* m_FilePath = nullptr;

        void* m_RendererID = 0;
    };

}


#endif //D3NGINE_D3DTEXTURE_H
