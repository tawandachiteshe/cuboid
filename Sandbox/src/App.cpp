#include <Cuboid/Core/Cuboid.h>
#include <Cuboid/Core/EntryPoint.h>
#include "SandBox2D.h"

using namespace Cuboid;

class App: public Cuboid::Application
{
	public:

		App()
	{
			CUBOID_CORE_INFO("APP iniT");
			PushLayer(new SandBox2D("Sandbox2D Layer"));
	}

};

Cuboid::Application* Cuboid::CreateApplication()
{
	return new App();
}
