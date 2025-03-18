#include "ZFB.h"
#include <unistd.h>

int main()
{
	ZFB_Texture* suntex;
	ZFB_InitKeyboard();
	ZFB_Device dev = { "/dev/fb0" };
	ZFB_InitFB(&dev);
	
	ZFB_Entity player = { .id = 0, .width = 150, .height = 150, .physics = {{700, 500},{0, 0},{0, 0}, 1, 0} };
	ZFB_Entity a = { .id = 10, .width = 250, .height = 250, .physics = {{1280, 0}, {0, 0}, {0, 0}, 1, 0} };
	ZFB_Entity sunEntity = { .id = 20, .width = 200, .height = 200, .physics = {{640, 400},{0, 0},{0, 0}, 5, 0} };
	ZFB_Entity ballEntity = { .id = 30, .width = 50, .height = 50, .physics = {{640, 400},{0, 0},{0, 0}, 5, 1} };
	ZFB_Vector2 aForce = {0, 0};
	ZFB_Vector2 sunForce = {0, 0};
	ZFB_Vector2 playerForce = {0, 0};
	ZFB_Vector2 ballForce = {0, 0};
	float dt = 1;

	ZFB_Texture* balltex = ZFB_LoadTexture("cringeculture.png");
	ZFB_Texture* tex = ZFB_LoadTexture("pointer.png");
	ZFB_Texture* spaceshiptex = ZFB_LoadTexture("spaceship.png");

	ZFB_DrawBG(dev, &ZFB_Red, NULL);
	
	ZFB_Rect rect = { a.physics.position.x, a.physics.position.y, a.width, a.height, tex };
	ZFB_Rect sun = { sunEntity.physics.position.x, sunEntity.physics.position.y, sunEntity.width, sunEntity.height, NULL };
	ZFB_Rect plr = { player.physics.position.x, player.physics.position.y, player.width, player.height, spaceshiptex };
  ZFB_Rect ball = { ballEntity.physics.position.x, ballEntity.physics.position.y, ballEntity.width, ballEntity.height, balltex };

	int quit = 0;
	int pauseflag = -1;
	while (!quit)
	{
		if (a.physics.position.y > player.physics.position.y)
		{
			aForce.y = -1;
		} else if (a.physics.position.y < player.physics.position.y)
		{
			aForce.y = 1;
		}
		if (a.physics.position.x > player.physics.position.x)
		{
			aForce.x = -1;
		} else if (a.physics.position.x < player.physics.position.x)
		{
			aForce.x = 1;
		}
		if (sunEntity.physics.position.y > player.physics.position.y)
		{
			sunForce.y = -1;
		} else if (sunEntity.physics.position.y < player.physics.position.y)
		{
			sunForce.y = 1;
		}
		if (sunEntity.physics.position.x > player.physics.position.x)
		{
			sunForce.x = -1;
		} else if (sunEntity.physics.position.x < player.physics.position.x)
		{
			sunForce.x = 1;
		}

    if (ballEntity.physics.position.x > 800-50)
		{
			ballForce.y = -1;
		}

		switch (ZFB_KeyPressed())
		{
			case 114:
				aForce.y = 1;
				sunForce.y = -1;
				break;
			case 101:
				aForce.x = 1;
				sunForce.x = -1;
				break;
			case 97:
				player.physics.acceleration.x -= 2.5;
				break;
			case 100:
				player.physics.acceleration.x += 2.5;
				break;
			case 119:
				player.physics.acceleration.y -= 2.5;
				break;
			case 115:
				player.physics.acceleration.y += 2.5;
				break;
			case 107:
				if (sun.texture)
				{
					free(suntex->path);
					free(suntex);
					sun.texture = NULL;
				}
				break;
			case 113:
				quit = 1;
				break;
			case 112:
				pauseflag *= -1;
				break;
			default:
				break;
		}
		if (pauseflag == 1)
		{
			continue;
		}

		if (player.physics.position.y >= 800)
		{
			player.physics.acceleration.y -= 5;
		}
		update_physics(&a, dt);
		update_physics(&sunEntity, dt);
		update_physics(&ballEntity, dt);
		update_physics(&player, dt);
		apply_force(&a, aForce);
		apply_force(&ballEntity, ballForce);
		apply_force(&player, playerForce);
		apply_force(&sunEntity, sunForce);

		rect.x = a.physics.position.x;
		rect.y = a.physics.position.y;
		sun.x = sunEntity.physics.position.x;
		sun.y = sunEntity.physics.position.y;
		plr.x = player.physics.position.x;
		plr.y = player.physics.position.y;
		ball.x = ballEntity.physics.position.x;
		ball.y = ballEntity.physics.position.y;

		ZFB_DrawBG(dev, &ZFB_Red, NULL);
		ZFB_DrawRect(dev, sun, &ZFB_Yellow);
		ZFB_DrawRect(dev, rect, NULL);
		ZFB_DrawRect(dev, plr, NULL);
		ZFB_DrawRect(dev, ball, NULL);
		
		if (check_collision(a, sunEntity))
		{
			if (!sun.texture)
			{
				suntex = ZFB_LoadTexture("textureexample.png");
				sun.texture = suntex;
			}
			//quit = 1;
		}

		//Debug
		printf("\rX: %d, Y:%d\n", plr.x, plr.y);
		ZFB_DInfo();
		printf("\e[A");

		usleep(33 * 1000); //30fps
	}
	system("clear");
	printf("Simulation Done\n\r");
	ZFB_CloseKeyboard();
	ZFB_Exit(&dev);
	free(tex->path);
	//free(bgtex->path);
	//free(bgtex);
	free(tex);
}
