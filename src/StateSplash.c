#pragma bank 2
#include "StateSplash.h"
#include "Keys.h"
UINT8 bank_STATE_SPLASH = 2;

#include "..\res\src\splashTiles.h"
#include "..\res\src\splashMap.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

extern UINT8 n_sprite_types;

void Start_STATE_SPLASH() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	InitScrollTiles(0, 24, splashTiles, 3);
	InitScroll(splashMapWidth, splashMapHeight, splashMap, 0, 0, 3);	
	SHOW_BKG;	

	//PlayMusic(exo_start_mod_Data, 4, 0);
}

extern UINT8 level;

void Update_STATE_SPLASH() {
	
	if (KEY_PRESSED(J_START)) {
		level = 1;
		SetState(STATE_GAME);
	}
	
}