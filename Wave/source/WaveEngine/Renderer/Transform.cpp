#include "wavepch.h"
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace wave {
	
	Transform::Transform(glm::mat4 transform)
	: m_Transform(transform) {
		m_Position = GetPosition();
		m_Rotation = GetRotation().z;
		m_Scale = GetScale();
	}


	glm::vec3 Transform::GetPosition() const {
		return glm::vec3(m_Transform[3]);
	}

	glm::quat Transform::GetRotation() const {
		
		glm::vec3 scale = GetScale();
		//std::cout << glm::vec3(m_Transform[0]).x / scale.x << ", " << glm::vec3(m_Transform[0]).y / scale.x << ", " << glm::vec3(m_Transform[0]).z / scale.x << std::endl;
		//std::cout << glm::vec3(m_Transform[1]).x / scale.y << ", " << glm::vec3(m_Transform[1]).y / scale.y << ", " << glm::vec3(m_Transform[1]).z / scale.y << std::endl;
		//std::cout << glm::vec3(m_Transform[2]).x / scale.z << ", " << glm::vec3(m_Transform[2]).y / scale.z << ", " << glm::vec3(m_Transform[2]).z / scale.z << std::endl;
		glm::mat3 rotation = glm::mat3(
			glm::vec3(m_Transform[0]) / scale.x,  // Normalize X column
			glm::vec3(m_Transform[1]) / scale.y,  // Normalize Y column
			glm::vec3(m_Transform[2]) / scale.z   // Normalize Z column
		);
		return glm::quat_cast(rotation);

	}

	glm::vec3 Transform::GetScale() const {
		glm::vec3 scale;
		scale.x = glm::length(glm::vec3(m_Transform[0]));
		scale.y = glm::length(glm::vec3(m_Transform[1]));
		scale.z = glm::length(glm::vec3(m_Transform[2]));
		return scale;
	}

	void Transform::SetPosition(const glm::vec3& position) {
		m_Transform = glm::translate(glm::mat4(1.0f), position);
	}

	void Transform::SetRotation(float angle) {
		m_Transform = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));
	}

	void Transform::SetScale(const glm::vec3& scale) {
		m_Transform = glm::scale(glm::mat4(1.0f), scale);
	}

	void Transform::Translate(const glm::vec3& translation) {
		m_Transform = glm::translate(m_Transform, translation);
	}

	void Transform::Rotate(float angle) {
		m_Transform = glm::rotate(m_Transform, angle, glm::vec3(0, 0, 1));
	}

	void Transform::Scale(const glm::vec3& scale) {
		m_Transform = glm::scale(m_Transform, scale);
	}


}  // namespace wave