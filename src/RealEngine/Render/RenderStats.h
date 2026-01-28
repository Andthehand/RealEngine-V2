#pragma once
#include <cstdint>

namespace RealEngine {
	struct RenderStats {
        // Frame
        uint32_t DrawCalls = 0;

        // 2D
        struct Sprite {
            uint32_t DrawCalls = 0;

            uint32_t QuadCount = 0;
            uint32_t TextureBinds = 0;
		} Sprites;

        // Text
        struct Text {
            uint32_t DrawCalls = 0;

            uint32_t GlyphCount = 0;
		} Text;

        void Reset() {
            DrawCalls = 0;

            Sprites.DrawCalls = 0;
            Sprites.QuadCount = 0;
            Sprites.TextureBinds = 0;

            Text.DrawCalls = 0;
            Text.GlyphCount = 0;
        }
	};
}