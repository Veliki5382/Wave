#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

#include "WaveEngine/Core.h"

namespace wave {
	
	class WAVE_API Transform {

	public:
		Transform(glm::mat4 transform = glm::mat4(1.0f));
		
		operator glm::mat4() { return m_Transform; }
		operator const glm::mat4() const { return m_Transform; }
		
		inline Transform operator+ (const Transform& other) const {
			return Transform(m_Transform + other.m_Transform);
		}
		inline Transform operator- (const Transform& other) const {
			return Transform(m_Transform - other.m_Transform);
		}
		inline Transform operator* (const Transform& other) const {
			return Transform(m_Transform * other.m_Transform);
		}

		glm::vec3 GetPosition() const;
		glm::quat GetRotation() const;
		glm::vec3 GetScale() const;

		void SetPosition(const glm::vec3& position);
		void SetRotation(float angle);
		void SetScale(const glm::vec3& scale);
		inline void SetScale(float x, float y) { SetScale(glm::vec3(x, y, 1.0f)); }

		void Translate(const glm::vec3& translation);
		void Rotate(float angle);
		void Scale(const glm::vec3& scale);
		inline void Scale(float x, float y) { Scale(glm::vec3(x, y, 1.0f)); }


	private:
		glm::mat4 m_Transform;
		glm::vec3 m_Position, m_Scale;
		float m_Rotation;
	};


}  // namespace wave

#endif