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

#include "GUIRenderer.h"
#include <Rocket/Core.h>
#include "GUIRenderer.h"
#include <string>

#define GL_CLAMP_TO_EDGE 0x812F

namespace JN {

	GUIRenderer::GUIRenderer() {
		m_rocket_context = NULL;
		m_width = 0;
		m_height = 0;
		_vao = 0;
		_vbo = 0;
		_iao = 0;

	}

	GUIRenderer::~GUIRenderer() {
		// delete buffers
		if (_vbo != 0) glDeleteBuffers(1, &_vbo);
		if (_iao != 0) glDeleteBuffers(1, &_iao);
		if (_vao != 0) glDeleteVertexArrays(1, &_vao);
	}


	void GUIRenderer::init(Camera2D *camera) {

		_camera = camera;

		// generate buffers
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);

		if (_vbo == 0)
			glGenBuffers(1, &_vbo);

		if (_iao == 0)
			glGenBuffers(1, &_iao);

		// init shaders
		_program.addAttribute("vertexPosition");
        _program.addAttribute("vertexColor");
		_program.addAttribute("vertexUV");

		_program.compileShaders("../shaders/gui.vert", "../shaders/gui.frag");

		// binding buffers
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// set data pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Rocket::Core::Vertex),
							  (void *) offsetof(Rocket::Core::Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Rocket::Core::Vertex),
							  (void *) offsetof(Rocket::Core::Vertex, colour));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rocket::Core::Vertex),
                              (void *) offsetof(Rocket::Core::Vertex, tex_coord));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iao);

		glBindVertexArray(0);
	}


// Called by Rocket when it wants to render geometry that it does not wish to optimise.
	void GUIRenderer::RenderGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices,
									 const Rocket::Core::TextureHandle texture,
									 const Rocket::Core::Vector2f &translation) {

		glm::mat4 projection = _camera->getCameraMatrix();





		// OpenGL

		glBindBuffer(GL_ARRAY_BUFFER, _vbo); ///< bind Vertex Array
		// orphan buffer and upload vertex data
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(Rocket::Core::Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, num_vertices * sizeof(Rocket::Core::Vertex), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0); ///< unbind Vertex Array

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iao); ///< bind Indices Array
		// upload indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, num_indices * sizeof(GLuint), indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); ///< unbind Indices Array


		// OpenGL Render
		_program.use();

		// activate texture
		glActiveTexture(GL_TEXTURE0);

		//upload uniforms to shaders
		GLint camLoc = _program.getUniformLocation("P");
		glUniformMatrix4fv(camLoc, 1, GL_FALSE, &projection[0][0]);

		GLint offsetLoc = _program.getUniformLocation("offsetVec");
		glUniform2fv(offsetLoc, 1, &translation.x);

		GLint textureLocation = _program.getUniformLocation("mySampler");
		glUniform1i(textureLocation, 0);

        // sends true if texture is being used, false to render only plain color
        GLint isTextureBoundLoc = _program.getUniformLocation("isTextureBound");
        glUniform1i(isTextureBoundLoc, (texture ? 1 : 0));

		glBindVertexArray(_vao);// render stuff
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
		// rendering done - unbinding everything...
		glBindVertexArray(0);
		_program.unUse();


	}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
	Rocket::Core::CompiledGeometryHandle GUIRenderer::CompileGeometry(Rocket::Core::Vertex *ROCKET_UNUSED_PARAMETER(
																	  vertices),

	int ROCKET_UNUSED_PARAMETER(num_vertices),
	int *ROCKET_UNUSED_PARAMETER(indices),
	int ROCKET_UNUSED_PARAMETER(num_indices),

	const Rocket::Core::TextureHandle ROCKET_UNUSED_PARAMETER(texture)

	) {
	ROCKET_UNUSED(vertices);
	ROCKET_UNUSED(num_vertices);
	ROCKET_UNUSED(indices);
	ROCKET_UNUSED(num_indices);
	ROCKET_UNUSED(texture);

	return (Rocket::Core::CompiledGeometryHandle) NULL;
}

// Called by Rocket when it wants to render application-compiled geometry.		
void GUIRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED_PARAMETER(geometry),
										 const Rocket::Core::Vector2f &ROCKET_UNUSED_PARAMETER(translation)) {
	ROCKET_UNUSED(geometry);
	ROCKET_UNUSED(translation);
}

// Called by Rocket when it wants to release application-compiled geometry.		
void GUIRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED_PARAMETER(geometry)) {
	ROCKET_UNUSED(geometry);
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.		
void GUIRenderer::EnableScissorRegion(bool enable) {
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.		
void GUIRenderer::SetScissorRegion(int x, int y, int width, int height) {
	glScissor(x, m_height - (y + height), width, height);
}

// Set to byte packing, or the compiler will expand our struct, which means it won't read correctly from file
#pragma pack(1) 
struct TGAHeader {
	char idLength;
	char colourMapType;
	char dataType;
	short int colourMapOrigin;
	short int colourMapLength;
	char colourMapDepth;
	short int xOrigin;
	short int yOrigin;
	short int width;
	short int height;
	char bitsPerPixel;
	char imageDescriptor;
};
// Restore packing
#pragma pack()

// Called by Rocket when a texture is required by the library.		
bool GUIRenderer::LoadTexture(Rocket::Core::TextureHandle &texture_handle, Rocket::Core::Vector2i &texture_dimensions,
							  const Rocket::Core::String &source) {


    if (source.Find(".png") != -1) {
        printf("Loading PNG texture : %s\n\n", source.CString());
        JN::GLTexture loadedTexture = JN::ResourceManager::getTexture(std::string(source.CString()));

        texture_handle = loadedTexture.id;
        texture_dimensions.x = loadedTexture.widht;
        texture_dimensions.y = loadedTexture.height;
        return true;
    }

    if (source.Find(".tga") != -1) {
        printf("Loading TGA texture : %s\n\n", source.CString());
        Rocket::Core::FileInterface *file_interface = Rocket::Core::GetFileInterface();
        Rocket::Core::FileHandle file_handle = file_interface->Open(source);
        if (!file_handle) {
            return false;
        }

        file_interface->Seek(file_handle, 0, SEEK_END);
        size_t buffer_size = file_interface->Tell(file_handle);
        file_interface->Seek(file_handle, 0, SEEK_SET);

        ROCKET_ASSERTMSG(buffer_size > sizeof(TGAHeader),
                         "Texture file size is smaller than TGAHeader, file must be corrupt or otherwise invalid");
        if (buffer_size <= sizeof(TGAHeader)) {
            file_interface->Close(file_handle);
            return false;
        }

        char *buffer = new char[buffer_size];
        file_interface->Read(buffer, buffer_size, file_handle);
        file_interface->Close(file_handle);

        TGAHeader header;
        memcpy(&header, buffer, sizeof(TGAHeader));

        int color_mode = header.bitsPerPixel / 8;
        int image_size = header.width * header.height * 4; // We always make 32bit textures

        if (header.dataType != 2) {
            Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Only 24/32bit uncompressed TGAs are supported.");
            return false;
        }

        // Ensure we have at least 3 colors
        if (color_mode < 3) {
            Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Only 24 and 32bit textures are supported");
            return false;
        }

        const char *image_src = buffer + sizeof(TGAHeader);
        unsigned char *image_dest = new unsigned char[image_size];

        // Targa is BGR, swap to RGB and flip Y axis
        for (long y = 0; y < header.height; y++) {
            long read_index = y * header.width * color_mode;
            long write_index = ((header.imageDescriptor & 32) != 0) ? read_index : (header.height - y - 1) *
                                                                                   header.width *
                                                                                   color_mode;
            for (long x = 0; x < header.width; x++) {
                image_dest[write_index] = image_src[read_index + 2];
                image_dest[write_index + 1] = image_src[read_index + 1];
                image_dest[write_index + 2] = image_src[read_index];
                if (color_mode == 4)
                    image_dest[write_index + 3] = image_src[read_index + 3];
                else
                    image_dest[write_index + 3] = 255;

                write_index += 4;
                read_index += color_mode;
            }
        }

        texture_dimensions.x = header.width;
        texture_dimensions.y = header.height;

        bool success = GenerateTexture(texture_handle, image_dest, texture_dimensions);

        delete[] image_dest;
        delete[] buffer;

        return true;
    }
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool GUIRenderer::GenerateTexture(Rocket::Core::TextureHandle &texture_handle, const Rocket::Core::byte *source,
								  const Rocket::Core::Vector2i &source_dimensions) {
	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	if (texture_id == 0) {
		printf("Failed to generate textures\n");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				 source);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	texture_handle = (Rocket::Core::TextureHandle) texture_id;

	return true;
}

// Called by Rocket when a loaded texture is no longer required.		
void GUIRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle) {
	glDeleteTextures(1, (GLuint * ) & texture_handle);
}

}