#include "..\SBE_Internal.h"
#include "WindowHint.h"

SBI::WindowHint::WindowHint()
{
	this->resizable = GL_TRUE;
	this->visible = GL_TRUE;
	this->decorated = GL_TRUE;
	this->red_bits = 8;
	this->green_bits = 8;
	this->blue_bits = 8;
	this->alpha_bits = 8;
	this->depth_bits = 24;
	this->stencil_bits = 8;
	this->accum_red_bits = 0;
	this->accum_green_bits = 0;
	this->accum_blue_bits = 0;
	this->accum_alpha_bits = 0;
	this->aux_buffer = 0;
	this->samples = 0;
	this->refresh_rate = 0;
	this->stereo = GL_FALSE;
	this->srgb_capable = GL_FALSE;
	this->client_api = SBI::CLIENT_API::OPENGL_API;
	this->context_version_major = 1;
	this->context_version_minor = 0;
	this->context_robustness = SBI::CONTEXT_ROBUSTNESS::NO_ROBUSTNESS;
	this->opengl_forward_compatible = GL_FALSE;
	this->opengl_debug_context = GL_FALSE;
	this->opengl_profile = SBI::OPENGL_PROFILE::OPENGL_ANY_PROFILE;
}


SBI::WindowHint::~WindowHint()
{
}
