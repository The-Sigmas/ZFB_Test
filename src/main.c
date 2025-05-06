#include "ZFB.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DESTROY) PostQuitMessage(0);
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ZFB_Device dev =
	{
		.width = 1280,
		.height = 720
	};

	ZFB_Entity player = {};
	ZFB_Color bgColor = { 255, 0, 0 };
	ZFB_Texture* bgTex = ZFB_LoadTexture("pointer.png");

	ZFB_InitFB(&dev);
	ZFB_CreateWindow(&dev, hInstance, hPrevInstance, lpCmdLine, nShowCmd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
      TranslateMessage(&msg);
    	DispatchMessage(&msg);
    }

		bgColor.r = (bgColor.r + 10) % 255;

		ZFB_DrawBG(dev, NULL, bgTex);
		ZFB_Present(dev);
		Sleep(16);
	}

	ZFB_FreeTextures();
	return 0;
}
