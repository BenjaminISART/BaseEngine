#ifndef __CAMERA__
#define __CAMERA__

#include "Objects/Components/Component.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4_utils.hpp"

namespace Objects::Components
{
	class Camera : public Component
	{
	private:

		float Pitch = 0.0f;
		float Yaw = -90.0f;

	public:
		ptm::Vec3 position;
		ptm::Vec3 diffPosition;
		ptm::Vec3 target;
		ptm::Vec3 up;
		ptm::Vec3 right;

		
		ptm::Mat4 m_LookAt;
		ptm::Mat4 m_Projection;

		Camera();
		Camera(Camera const& c);
		Camera(ptm::Vec3 const& p, ptm::Vec3 const& t, ptm::Vec3 const& u);
		~Camera();

		void Update() override;
		void Start() override;

		void ProcessMouseMovement(float x, float y);

		Camera& operator=(Camera const& c);
	};
}

#endif