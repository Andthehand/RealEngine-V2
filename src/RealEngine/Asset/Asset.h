#pragma once

#include "RealEngine/Types/StringHash.h"

namespace RealEngine {
	using AssetHandle = StringHash;

	enum class AssetType : uint16_t {
		None = 0,
		Texture2D,
		Shader
	};

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