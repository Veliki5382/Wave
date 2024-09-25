#include "wavepch.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace wave {

	void OpenGLRenderer::ClearColor(float red, float green, float blue , float alpha = 1.0f) {
		
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::Begin() {
	}

	void OpenGLRenderer::End() {
	}

	void OpenGLRenderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		
		vertexArray->Bind();
		shader->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}  // namespace wave