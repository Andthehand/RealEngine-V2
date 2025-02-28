#pragma once
#include "RealEngine.h"
#include "Log.h"

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern RealEngine::Application* RealEngine::CreateApplication(const ApplicationCommandLineArgs& args);

int main(int argc, char** argv) {
	RealEngine::Log::Init();

	auto app = RealEngine::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}