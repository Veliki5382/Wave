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

	void OpenGLRenderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Transform& transform ) {
		
		vertexArray->Bind();
		shader->Bind();
		//std::cout << m_VPMatrix[0][0] << ", " << m_VPMatrix[0][2] << ", " << m_VPMatrix[0][2] << ", " << m_VPMatrix[0][3] << std::endl;
		//std::cout << m_VPMatrix[1][0] << ", " << m_VPMatrix[1][2] << ", " << m_VPMatrix[1][2] << ", " << m_VPMatrix[1][3] << std::endl;
		//std::cout << m_VPMatrix[2][0] << ", " << m_VPMatrix[2][2] << ", " << m_VPMatrix[2][2] << ", " << m_VPMatrix[2][3] << std::endl;
		//std::cout << m_VPMatrix[3][0] << ", " << m_VPMatrix[3][2] << ", " << m_VPMatrix[3][2] << ", " << m_VPMatrix[3][3] << std::endl;

		shader->UploadUniform4f("u_VPMatrix", m_VPMatrix);
		shader->UploadUniform4f("u_Transform", glm::mat4(transform));

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}  // namespace wave