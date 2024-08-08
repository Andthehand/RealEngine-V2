#include <RealEngine/Core/EntryPoint.h>
#include <RealEngine.h>

#include <iostream>

class Sandbox : public RealEngine::Application {
public:
	Sandbox() {
	}

	~Sandbox() {

	}

	void Run() override {
		std::cout << "Hello, RealEngine!" << std::endl;
	}
};

RealEngine::Application* RealEngine::CreateApplication() {
	return new Sandbox();
}