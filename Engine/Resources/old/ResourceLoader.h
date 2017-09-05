#include "..\pch.h"

#include "OBJ.h"
#include "OBJ_mtllib.h"

namespace SBR
{
	class ResourceLoader
	{&
	public:
		static GLint LoadTexture(std::string path);
		static GLint LoadPNG(std::string path);
		static GLint LoadJPG(std::string path);
		static GLint LoadDDS(std::string path);
		static GLint LoadTGA(std::string path);
		static GLint LoadShader(std::string path);
		static OBJ* LoadObj(std::string path);
		static OBJ_mtllib* LoadObjMtlLib(std::string path);
	};
}