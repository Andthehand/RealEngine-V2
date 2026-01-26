#include "FontImporter.h"

namespace RealEngine {
	Ref<Font> FontImporter::ImportFont(const AssetMetadata& metadata) {
		return CreateRef<Font>(metadata.FilePath);
	}
}


