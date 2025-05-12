#include "ZFB.h"

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
	
	// Event
	ZFB_Event* event = {};
	ZFB_EventInit();

	// Background
	ZFB_Color bgColor = { 255, 0, 0 };

	// Textures
	ZFB_Texture* playerTex = ZFB_LoadTexture("spaceship.png");
	ZFB_Texture* bgTex = ZFB_LoadTexture("pointer.png");

	// Entities
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

	// Set terminal to raw mode
	ZFB_RawMode();
	while (true)
	{
		// Print the Debug info
		// CPU, MEM, PROCMEM
		ZFB_DInfo();
		
		// Keyboard schenanigans
		ZFB_ProcessKeyboard();

		// Read Events
		ZFB_PollEvent(event);

		switch(event->type)
		{
			case ZFB_EVENT_KEYDOWN:
				{
					printf("\r%d\n", event->data.key.key_code);
				}
		}

		// Rectangles
		ZFB_Rect player =
		{
			.position = playerEntity.physics.position,
			.width = playerEntity.width,
			.height = playerEntity.height,
			.texture = playerTex // NOTE: Can be NULL aswell
		};

		// Draw the Rects
		ZFB_DrawRect(dev, player, NULL);

		// Draw the Background
		ZFB_DrawBG(dev, &bgColor, bgTex);
	}
	ZFB_ExitRawMode();
	ZFB_FreeTextures();
	return 0;
}
