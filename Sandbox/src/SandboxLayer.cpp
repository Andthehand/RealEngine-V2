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
	RE_CORE_INFO("SandboxLayer Updated");
}