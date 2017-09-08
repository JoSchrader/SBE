#pragma once
#include "..\..\pch.h"
#include <sys/stat.h>

namespace SBR
{
	class File
	{
	public:
		static SBE_EXPORT bool Exist(char* path)
		{
			struct stat st;
			if (stat(path, &st) != 0)
			{
				return false;
			}
			return true;
		}

		static SBE_EXPORT void Extension(char* path, char* result, int maxLen)
		{
			int len = (int)strlen(path);
			int i = 0;
			for (i = len; i >= 0; i--)
			{
				if (path[i] == '.')
					break;
			}

			if (i == -1)
				*result = 0;

			strcpy_s(result, maxLen, &path[i]);
		}

		static SBE_EXPORT int Size(char* path)
		{
			struct stat st;
			if (stat(path, &st) != 0) {
				return 0;
			}
			return st.st_size;
		}

		/// <summary>Caller is responsible to free returned pointer</summary>
		static SBE_EXPORT char* Read(char* path, int* size)
		{
			std::ifstream t(path, std::ios::binary);
			t.seekg(0, std::ios::end);
			*size = (int) t.tellg();
			char* buffer = (char*)malloc(sizeof(char) * *size + 1);
			t.seekg(0);
			t.read(buffer, *size);
			buffer[*size] = 0;
			return buffer;
		}

		static SBE_EXPORT void Write(char* path, char* buffer, int size)
		{
			FILE* file = fopen(path, "wb");
			fwrite(buffer, 1, size, file);
			fclose(file);
		}
	};
}