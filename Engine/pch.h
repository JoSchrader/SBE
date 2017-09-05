#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <atomic>
#include <vector>
#include <winsock2.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <cstdio>
#include <Windows.h>

#include <intrin.h> // for debug assertion

#define GLEW_STATIC
#define GLEW_NO_GLU
#define GLFW_NO_GLU

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <libpng\png.h>

#define XMD_H
extern "C"
{
#include <libjpeg\jpeglib.h>
}

#pragma warning (disable : 4251)  //disables dll export warning when members dont have __declspec(dllexport)

#define SBE_EXPORT __declspec(dllexport)

#define SBE_PACKAGE_MAXSIZE 5000