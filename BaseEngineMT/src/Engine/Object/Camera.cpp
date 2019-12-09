#include "Engine/Object/Camera.hpp"
using namespace ptm;


Camera::Camera(ptm::Vec3 _position, ptm::Vec3 _target, ptm::Vec3 _up) :
	position{ _position },
	target{ _target },
	up{ _up }
{
	cameraMatrix = ptm::Mat4_utils::LookAt(_position, _position + _target, _up);

	projectionMatrix = ptm::Mat4_utils::InfinitePerspectiveProjection(40.0f, 1000 / 800.0f, 0.01f);
}



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

	cameraMatrix = Mat4_utils::LookAt(position, position + target, up);
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
	right = (Vec3::Cross(front, 1_Vec3y)).Normal();
	up = (Vec3::Cross(right, front)).Normal();
}