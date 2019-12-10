#include "Engine/Object/Camera.hpp"
#include "Engine/Engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace ptm;


Camera::Camera(ptm::Vec3 _position, ptm::Vec3 _target, ptm::Vec3 _up) :
	m_position{ _position },
	m_target{ _target },
	m_up{ _up }
{
	cameraMatrix = ptm::Mat4_utils::LookAt(_position, _position + _target, _up);

	projectionMatrix = ptm::Mat4_utils::InfinitePerspectiveProjection(40.0f, 1000 / 800.0f, 0.01f);
}



void Camera::Update()
{
	if (Input->IsPressingKey(GLFW_KEY_W))
		m_position += m_target * 0.05f * speed;
	if (Input->IsPressingKey(GLFW_KEY_S))
		m_position -= m_target * 0.05f * speed;
	if (Input->IsPressingKey(GLFW_KEY_D))
		m_position += m_right * 0.05f * speed;
	if (Input->IsPressingKey(GLFW_KEY_A))
		m_position += -m_right * 0.05f * speed;
	if (Input->IsPressingKey(GLFW_KEY_LEFT_SHIFT))
		m_position += m_up * 0.05f * speed;
	if (Input->IsPressingKey(GLFW_KEY_LEFT_CONTROL))
		m_position += m_up * -0.05f * speed;

	cameraMatrix = Mat4_utils::LookAt(m_position, m_position + m_target, m_up);
}



void Camera::ProcessMouseMovement(float x, float y)
{
	if (glfwGetMouseButton(Core::Engine::GetEngine()->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS || m_firstProcess)
	{
		x *= 0.05f * sensibility;
		y *= 0.05f * sensibility;

		m_Yaw += x;
		m_Pitch += y;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		ptm::Vec3 front;
		front.x = cos(ptm::RAD(m_Yaw)) * cos(ptm::RAD(m_Pitch));
		front.y = sin(ptm::RAD(m_Pitch));
		front.z = sin(ptm::RAD(m_Yaw)) * cos(ptm::RAD(m_Pitch));
		m_target = front.Normal();
		m_right = (Vec3::Cross(front, 1_Vec3y)).Normal();
		m_up = (Vec3::Cross(m_right, front)).Normal();

		if (m_firstProcess)
			m_firstProcess = false;
	}
}