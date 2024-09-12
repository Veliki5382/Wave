#include "wavepch.h"
#include "OpenGLIndexBuffer.h"

#include <GLAD/glad.h>


namespace wave {

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count) {

		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {

		glDeleteBuffers(1, &m_BufferID);
	}

	void OpenGLIndexBuffer::Bind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::Unbind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}  // namespace wave