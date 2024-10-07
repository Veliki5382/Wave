#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>

#include "WaveEngine/Core.h"


namespace wave {

	class WAVE_API OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float up, float down, float nearBorder = -1.0f, float farBorder = 1.0f);

		inline const glm::vec3 GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMatrices(); }

		inline const float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateMatrices(); }

		inline const glm::mat4 GetProjectionMatrix() { RecalculateMatrices(); return m_ProjectionMatrix; }
		inline const glm::mat4 GetViewMatrix() { RecalculateMatrices(); return m_ViewMatrix; }
		inline const glm::mat4 GetVPMatrix() { RecalculateMatrices(); return m_VPMatrix; }

	private:
		void RecalculateMatrices();

	private:
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
		glm::mat4 m_VPMatrix;

		glm::vec3 m_Position;
		float m_Rotation;

	};


}  // namespace wave


#endif