//
// Created by Jerry on 8/6/2020.
//

#ifndef CUBOID_D3DGRAPHICSCONTEXT_H
#define CUBOID_D3DGRAPHICSCONTEXT_H

#include <Cuboid/Renderer/GraphicsContext.h>

namespace Cuboid
{

    class D3DGraphicsContext : public GraphicsContext
    {
        public:
        D3DGraphicsContext(HWND window);

        void Init() override;

        void SwapBuffers() override;

        void SetVsync(bool enable) override;

        void CreateRenderTarget();

        ~D3DGraphicsContext();

        void ResizeSwapBuffers() override;
   
    };

}

#endif //CUBOID_D3DGRAPHICSCONTEXT_H
