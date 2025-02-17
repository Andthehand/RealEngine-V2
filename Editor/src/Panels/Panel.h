#pragma once

namespace RealEngine {
	class Panel {
	public:
		Panel() = default;
		virtual ~Panel() = default;
		virtual void OnImGui() = 0;
	public:
		bool IsVisible = true;
	};
}