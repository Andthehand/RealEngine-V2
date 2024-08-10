#include <RealEngine/Core/EntryPoint.h>
#include <RealEngine.h>

#include <iostream>

class Sandbox : public RealEngine::Application {
public:
	Sandbox(const RealEngine::ApplicationSpecification& specification) 
		: Application(specification) {

	}

	~Sandbox() {

	}
};

RealEngine::Application* RealEngine::CreateApplication(const RealEngine::ApplicationCommandLineArgs& args) {
	ApplicationSpecification specification = { "Sandbox", args };
	return new Sandbox(specification);
}