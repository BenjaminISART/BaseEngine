#include "Managers/ComponentFactory.hpp"

// Components
#include "Objects/Components/Model.hpp"
#include "Objects/Components/Transform.hpp"
#include "Objects/Components/Shader.hpp"
#include "Objects/Components/Camera.hpp"
#include "Objects/Components/MeshRenderer.hpp"

// Others
#include "Managers/ResourceManager.hpp"
#include "DataStructure/Graph.hpp"
#include "Maths/Vec3.hpp"

namespace Managers::ComponentFactory
{
	std::shared_ptr<Component> CreateComponentWithName(std::string const& className, std::string const& params)
	{
		if (strcmp(className.c_str(), "Shader") == 0)
			return SetShader(params);
		else if (strcmp(className.c_str(), "Model") == 0)
			return SetModel(params);
		else if (strcmp(className.c_str(), "Transform") == 0)
			return SetTransform(params);
		else if (strcmp(className.c_str(), "Camera") == 0)
			return SetCamera(params);
		else if (strcmp(className.c_str(), "MeshRenderer") == 0)
			return SetTransform(params);
	}

	std::shared_ptr<Component> SetTransform(std::string const& params)
	{
		Vec3 t, r, s;
		std::stringstream sstr(params);

		sstr >> t.x;
		sstr >> t.y;
		sstr >> t.z;
		sstr >> r.x;
		sstr >> r.y;
		sstr >> r.z;
		sstr >> s.x;
		sstr >> s.y;
		sstr >> s.z;

		return std::make_shared<Transform>(t,r,s);
	}

	std::shared_ptr<Component> SetCamera(std::string const& params)
	{
		Vec3 p, t, u;
		std::stringstream sstr(params);

		sstr >> p.x;
		sstr >> p.y;
		sstr >> p.z;
		sstr >> t.x;
		sstr >> t.y;
		sstr >> t.z;
		sstr >> u.x;
		sstr >> u.y;
		sstr >> u.z;

		std::cout << p << t << u << std::endl;

		return std::make_shared<Camera>(p,t,u);
	}

	std::shared_ptr<Component> SetShader(std::string const& params)
	{
		return RManager->GetShader(params);
	}

	std::shared_ptr<Component> SetModel(std::string const& params)
	{
		return std::shared_ptr<Model>(RManager->GetModel(params));
	}

	std::shared_ptr<Component> SetMeshRenderer(std::string const& params)
	{
		return std::make_shared<MeshRenderer>();
	}
}
