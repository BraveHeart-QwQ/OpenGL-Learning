#include "BasicIBO.hpp"
#include <iostream>

namespace gl_template {

unsigned int BasicIBO::DEFAULT_INDICES[6] = {
	0, 1, 2,
	3, 4, 5
};

BasicIBO::BasicIBO()
    : BasicIBO(600,
               600,
               DEFAULT_VERTEX_SHADER,
               DEFAULT_FRAGMENT_SHADER) { }

BasicIBO::BasicIBO(int window_width,
                   int window_height)
    : BasicIBO(window_width,
               window_height,
               DEFAULT_VERTEX_SHADER,
               DEFAULT_FRAGMENT_SHADER) { }

BasicIBO::BasicIBO(const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : BasicIBO(600,
               600,
               vertex_shader_source,
               fragment_shader_source) { }

BasicIBO::BasicIBO(float        vertices[],
                   unsigned int vertices_size,
                   unsigned int indices[],
                   unsigned int indices_size)
    : BasicIBO(600,
               600,
               vertices,
               vertices_size,
               indices,
               indices_size) { }

BasicIBO::BasicIBO(int          window_width,
                   int          window_height,
                   float        vertices[],
                   unsigned int vertices_size,
                   unsigned int indices[],
                   unsigned int indices_size)
    : BasicIBO(window_width,
               window_height,
               vertices,
               vertices_size,
               indices,
               indices_size,
               DEFAULT_VERTEX_SHADER,
               DEFAULT_FRAGMENT_SHADER) { }

BasicIBO::BasicIBO(int                window_width,
                   int                window_height,
                   const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : BasicIBO(window_width,
               window_height,
               DEFAULT_VERTICES,
               sizeof(DEFAULT_VERTICES),
               DEFAULT_INDICES,
               sizeof(DEFAULT_INDICES),
               vertex_shader_source,
               fragment_shader_source) { }


BasicIBO::BasicIBO(int                window_width,
                   int                window_height,
                   float              vertices[],
                   unsigned int       vertices_size,
                   unsigned int       indices[],
                   unsigned int       indices_size,
                   const std::string& vertex_shader_source,
                   const std::string& fragment_shader_source)
    : BasicVBO(window_width,
               window_height,
               vertices,
               vertices_size,
               vertex_shader_source,
               fragment_shader_source),
      _indices(indices),
      _indices_size(indices_size) { }

void BasicIBO::_InitBuffer()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_IBO);
}

void BasicIBO::_InitBufferData()
{
	// NOTE Bind 属于拷贝数据的一部分（而不是初始化）
	glBindVertexArray(_VAO); // 这里要先绑定 VAO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

	glBufferData(GL_ARRAY_BUFFER, _vertices_size, _vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size, _indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void BasicIBO::_UpdateRender()
{
	glUseProgram(_shader_program);
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

} // namespace gl_template