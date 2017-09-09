#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS



#define GLEW_STATIC
#define GLEW_NO_GLU

#include "..\GLEW\src\glew.h"
#include "..\GLFW\src\glfw3.h"

#include <atomic>
#include <vector>
#include <winsock2.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <cstdio>
#include <Windows.h>


#pragma warning (disable : 4251)  //disables dll export warning when members dont have __declspec(dllexport)

#define SBE_EXPORT __declspec(dllexport)

#define SBE_PACKAGE_MAXSIZE 5000