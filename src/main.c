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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ZFB_Device dev =
	{
		.width = 1280,
		.height = 720,
		.title = "ZFB_Test"
	};

	int bulletCount = 0;
	ZFB_Entity* bullets = malloc(sizeof(ZFB_Entity) * bulletCount);

	ZFB_Event event = {};

	ZFB_InitFB(&dev);
	ZFB_EventInit();
	ZFB_CreateWindow(&dev, hInstance, hPrevInstance, lpCmdLine, nShowCmd);

	ZFB_Color bgColor = { 255, 0, 0 };

	ZFB_Texture* bgTex = ZFB_LoadTexture("pointer.png");
	ZFB_Texture* playerTex = ZFB_LoadTexture("spaceship.png");
	ZFB_Texture* osakaTex = ZFB_LoadTexture("textureexample.png");

	ZFB_Entity playerEntity =
	{
		.id = 0,
		.physics = // NOTE: you can also define physics seperately, ZFB_PhysicsBody playerPhysics = {...};
		{
			.position = { dev.width/2, dev.height/2 }, // ZFB_Vector2
			.velocity = { 0, 0 },
			.acceleration = { 0, 0 },
			.mass = 5,
			.gravity = false,
			.rotation = 0,
		},
		.width = 50,
		.height = 50,
	}; ZFB_Rect player = {.texture = playerTex};

	ZFB_Rect osaka =
	{
		.position = { 0, 0 },
		.width = 200,
		.height = 200,
		.texture = osakaTex
	};

	float rotValue = 0;
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
      		TranslateMessage(&msg);
    		DispatchMessage(&msg);
    	}

		rotValue += 0.1;

		ZFB_ProcessKeyboard();

		ZFB_PollEvent(&event);

		switch(event.type)
		{
			case ZFB_EVENT_KEYDOWN:
				{
					if(ZFB_IsKeyPressed(39))
					{
						ZFB_ApplyTorque(&playerEntity, 0.05);
					}
					if(ZFB_IsKeyPressed(38))
					{
						ZFB_ApplyForceLocal(&playerEntity, (ZFB_Vector2){0, -0.5});
					}
					if(ZFB_IsKeyPressed(40))
					{
						ZFB_ApplyForceLocal(&playerEntity, (ZFB_Vector2){0, 0.5});
					}
					if(ZFB_IsKeyPressed(37))
					{
						ZFB_ApplyTorque(&playerEntity, -0.05);
					}
					if(ZFB_IsKeyPressed(34))
					{
						dev.width += 100;
						dev.height += 100;
						ZFB_UpdateFB(&dev);
					}
					if(ZFB_IsKeyPressed(33))
					{
						dev.width -= 100;
						dev.height -= 100;
						ZFB_UpdateFB(&dev);
					}
					if(ZFB_IsKeyPressed(32))
					{
						ZFB_Entity bullet =
						{
							.physics =
							{
								.position = playerEntity.physics.position,
								.mass = 1,
								.gravity = false,
								.rotation = playerEntity.physics.rotation,
							},
							.width = 10,
							.height = 10,
						};
						bullets = realloc(bullets, sizeof(ZFB_Entity) * (bulletCount + 1));
						bullets[bulletCount] = bullet;
						bulletCount++;
					}
					break;
				}
		}

		ZFB_DrawBG(dev, NULL, bgTex);
		//ZFB_DrawBG(dev, &ZFB_Red, NULL);

		ZFB_SyncEntity(&player, playerEntity);

		ZFB_UpdatePhysics(&playerEntity, 1);

		for(int i = 0; i < bulletCount; i++)
		{
			ZFB_Rect bulletRect = {};
			ZFB_ApplyForceLocal(&bullets[i], (ZFB_Vector2){0, -0.5});
			ZFB_SyncEntity(&bulletRect, bullets[i]);
			ZFB_UpdatePhysics(&bullets[i], 1);
			ZFB_DrawRect(dev, bulletRect, &ZFB_Yellow);
		}

		osaka.rotation = rotValue;

		ZFB_DrawRect(dev, player, &ZFB_Red);
		ZFB_DrawRect(dev, osaka, NULL);

		ZFB_Present(dev);
		Sleep(16);
	}

	ZFB_EventShutdown();
	ZFB_FreeTextures();
	return 0;
}
