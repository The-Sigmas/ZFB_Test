#include "ZFB.h"
#include <math.h>

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
			.mass = 5,
			.gravity = false,
			.rotation = 0,
		},
		.width = 50,
		.height = 50,
	};	
	
	// Rectangles
	ZFB_Rect player = {};

	// Set terminal to raw mode
	ZFB_RawMode();
	bool quit = false;
	float rotation = 0;
	while (!quit)
	{
		// Print the Debug info
		// CPU, MEM, PROCMEM
		//ZFB_DInfo();

		rotation+=0.1;
		
		// Keyboard schenanigans
		ZFB_ProcessKeyboard();

		// Read Events
		ZFB_PollEvent(&event);

		switch(event.type)
		{
			case ZFB_EVENT_KEYDOWN:
				{
					if(ZFB_IsKeyPressed(1))
					{
						quit = true;
					}

					if(ZFB_IsKeyPressed(106))
					{
						ZFB_ApplyTorque(&playerEntity, 0.05);
					}
					if(ZFB_IsKeyPressed(105))
					{
						ZFB_ApplyTorque(&playerEntity, -0.05);
					}
					break;
				}
			case ZFB_EVENT_KEYUP:
				{
					break;	
				}
		}

		// Rectangles
		ZFB_SyncEntity(&player, &playerEntity);
		
		ZFB_Rect test =
		{
			.position = { dev.width/2, dev.height/2 },
			.width = 250,
			.height = 250,
			.rotation = rotation,
			.texture = testTex
		};

		ZFB_UpdatePhysics(&playerEntity, 1);

		// Draw the Background
		ZFB_DrawBG(dev, &bgColor, bgTex);
		
		// Draw the Rects
		ZFB_DrawRect(dev, player, NULL);
		ZFB_DrawRect(dev, test, NULL);
	}
	ZFB_ExitRawMode();
	ZFB_FreeTextures();
	return 0;
}
