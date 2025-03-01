#include "LayerStack.h"

namespace RealEngine {
	LayerStack::~LayerStack() {
		RE_CORE_INFO("Destroying LayerStack");

		Clear();
	}

	void LayerStack::Clear() {
		RE_PROFILE_FUNCTION();

		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}

		m_Layers.clear();
		m_LayerInsertIndex = 0;
	}

	void LayerStack::PushLayer(Layer* layer) {
		RE_CORE_ASSERT(layer, "Layer is null");
		RE_CORE_INFO("Pushing layer: {0}", layer->GetName());

		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		RE_CORE_ASSERT(overlay, "Overlay is null");
		RE_CORE_INFO("Pushing overlay: {0}", overlay->GetName());

		overlay->OnAttach();
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;

			return;
		}

		RE_CORE_ASSERT(false, "Layer not found");
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		
			return;
		}

		RE_CORE_ASSERT(false, "Layer not found");
	}
}