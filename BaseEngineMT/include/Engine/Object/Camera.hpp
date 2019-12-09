#ifndef __CAMERA__
#define __CAMERA__

#include "Engine/Manager/InputManager.hpp"
#include "Engine/Maths/Mat4_utils.hpp"

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
	Camera(ptm::Vec3 _position, ptm::Vec3 _target, ptm::Vec3 _up); // CTOR
	Camera(Camera const& c) = default; // CPY CTOR
	Camera(Camera&& c) = default; // MV CTOR
	~Camera() = default; // DTOR

#pragma region public attributes
	ptm::Mat4 cameraMatrix;
	ptm::Mat4 projectionMatrix;
#pragma endregion

#pragma region public methods
	void Update();

	void ProcessMouseMovement(float x, float y);
#pragma endregion
};

#endif // __CAMERA__