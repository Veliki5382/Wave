#include "wavepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace wave {

	OrthographicCamera::OrthographicCamera(float left, float right, float up, float down, float nearBorder, float farBorder)
		: m_ProjectionMatrix(glm::ortho(left, right, down, up, nearBorder, farBorder)), m_ViewMatrix(glm::mat4(1.0f)),
		m_VPMatrix(m_ProjectionMatrix * m_ViewMatrix), m_Position(0.0f), m_Rotation(0.0f) {}

	void OrthographicCamera::RecalculateMatrices() {
		
		glm::mat4 transformation = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), 3.14f * m_Rotation / 180, glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transformation);
		m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}  // namespace wave