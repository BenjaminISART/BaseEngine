#include "Engine/Property/Transform.hpp"



Transform::Transform() : position{ Vec3::zero }, rotation{ Vec3::zero }, scale{ Vec3::zero }
{
	UpdateMatrix();
}



void Transform::UpdateMatrix()
{
	transformMatrix = ptm::Mat4_utils::CreateTRS(position, rotation, scale);
}