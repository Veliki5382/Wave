#include "wavepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>


namespace wave {

	GLenum GetOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		default: WAVE_CORE_ASSERT(false, "Cannot conver to OpenGL Base Type.");
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_VertexArrayID);
		
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_VertexArrayID);	
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		
		WAVE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout.");

		glBindVertexArray(m_VertexArrayID);
		vertexBuffer->Bind();

		for (const auto& element : vertexBuffer->GetLayout()) {
			WAVE_CORE_TRACE("Name: {0}, Size: {1}, Count: {2}", element.Name, element.Size, element.Count);
			glEnableVertexAttribArray(element.Index);
			glVertexAttribPointer(
				element.Index,
				element.Count,
				GetOpenGLBaseType(element.Type),
				element.Normalized,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		
		glBindVertexArray(m_VertexArrayID);
		indexBuffer->Bind();
		
		m_IndexBuffer = indexBuffer;
	}


}  // namespace wave
