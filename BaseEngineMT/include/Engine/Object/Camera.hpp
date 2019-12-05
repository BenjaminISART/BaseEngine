#ifndef __CAMERA__
#define __CAMERA__

#include "Engine/Maths/Mat4_utils.hpp"
#include "Engine/Manager/InputManager.hpp"

class Camera
{
private:

#pragma region private attributes
	float Yaw = -90.0f;
	float Pitch = 0.0f;

	ptm::Vec3 position;
	ptm::Vec3 target;
	ptm::Vec3 up;
	ptm::Vec3 right;
	ptm::Vec3 diffPosition;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Camera() = default; // CTOR

	Camera(ptm::Vec3 _position, ptm::Vec3 _target, ptm::Vec3 _up):
		position{_position},
		target{_target},
		up{_up}
	{
		cameraMatrix = ptm::Mat4_utils::LookAt(_position, _position + _target, _up);

		projectionMatrix = ptm::Mat4_utils::InfinitePerspectiveProjection(40.0f, 1000 / 800.0f, 0.01f);
	} // CTOR

	// Camera(Camera const& c); // CPY CTOR
	// Camera(Camera const && c); // MV CTOR
	~Camera() = default; // DTOR

#pragma region public attributes
	ptm::Mat4 cameraMatrix;
	ptm::Mat4 projectionMatrix;
#pragma endregion

#pragma region public methods
	void Update()
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

	void ProcessMouseMovement(float x, float y)
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
#pragma endregion
};

#endif // __CAMERA__