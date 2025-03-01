#pragma once
#include "RealEngine/Render/Texture.h"
#include "GeneralManager.h"

namespace RealEngine {
	class TextureManager : public GeneralManager<Texture2D> {
	public:
		[[deprecated]]
		static Ref<Texture2D> LoadTexture(const std::filesystem::path& path) {
			//return LoadResource(path);
		}
	};
}
