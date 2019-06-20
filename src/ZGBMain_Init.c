#pragma bank 1
#include "ZGBMain.h"
UINT8 init_bank = 1;


#include "StateGame.h"
#include "StateMap2.h"
#include "StateSplash.h"

#include "SpritePlayer.h"
#include "SpriteExplosion.h"
#include "SpriteBullet.h"
#include "SpriteJelly.h"
#include "SpriteBat.h"
#include "SpriteGhost.h"
#include "SpriteSkull.h"
#include "SpriteCamera.h"

#include "../res/src/player.h"
#include "../res/src/explosion.h"
#include "../res/src/bullet.h"
#include "../res/src/jelly.h"
#include "../res/src/bat.h"
#include "../res/src/ghost.h"
#include "../res/src/skull.h"
#include "../res/src/cameraAnchor.h"

UINT8 next_state = STATE_SPLASH;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_SPLASH);
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PLAYER, player, 3, FRAME_16x16, 9);
	INIT_SPRITE(SPRITE_EXPLOSION, explosion, 3, FRAME_16x16, 4);
	INIT_SPRITE(SPRITE_BULLET, bullet, 3, FRAME_16x16, 3);
	INIT_SPRITE(SPRITE_JELLY, jelly, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_BAT, bat, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_GHOST, ghost, 3, FRAME_16x16, 1);
	INIT_SPRITE(SPRITE_SKULL, skull, 3, FRAME_16x16, 2);
	INIT_SPRITE(SPRITE_CAMERA, camera, 3, FRAME_16x16, 1);
}