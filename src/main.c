#include "ZFB.h"

int main()
{
	// Create the Device and set the Parameters
	ZFB_Device dev = { "/dev/fb0" };
	// Initialize the Device
	ZFB_InitFB(&dev);
	
	// Background
	ZFB_Color bgColor = { 255, 0, 0 };

	// Setup the player
	ZFB_Entity player = {};

	// Set terminal to raw mode
	ZFB_RawMode();
	while (1)
	{
		// Print the Debug info
		// CPU, MEM, PROCMEM
		ZFB_DInfo();
		


		// Draw the Background
		ZFB_DrawBG(dev, &bgColor, NULL);
	}
	ZFB_ExitRawMode();
	return 0;
}
