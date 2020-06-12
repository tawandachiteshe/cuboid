//
// Created by Jerry on 8/6/2020.
//

#ifndef D3NGINE_D3DGRAPHICSCONTEXT_H
#define D3NGINE_D3DGRAPHICSCONTEXT_H

#include <D3NGINE/Renderer/GraphicsContext.h>
#include <d3d11.h>

namespace D3G
{

    class D3DGraphicsContext : public GraphicsContext
    {
        public:
        void Init() override;

        void SwapBuffers() override;

        void SetVsync(bool enable) override;

        void Set_hwnd(const HWND *hwnd);

        private:
        static ID3D11Device*            m_d3dDevice;
        static ID3D11DeviceContext*     m_d3dDeviceContext;
        static IDXGISwapChain*          m_SwapChain;
        static ID3D11RenderTargetView*  m_mainRenderTargetView;
        const HWND* m_hwnd = nullptr;
        void CreateRenderTarget();
    };

}

#endif //D3NGINE_D3DGRAPHICSCONTEXT_H
