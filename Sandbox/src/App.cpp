#include <D3NGINE/D3G.h>
#include <D3NGINE/EntryPoint.h>
#include "SandBox2D.h"

using namespace D3G;

class App: public D3G::Application
{
	public:

		App()
	{
			D3G_CORE_INFO("APP iniT");
			PushLayer(new SandBox2D("Sandbox2D Layer"));
	}

};

D3G::Application* D3G::CreateApplication()
{
	return new App();
}
