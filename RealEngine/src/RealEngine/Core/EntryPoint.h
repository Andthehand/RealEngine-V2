#pragma once
#include "Application.h"

extern RealEngine::Application* RealEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = RealEngine::CreateApplication();
	app->Run();
}