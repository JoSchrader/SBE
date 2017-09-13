#pragma once
#include <GLFW\glfw3.h>
#include "..\SBE_Internal.h"

namespace SBI
{
	enum class SBE_API CLIENT_API { OPENGL_API = GLFW_OPENGL_API, OPENGL_ES_API = GLFW_OPENGL_ES_API };
	enum class SBE_API CONTEXT_ROBUSTNESS{ NO_ROBUSTNESS = GLFW_NO_ROBUSTNESS, NO_RESET_NOTIFICATION = GLFW_NO_RESET_NOTIFICATION, LOSE_CONTEXT_ON_RESET = GLFW_LOSE_CONTEXT_ON_RESET };
	enum class SBE_API OPENGL_PROFILE { OPENGL_ANY_PROFILE = GLFW_OPENGL_ANY_PROFILE, OPENGL_COMPAT_PROFILE = GLFW_OPENGL_COMPAT_PROFILE, OPENGL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE };

	class SBE_API WindowHint
	{
	public:
		GLboolean resizable;
		GLboolean visible;
		GLboolean decorated;
		GLint red_bits;
		GLint green_bits;
		GLint blue_bits;
		GLint alpha_bits;
		GLint depth_bits;
		GLint stencil_bits;
		GLint accum_red_bits;
		GLint accum_green_bits;
		GLint accum_blue_bits;
		GLint accum_alpha_bits;
		GLint aux_buffer;
		GLint samples;
		GLint refresh_rate;
		GLboolean stereo;
		GLboolean srgb_capable;
		CLIENT_API client_api;
		GLint context_version_major;
		GLint context_version_minor;
		CONTEXT_ROBUSTNESS context_robustness;
		GLboolean opengl_forward_compatible;
		GLboolean opengl_debug_context;
		OPENGL_PROFILE opengl_profile;

		WindowHint();
		~WindowHint();
	};
}
