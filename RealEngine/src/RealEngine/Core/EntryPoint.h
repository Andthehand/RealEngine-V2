#pragma once
#include "RealEngine.h"
#include "Log.h"

extern RealEngine::Application* RealEngine::CreateApplication();

int main(int argc, char** argv) {
	RealEngine::Log::Init();

	auto app = RealEngine::CreateApplication();
	RE_CORE_INFO("Application is running...");
	app->Run();

}