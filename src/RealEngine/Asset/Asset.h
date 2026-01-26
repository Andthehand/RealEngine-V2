#pragma once

#include "RealEngine/Types/StringHash.h"

namespace RealEngine {	
	using AssetHandle = StringHash;

	enum class AssetType : uint16_t {
		None = 0,
		Texture2D,
		Shader,
		Font
	};

	namespace Utils {
		static const char* GetAssetTypeString(AssetType type) {
			switch (type) {
			case AssetType::None: return "None";
			case AssetType::Texture2D: return "Texture2D";
			case AssetType::Shader: return "Shader";
			case AssetType::Font: return "Font";
			default: return "Unknown";
			}
		};
	}

	class Asset {
	public:
		Asset() = default;
		virtual ~Asset() = default;

		AssetHandle GetHandle() const { return m_Handle; }
		virtual AssetType GetType() const = 0;
	private:
		AssetHandle m_Handle;

		friend class AssetManager;
	};
}