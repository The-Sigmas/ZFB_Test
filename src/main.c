#include "ZFB.h"
#include <math.h>
#include <unistd.h>

/*
 * This examples shows you how to set up a simple
 * project using the ZFB library.
 *
 * NOTE:
 * - Focused on Linux
 *   - for Windows see the `windows` branch
 * - Uses the kernel framebuffer `/dev/fb0`
 *   - for DRM see the `DRM` branch, TODO: Implement DRM as a whole first
 * - Expects to be run over a TTY device
 * - Expects the tty to have raw mode support
 */

int main()
{
	// Create the Device and set the Parameters
	ZFB_Device dev = { "/dev/fb0" };
	// Initialize the Device
	ZFB_InitFB(&dev);
	
	ZFB_InitInput();

	// Event
	ZFB_Event event = {};
	ZFB_EventInit();

	// Background
	ZFB_Color bgColor = { 255, 0, 0 };

	// Textures
	ZFB_Texture* playerTex = ZFB_LoadTexture("spaceship.png");
	ZFB_Texture* bgTex = ZFB_LoadTexture("pointer.png");
	ZFB_Texture* testTex = ZFB_LoadTexture("textureexample.png");

	// Entities
	ZFB_Entity playerEntity =
	{
		.id = 0,
		.physics = // NOTE: you can also define physics seperately, ZFB_PhysicsBody playerPhysics = {...};
		{
			.position = { dev.width/2, dev.height/2 }, // ZFB_Vector2
			.mass = 3,
			.gravity = false,
			.rotation = 0,
		},
		.width = 50,
		.height = 50,
	};
	ZFB_Entity testEntity =
	{
		.physics =
		{
			.position = { dev.width/2, dev.height/2 },
			.mass = 1,
			.gravity = true,
			.rotation = 0,
		},
		.width = 200,
		.height = 200,
	};
	
	// Rectangles
	ZFB_Rect player = {.texture = playerTex};
	ZFB_Rect test = {.texture = testTex};

	// Set terminal to raw mode
	ZFB_RawMode();
	bool quit = false;
	float rotation = 0;
	while (!quit)
	{
		// Print the Debug info
		// CPU, MEM, PROCMEM
		// ZFB_DInfo();

		rotation+=0.1;
		
		// Keyboard schenanigans
		ZFB_ProcessKeyboard();

		// Read Events
		ZFB_PollEvent(&event);

		if(ZFB_IsKeyPressed(KEY_ESC))
		{
			quit = true;
		}
		if(ZFB_IsKeyPressed(KEY_RIGHT))
		{
			ZFB_ApplyTorque(&playerEntity, 0.02);
		}
		if(ZFB_IsKeyPressed(KEY_LEFT))
		{
			ZFB_ApplyTorque(&playerEntity, -0.02);
		}
		if(ZFB_IsKeyPressed(KEY_UP))
		{
			ZFB_ApplyForceLocal(&playerEntity, (ZFB_Vector2){0, -0.5});
		}
		if(ZFB_IsKeyPressed(KEY_DOWN))
		{
			ZFB_ApplyForceLocal(&playerEntity, (ZFB_Vector2){0, 0.5});
		}

		testEntity.physics.rotation = rotation;

		// Rectangles
		ZFB_SyncEntity(&player, playerEntity);
		ZFB_SyncEntity(&test, testEntity);

		ZFB_UpdatePhysics(&playerEntity, 1);
		ZFB_UpdatePhysics(&testEntity, 1);

		// Draw the Background
		ZFB_DrawBG(dev, &bgColor, bgTex);
		
		// Draw the Rects
		ZFB_DrawRect(dev, player, NULL);
		ZFB_DrawRect(dev, test, NULL);

		usleep(16000);
	}
	ZFB_ExitRawMode();
	ZFB_FreeTextures();
	return 0;
}
