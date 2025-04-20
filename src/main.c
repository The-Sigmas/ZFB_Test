#include "ZFB.h"
#include <unistd.h>

ZFB_Device dev = { "/dev/fb0" };

ZFB_Entity player = {};
ZFB_Color* color = { 255, 0, 0 };

int main()
{
	ZFB_InitFB(&dev);
	while (true)
	{
		ZFB_DrawBG(dev, color, NULL);
	}
	return 0;
}
