#include <iostream>
#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"
#include "Maths/Mat4_utils.hpp"
#include "Engine/Engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace ptm;

int main()
{
	Core::Engine* engine = EngineInst;
	engine->Load();
	engine->Run();
	engine->Unload();
	return 0;
}
