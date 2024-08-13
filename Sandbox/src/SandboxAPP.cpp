#include <RealEngine/Core/EntryPoint.h>
#include <RealEngine.h>

#include <iostream>

#include "SandboxLayer.h"

class Sandbox : public RealEngine::Application {
public:
	Sandbox(const RealEngine::ApplicationSpecification& specification) 
		: Application(specification) {
		PushLayer(new SandboxLayer());
	}

	~Sandbox() = default;
};

RealEngine::Application* RealEngine::CreateApplication(const RealEngine::ApplicationCommandLineArgs& args) {
	ApplicationSpecification specification = { "Sandbox", args };
	return new Sandbox(specification);
}