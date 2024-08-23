#include "SandboxLayer.h"


SandboxLayer::SandboxLayer() 
	: Layer("SandboxLayer") {}

void SandboxLayer::OnAttach() {
	RealEngine::Application::Get().GetWindow().SetVSync(true);
	RealEngine::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
}

void SandboxLayer::OnDetach() {
}

void SandboxLayer::OnUpdate() {
	RealEngine::RenderCommands::Clear();
}

void SandboxLayer::OnEvent(const RealEngine::Event& event) {
}