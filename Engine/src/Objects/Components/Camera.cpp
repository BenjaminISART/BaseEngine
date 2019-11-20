#include "Objects/Components/Camera.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Components/Transform.hpp"
#include "Maths/Mat4_utils.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Math.hpp"
#include "DataStructure/Graph.hpp"
#include "Engine/Engine.hpp"
#include "Managers/InputManager.hpp"

using namespace ptm;

namespace Objects::Components
{
	Camera::Camera() :
		position{ 0_Vec3 },
		diffPosition{ 0_Vec3 },
		target { 1_Vec3z },
		up { 1_Vec3y }
	{
		m_LookAt = Mat4_utils::LookAt(position, position + target, up);
		m_Projection = Mat4_utils::InfinitePerspectiveProjection(45.0f, 1600.0f / 900.0f, 0.01f);
	}

	Camera::Camera(Camera const& c):
		position{c.position},
		diffPosition{ c.diffPosition },
		target{c.target},
		up{c.up}
	{
		m_LookAt = Mat4_utils::LookAt(position, position + target, up);
		m_Projection = Mat4_utils::InfinitePerspectiveProjection(45.0f, 1600.0f / 900.0f, 0.01f);
	}

	Camera::Camera(ptm::Vec3 const& p, ptm::Vec3 const& t, ptm::Vec3 const& u)
	{
		position = p;
		diffPosition = p;
		target = t;
		up = u;

		m_LookAt = Mat4_utils::LookAt(position, position + target, up);
		m_Projection = Mat4_utils::InfinitePerspectiveProjection(40.0f, 1600.0f / 900.0f, 0.01f);
	}

	Camera::~Camera()
		= default;

	void Camera::Update()
	{
		if (Input->IsPressingKey(GLFW_KEY_W))
			position += target * 0.05f;
		if (Input->IsPressingKey(GLFW_KEY_S))
			position -= target * 0.05f;
		if (Input->IsPressingKey(GLFW_KEY_D))
			position += right * 0.05f;
		if (Input->IsPressingKey(GLFW_KEY_A))
			position += -right * 0.05f;

		m_LookAt = Mat4_utils::LookAt(position + diffPosition, position + target, up);

		if (m_gameObject != nullptr)
		{
			position = m_gameObject->GetComponent<Transform>()->translation;
		}
	}

	void Camera::Start()
	{
	}

	Camera& Camera::operator=(Camera const& c)
	{
		return *this;
	}

	void Camera::ProcessMouseMovement(float x, float y)
	{
		x *= 0.05f;
		y *= 0.05f;

		Yaw += x;
		Pitch += y;

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		ptm::Vec3 front;
		front.x = cos(ptm::RAD(Yaw)) * cos(ptm::RAD(Pitch));
		front.y = sin(ptm::RAD(Pitch));
		front.z = sin(ptm::RAD(Yaw)) * cos(ptm::RAD(Pitch));
		target = front.Normal();
		// Also re-calculate the Right and Up vector
		right = (Vec3::Cross(front, 1_Vec3y)).Normal();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = (Vec3::Cross(right, front)).Normal();
	}

}
