#pragma bank 2
#include "StateGame.h"
#include "StateMap2.h"
#include "Keys.h"
UINT8 bank_STATE_GAME = 2;
UINT8 bank_STATE_MAP2 = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\map2.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

extern UINT8 n_sprite_types;
struct Sprite *playerState;
struct Sprite *cameraState;
UINT8 level = 1;

UINT8 collision_tiles[] = { 13, 1, 2, 3, 4, 5, 6, 7, 14, 15 ,16,17, 22, 23 };

void Start_STATE_GAME() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	playerState = SpriteManagerAdd(SPRITE_PLAYER, 88, (mapHeight << 3) - 40);
	cameraState = SpriteManagerAdd(SPRITE_CAMERA, playerState->x, playerState->y);
	scroll_target = playerState;

	//SpriteManagerAdd(SPRITE_EXPLOSION, 90, (mapHeight << 3) - 45);

	InitScrollTiles(0, 24, tiles, 3);
	if (level == 1) {
		InitScroll(mapWidth, mapHeight, map, collision_tiles, 0, 3);
	}
	else if (level == 2) {
		InitScroll(map2Width, map2Height, map2, collision_tiles, 0, 3);
	}
		
	SHOW_BKG;	

	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
}

extern INT8 speed;
INT8 screenShakeArray[8] = { -1,1,0,1,-1,-1,1,0 };
INT8 screenShakeAuxX= 0;
INT8 screenShakeAuxY = 0;
INT8 screenShakeTime = 0;
INT8 screenShakeIndexX = 0;
INT8 screenShakeIndexY = 7;

void Update_STATE_GAME() {

	/*
	if (KEY_PRESSED(J_B)) {
		screenShakeTime = 8;
	}
	*/
	
	cameraState->y = playerState->y + screenShakeAuxY;
	//cameraState->x = 100 + screenShakeAuxX;

	if (screenShakeTime > 0) {
		screenShakeTime--;

		scroll_target = cameraState;
				
		//screenShakeAuxX = screenShakeArray[screenShakeIndexX];
		screenShakeAuxY = screenShakeArray[screenShakeIndexY];

		/*screenShakeIndexX++;
		if (screenShakeIndexX > 7) {
			screenShakeIndexX = 0;
		}*/

		screenShakeIndexY--;
		if (screenShakeIndexY <= 0) {
			screenShakeIndexY = 7;
		}

		if (screenShakeTime <= 0) {
			screenShakeAuxX = 0;
			screenShakeAuxY = 0;
			scroll_target = playerState;
		}
	}

	//Condición final
	if (playerState->y < 2) {
		level++;
		if (level <= 2) {
			SetState(STATE_GAME);
		}
		else {
			SetState(STATE_SPLASH);
		}
		
	}/*
	if (KEY_PRESSED(J_START)) {
		level++;
		if (level <= 2) {
			SetState(STATE_GAME);
		}
	}*/
}