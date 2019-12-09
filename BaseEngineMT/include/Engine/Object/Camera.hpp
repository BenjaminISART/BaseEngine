#ifndef __CAMERA__
#define __CAMERA__

#include "Engine/Manager/InputManager.hpp"
#include "Engine/Maths/Mat4_utils.hpp"


// basically only for overviewCamera of class Engine
class Camera
{
private:

#pragma region private attributes
	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;

	int m_height;
	int m_width;

	ptm::Vec3 m_position;
	ptm::Vec3 m_target;
	ptm::Vec3 m_up;
	ptm::Vec3 m_right;
	ptm::Vec3 m_diffPosition;

	bool m_firstProcess = true;
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

	void SetWidthHeight(const int& w, const int& h) { m_height = h; m_width = w; }

	void UpdateProjectionMatrix(const int& w, const int& h)
	{
		if (w == m_width && h == m_height)
			return;

		SetWidthHeight(w, h);
		
		projectionMatrix = ptm::Mat4_utils::InfinitePerspectiveProjection(40.0f, float(m_width) / float(m_height), 0.01f);
	}
#pragma endregion
};

#endif // __CAMERA__