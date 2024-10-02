#include "wavepch.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace wave {

	OpenGLRenderer::OpenGLRenderer()
		: m_VPMatrix(glm::mat4(1.0f)) {}

	void OpenGLRenderer::ClearColor(float red, float green, float blue , float alpha = 1.0f) {
		
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::Begin(OrthographicCamera& camera) {
		
		m_VPMatrix = camera.GetVPMatrix();
	}

	void OpenGLRenderer::End() {
	}

	void OpenGLRenderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		
		vertexArray->Bind();
		shader->Bind();
		shader->UploadUniform4f("u_VPMatrix", m_VPMatrix);

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}  // namespace wave