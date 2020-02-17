#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NOMINMAX
#include <windows.h>

#undef NOMINMAX
#include <windows.h>
#include <assert.h>
#include <d3d11.h>
#include <D3DX11tex.h>
#include <DirectXMath.h>
using namespace DirectX;
#include <cassert>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

//assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#pragma comment(lib,"assimp.lib")

//stb-master
#include <stb-master/stb_image.h>
#include <stb-master/stb_image_write.h>

#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ


HWND GetWindow();

#endif // !MAIN_H_