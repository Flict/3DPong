#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->m_pos = pos;
		this->m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		this->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->m_projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	//void MoveForward(float amt)
	//{
	//	pos += forward * amt;
	//}

	//void MoveRight(float amt)
	//{
	//	pos += glm::cross(up, forward) * amt;
	//}

	//void Pitch(float angle)
	//{
	//	glm::vec3 right = glm::normalize(glm::cross(up, forward));

	//	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	//	up = glm::normalize(glm::cross(forward, right));
	//}

	//void RotateY(float angle)
	//{
	//	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	//	glm::mat4 rotation = glm::rotate(angle, UP);

	//	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	//	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	//}

protected:
private:
	glm::mat4 m_projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward; // Direction the camera is looking
	glm::vec3 m_up; // Which direction is up
};