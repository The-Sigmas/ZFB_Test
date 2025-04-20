#include "ZFB.h"
#include <unistd.h>

ZFB_Device dev = { "/dev/fb0" };

ZFB_Entity player = {};
ZFB_Color bgColor = { 255, 0, 0 };

int main()
{
	ZFB_InitFB(&dev);
	while (1)
	{
		ZFB_DrawBG(dev, &bgColor, NULL);
	}
	return 0;
}
