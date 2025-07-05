#pragma once
#include <glm/glm.hpp>

namespace RealEngine {
	/// @brief Represents a basic camera with a projection matrix.
	class Camera {
	public:
		/// @brief Constructs a camera with the given projection matrix.
		/// @param projection The projection matrix (orthographic or perspective).
		Camera(const glm::mat4& projection)
			: m_Projection(projection) {}
		Camera() = default;

		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}