#pragma once
#include "RealEngine.h"

class SandboxLayer : public RealEngine::Layer {
public:
	SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
};