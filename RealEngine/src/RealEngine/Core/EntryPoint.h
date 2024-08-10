#pragma once
#include "RealEngine.h"
#include "Log.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

extern RealEngine::Application* RealEngine::CreateApplication();

int main(int argc, char** argv) {
	RealEngine::Log::Init();

	auto app = RealEngine::CreateApplication();

	RE_CORE_INFO("Application is running...");

	int i = 0;
	while (true) {
		RE_PROFILE_FRAME();
		
		std::string test = std::format("Frame number: {0}", i);
		RE_CORE_TRACE("{0}", test);
		RE_CORE_INFO("{0}", test);
		RE_CORE_WARN("{0}", test);
		RE_CORE_ERROR("{0}", test);
		RE_CORE_CRITICAL("Crit");

		std::this_thread::sleep_for(std::chrono::milliseconds(33));

		i++;
	}

	app->Run();
}