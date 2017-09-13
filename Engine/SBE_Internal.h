#pragma once

#define WINGDIAPI __declspec(dllimport)
#define APIENTRY __stdcall

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#define GLEW_STATIC
#define GLEW_NO_GLU

#pragma warning (disable : 4251)  //disables dll export warning when members dont have __declspec(dllexport)
#pragma warning (disable : 4005)  //disables "WINGDIAPI": Makro-Redifinition Warning

#if defined(SBE_BUILD_DLL) && defined(SBE_BUILD)
	#error "You must not have both SBE_BUILD_DLL and SBE_BUILD defined"
#endif 

#if defined(SBE_BUILD_DLL)
	#define SBE_API __declspec(dllexport)
#elif defined(SBE_DLL)
	#define SBE_API __declspec(import)
#else
	#define SBE_API
#endif

#define SBE_PACKAGE_MAXSIZE 5000

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )