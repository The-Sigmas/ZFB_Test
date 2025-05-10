#include "ZFB.h"

/*
 * This example shows hot to set up a simple
 * project using the ZFB library/
 *
 * NOTE:
 * - Focused on Windows
 *   - For Linux see the `master` branch
 * - Uses WinGDI to create a window
 *   - for other methods see the respected branches
 */

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
	ZFB_InitFB(&dev);
	ZFB_CreateWindow(&dev, hInstance, hPrevInstance, lpCmdLine, nShowCmd);

	ZFB_Color bgColor = { 255, 0, 0 };

	ZFB_Texture* bgTex = ZFB_LoadTexture("pointer.png");
	ZFB_Texture* playerTex = ZFB_LoadTexture("spaceship.png");

	ZFB_Entity playerEntity =
	{
		.id = 0,
		.physics = // NOTE: you can also define physics seperately, ZFB_PhysicsBody playerPhysics = {...};
		{
			.position = { dev.width/2, dev.height/2 }, // ZFB_Vector2
			.velocity = { 0, 0 },
			.acceleration = { 0, 0 },
			.mass = 5,
			.gravity = true, // TODO: Change to .gravity
		},
		.width = 50,
		.height = 50,	
	};

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
      TranslateMessage(&msg);
    	DispatchMessage(&msg);
    }

		ZFB_DrawBG(dev, NULL, bgTex);

		ZFB_Rect player =
		{
			.position = playerEntity.physics.position,
			.width = playerEntity.width,
			.height = playerEntity.height,
			.texture = playerTex // NOTE: Can be NULL aswell
		};

		ZFB_DrawRect(dev, player, NULL);

		ZFB_Present(dev);
		Sleep(16);
	}

	ZFB_FreeTextures();
	return 0;
}
