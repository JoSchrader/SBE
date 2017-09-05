#pragma once
#include "..\pch.h"
#include "Resource.h"


namespace SBR
{
	class Texture : public SBR::Resource
	{
	public:
		GLint glid;

		Texture();
		~Texture();
	};	
}

/*
enum class TextureCoordinates : int
{
X,
Y,
Z,
S = X,
T = Y,
R = Z
};

enum class TextureMinFilter : int
{
NEAREST = GL_NEAREST,
LINEAR = GL_LINEAR,
NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

enum class TextureMagFilter : int
{
NEAREST = GL_NEAREST,
LINEAR = GL_LINEAR,
};

enum class TextureWrapMode : int
{
CLAMP = GL_CLAMP,
REPEAT = GL_REPEAT,
CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
};

enum class TextureCompareMode : int
{
R_TO_TEXTURE = GL_COMPARE_R_TO_TEXTURE,
NONE = GL_NONE
};

enum class TextureCompareFunc : int
{
LEQUAL = GL_LEQUAL,
GEQUAL = GL_GEQUAL,
LESS = GL_LESS,
GREATER = GL_GREATER,
EQUAL = GL_EQUAL,
NOTEQUAL = GL_NOTEQUAL,
ALWAYS = GL_ALWAYS,
NEVER = GL_NEVER,
};

enum class DepthTextureMode : int
{
LUMINANCE = GL_LUMINANCE,
INTENSITY = GL_INTENSITY,
ALPHA = GL_ALPHA
};

void SetMinFilter(TextureMinFilter filter);
TextureMinFilter GetMinFilter();

void SetMagFilter(TextureMagFilter filter);
TextureMagFilter GetMagFilter();

void SetMinLOD(GLfloat minLOD);
GLfloat GetMinLod();

void SetMaxLOD(GLfloat maxLOD);
GLfloat GetMaxLod();

void SetBaseLevel(GLfloat baseLevel);
GLfloat GetBaseLevel();

void SetMaxLevel(GLfloat maxLevel);
GLfloat GetMaxLevel();

void SetWrap(TextureCoordinates axis, TextureWrapMode wrapMode);
TextureWrapMode GetWrap(TextureCoordinates axis);

void SetBorderColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GLfloat* GetBorderColor();

void SetPriority(GLfloat priority);
GLfloat GetPriority();

void SetCompareMode(TextureCompareMode compareMode);
TextureCompareMode GetCompareMode();

void SetCompareFunc(TextureCompareFunc func);
TextureCompareFunc GetCompareFunc();

void SetDepthTextureMode(DepthTextureMode mode);
DepthTextureMode GetDepthTextureMode();

void SetGenerateMidmap(GLboolean mode);
GLboolean GetGenerateMidmap();*/