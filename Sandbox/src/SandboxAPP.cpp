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
		RE_ASSERT(false, "Assertion failed!");
	}
};

RealEngine::Application* RealEngine::CreateApplication() {
	return new Sandbox();
}