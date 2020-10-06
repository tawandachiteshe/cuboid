
#include <Cuboid/utils/Logger.h>

#ifndef CUBOID_ENTRYPOINT_H
#define CUBOID_ENTRYPOINT_H

extern Cuboid::Application* Cuboid::CreateApplication();

int main(int argc, char** argv)
{
	Cuboid::Logger::Init();
	auto app = Cuboid::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif

