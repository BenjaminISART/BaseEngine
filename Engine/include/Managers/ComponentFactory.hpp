#ifndef __COMPONENT_FACTORY__
#define __COMPONENT_FACTORY__

#include <sstream>
#include <string>
#include <iostream>
#include "Objects/Components/Component.hpp"
using namespace Objects::Components;

namespace Managers::ComponentFactory
{
	std::shared_ptr<Component> CreateComponentWithName(std::string const& className, std::string const& params);

	std::shared_ptr<Component> SetTransform(std::string const& params);
	std::shared_ptr<Component> SetShader(std::string const& params);
	std::shared_ptr<Component> SetModel(std::string const& params);
	std::shared_ptr<Component> SetCamera(std::string const& params);
	std::shared_ptr<Component> SetMeshRenderer(std::string const& params);
}

#endif
