//
// Created by Jerry on 8/6/2020.
//

#ifndef D3NGINE_D3DGRAPHICSCONTEXT_H
#define D3NGINE_D3DGRAPHICSCONTEXT_H

#include <D3NGINE/Renderer/GraphicsContext.h>

typedef struct ID3D11Device             ID3D11Device;
typedef struct ID3D11DeviceContext      ID3D11DeviceContext;
typedef struct IDXGISwapChain           IDXGISwapChain;
typedef struct ID3D11RenderTargetView   ID3D11RenderTargetView;

typedef struct SDL_Window SDL_Window;

namespace D3G
{

    class D3DGraphicsContext : public GraphicsContext
    {
        public:
        D3DGraphicsContext(SDL_Window *window);

        void Init() override;

        void SwapBuffers() override;

        void SetVsync(bool enable) override;

        private:
        static ID3D11Device*            m_d3dDevice;
        static ID3D11DeviceContext*     m_d3dDeviceContext;
        static IDXGISwapChain*          m_SwapChain;
        static ID3D11RenderTargetView*  m_mainRenderTargetView;

        public:
        inline static ID3D11DeviceContext* GetContext() { return m_d3dDeviceContext; }
        inline static ID3D11Device* GetDevice()  { return   m_d3dDevice; }
        inline static IDXGISwapChain* GetSwapChain()  { return m_SwapChain; };
        inline static ID3D11RenderTargetView* GetRenderTargetView() { return m_mainRenderTargetView; }
        void CreateRenderTarget();

        ~D3DGraphicsContext();

        void ResizeSwapBuffers() override;

        private:
        //TODO: WIndow needs to clean up
        void CleanupDeviceD3D();
        void CleanupRenderTarget();
        SDL_Window *m_Window;
        HWND m_hwnd = NULL;
    };

}

#endif //D3NGINE_D3DGRAPHICSCONTEXT_H
