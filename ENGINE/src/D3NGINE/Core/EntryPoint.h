
#include <D3NGINE/utils/Logger.h>

#ifndef D3G_ENTRYPOINT_H
#define D3G_ENTRYPOINT_H

extern D3G::Application* D3G::CreateApplication();

int main(int argc, char** argv)
{
	D3G::Logger::Init();
	auto app = D3G::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

