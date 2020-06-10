//
// Created by Jerry on 8/6/2020.
//

#ifndef D3NGINE_D3DGRAPHICSCONTEXT_H
#define D3NGINE_D3DGRAPHICSCONTEXT_H

#include <D3NGINE/Renderer/GraphicsContext.h>

namespace D3G
{

    class D3DGraphicsContext : public GraphicsContext
    {
        public:
        void Init() override;

        void SwapBuffers() override;

        void SetVsync(bool enable) override;

    };

}

#endif //D3NGINE_D3DGRAPHICSCONTEXT_H
