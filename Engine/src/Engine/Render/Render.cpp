#include "Engine/Render/Render.hpp"
#include "Managers/ResourceManager.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Components/Transform.hpp"
#include "Objects/Components/Shader.hpp"
#include "Objects/Components/Model.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core::Renderer
{
	std::unique_ptr<Render> Render::m_instance = nullptr;


	Render* Render::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<Render>();

		return m_instance.get();
	}

	void Render::RendScene()
	{
		RecursiveRend(SGraph->Head());
	}

	void Render::RecursiveRend(DataStructure::Node* n)
	{
		Objects::GameObject* go = n->data.get();

		for (size_t i = 0; i < n->Childrens().size(); i++)
		{
			go = n->Childrens()[i]->data.get();

			if (go != nullptr)
			{
				const auto t = go->GetComponent<Objects::Components::Transform>();
				const auto s = go->GetComponent<Objects::Components::Shader>();
				const auto m = go->GetComponent<Objects::Components::Model>();

				if (t != nullptr && s != nullptr && m != nullptr)
				{
					s->Use();

					glUniformMatrix4fv(glGetUniformLocation(s->ID(), "TRS"), 1, false, t->TRS.m_array);
					glUniformMatrix4fv(glGetUniformLocation(s->ID(), "proj"), 1, false, SGraph->m_mainCamera->m_Projection.m_array);
					glUniformMatrix4fv(glGetUniformLocation(s->ID() , "view"), 1, false, SGraph->m_mainCamera->m_LookAt.m_array);

					for (GLuint i = 0; i < go->GetComponent<Objects::Components::Model>()->m_mesh.size(); i++)
					{
						///* We recuperate the texture's ID. */
						//RManager->GetTexture("white")->Use();

						//glBindVertexArray(go->GetComponent<Objects::Components::Model>()->m_mesh[i].VAO);
						//glDrawElements(GL_TRIANGLES, go->GetComponent<Objects::Components::Model>()->m_mesh[i].index.size(),
						//	GL_UNSIGNED_INT, nullptr);
						//glBindVertexArray(0);

						go->GetComponent<Objects::Components::Model>()->m_mesh[i].Draw(*s);
					}
				}

				RecursiveRend(n->Childrens()[i].get());
			}
		}
	}

}
