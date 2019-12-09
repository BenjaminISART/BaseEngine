#include "Engine/Manager/Renderer.hpp"
#include "Engine/Engine.hpp"

void Renderer::RendActualScene(unsigned int shaderid)
{
	for (auto& object : *m_scene[m_actualScene].GetSGraph().GetObjects())
	{
		const auto& t = object.second.transform.transformMatrix;
		const auto& m = object.second.model;

		glUniformMatrix4fv(glGetUniformLocation(shaderid, "TRS"), 1, false, t.m_array);
		glUniformMatrix4fv(glGetUniformLocation(shaderid, "view"), 1, false, Core::Engine::GetEngine()->overviewCamera.cameraMatrix.m_array);
		glUniformMatrix4fv(glGetUniformLocation(shaderid, "proj"), 1, false, Core::Engine::GetEngine()->overviewCamera.projectionMatrix.m_array);

		object.second.Draw(shaderid);
	}
}