#pragma once
#include "RealEngine.h"
#include "Log.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

extern RealEngine::Application* RealEngine::CreateApplication(const ApplicationCommandLineArgs& args);

int main(int argc, char** argv) {
	RealEngine::Log::Init();

	auto app = RealEngine::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}