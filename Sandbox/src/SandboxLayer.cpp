#include "SandboxLayer.h"

SandboxLayer::SandboxLayer() 
	: Layer("SandboxLayer") {}

void SandboxLayer::OnAttach() {
	RE_CORE_INFO("SandboxLayer Attached");
}

void SandboxLayer::OnDetach() {
	RE_CORE_INFO("SandboxLayer Detached");
}

void SandboxLayer::OnUpdate() {
	RE_INFO("Mouse X: {0}, Mouse Y: {1}", RealEngine::Inputs::GetMouseX(), RealEngine::Inputs::GetMouseY());
	RE_INFO("Mouse Button: {0}", RealEngine::Inputs::IsMouseButtonPressed(RealEngine::Mouse::ButtonLeft) ? "Pressed" : "Not Pressed");
	RE_INFO("ESC: {0}", RealEngine::Inputs::IsKeyPressed(RealEngine::Key::Escape) ? "Pressed" : "Not Pressed");
}

void SandboxLayer::OnEvent(const RealEngine::Event& event) {
}