#ifndef __CAMERA__
#define __CAMERA__

#include "Engine/Maths/Mat4_utils.hpp"

class Camera
{
private:

#pragma region private attributes
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Camera() = default; // CTOR

	Camera(ptm::Vec3 position, ptm::Vec3 target, ptm::Vec3 up)
	{
		cameraMatrix = ptm::Mat4_utils::LookAt(position, position + target, up);

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
#pragma endregion
};

#endif // __CAMERA__