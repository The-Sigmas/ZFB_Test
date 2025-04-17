#include "ZFB.h"
#include <unistd.h>

ZFB_Device dev = { "/dev/fb0" };

ZFB_Entity player = {};

int main()
{
	ZFB_InitFB(&dev);
	while (true)
	{
		ZFB_DrawBG(dev, );
	}
	return 0;
}
