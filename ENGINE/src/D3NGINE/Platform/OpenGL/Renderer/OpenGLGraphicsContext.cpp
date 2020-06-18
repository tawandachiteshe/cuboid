/*
 * OpenGLGraphicsContext.cpp
 *
 *  Created on: 26 May,2020
 *      Author: Jerry
 */
#include <glad/glad.h>
#include <D3NGINE/Platform/OpenGL/Renderer/OpenGLGraphicsContext.h>
#include <imgui_impl_sdl.h>

namespace D3G {

    OpenGLGraphicsContext::~OpenGLGraphicsContext() {

    }

    void OpenGLGraphicsContext::Init() {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        int gladStatus = gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
        D3G_ASSERT(gladStatus, "GLAD FAILED TO INIT");
        D3G_CORE_DEBUG("GLAD INIT WITH STATUS CODE: " + std::to_string(gladStatus));

        const unsigned char *vendor = glGetString(GL_VENDOR);
        const unsigned char *version = glGetString(GL_VERSION);
        const unsigned char *orenderer = glGetString(GL_RENDERER);

        D3G_CORE_INFO(std::string((char *) vendor) + " GPU" + "OpenGL Version: " +
                      std::string((char *) version) + " Renderer: " + std::string((char *) orenderer));
        D3G_ASSERT(m_Window, "Window no data");
        D3G_ASSERT(m_Context, "Window no data");

    }


    OpenGLGraphicsContext::OpenGLGraphicsContext(SDL_Window *window) {
        D3G_CORE_INFO("GRaphics context");
        this->m_Window = window;
        this->m_Context = SDL_GL_CreateContext(m_Window);
        D3G_ASSERT(m_Window, "Window no data");
        D3G_ASSERT(m_Context, "Window no data");
        SDL_GL_MakeCurrent(m_Window, m_Context);

    }

    void OpenGLGraphicsContext::SetVsync(bool enable) {
        if (enable)
            SDL_GL_SetSwapInterval(1);
        else
            SDL_GL_SetSwapInterval(0);
    }

    void OpenGLGraphicsContext::SwapBuffers() {
        SDL_GL_SwapWindow(m_Window);
    }

    void OpenGLGraphicsContext::ResizeSwapBuffers()
    {

    }

} /* namespace D3G */
