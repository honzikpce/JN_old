/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef GUIRENDERER_H
#define GUIRENDERER_H



#include <Rocket/Core/RenderInterface.h>
#include <glm/glm.hpp>
#include "GUIOpenGL.h"
#include "Camera2D.hpp"
#include "GLSLProgram.hpp"
#include "DebugRenderer.hpp"
#include "ResourceManager.hpp"


#if defined(ROCKET_PLATFORM_LINUX)
    struct __X11NativeWindowData
    {
        Window window;
        Display *display;
        XVisualInfo *visual_info;
    };
#endif

namespace JN {

    class GUIRenderer : public Rocket::Core::RenderInterface//,  public GUIRendererExtensions
    {
    public:
        GUIRenderer();

        virtual ~GUIRenderer();

        /// Called by Rocket when it wants to render geometry that it does not wish to optimise.
        virtual void RenderGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                                    Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f &translation);

        /// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
        virtual Rocket::Core::CompiledGeometryHandle
        CompileGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices,
                        Rocket::Core::TextureHandle texture);

        /// Called by Rocket when it wants to render application-compiled geometry.
        virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry,
                                            const Rocket::Core::Vector2f &translation);

        /// Called by Rocket when it wants to release application-compiled geometry.
        virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

        /// Called by Rocket when it wants to enable or disable scissoring to clip content.
        virtual void EnableScissorRegion(bool enable);

        /// Called by Rocket when it wants to change the scissor region.
        virtual void SetScissorRegion(int x, int y, int width, int height);

        /// Called by Rocket when a texture is required by the library.
        virtual bool
        LoadTexture(Rocket::Core::TextureHandle &texture_handle, Rocket::Core::Vector2i &texture_dimensions,
                    const Rocket::Core::String &source);

        /// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
        virtual bool GenerateTexture(Rocket::Core::TextureHandle &texture_handle, const Rocket::Core::byte *source,
                                     const Rocket::Core::Vector2i &source_dimensions);

        /// Called by Rocket when a loaded texture is no longer required.
        virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);


        void init(Camera2D *camera);


    protected:
        GLuint _vbo, _vao, _iao;
        GLSLProgram _program;
        int m_width;
        int m_height;
        void *m_rocket_context;
        Camera2D *_camera;
        DebugRenderer *_debugRenderer = nullptr;

#if defined(ROCKET_PLATFORM_MACOSX)
        AGLContext gl_context;
#elif defined(ROCKET_PLATFORM_LINUX)
        struct __X11NativeWindowData nwData;
        GLXContext gl_context;
#elif defined(ROCKET_PLATFORM_WIN32)
        HWND window_handle;
        HDC device_context;
        HGLRC render_context;
#else
#error Platform is undefined, this must be resolved so gl_context is usable.
#endif

    };
}
#endif
