#pragma once
#include "RealEngine.h"
#include "Log.h"

#ifdef RE_PLATFORM_WINDOWS
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#endif


extern RealEngine::Application* RealEngine::CreateApplication(const ApplicationCommandLineArgs& args);

int main(int argc, char** argv) {
	RealEngine::Log::Init();

	auto app = RealEngine::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}