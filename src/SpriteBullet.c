#pragma bank 2
#include "SpriteBullet.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

const UINT8 anim_bulletExp[] = { 1, 0 };
const UINT8 anim_bullet[] = { 2, 1, 2};

UINT8 timeExp = 0;
UINT8 speed = 1;

void Start_SPRITE_BULLET() {
	UINT8 timeExp = 0;
	SetSpriteAnim(THIS, anim_bulletExp, 30);
	speed = 1;
}

void Update_SPRITE_BULLET() {
	if (TranslateSprite(THIS, 0, speed) != 0) {
		timeExp = 0;
		SpriteManagerRemoveSprite(THIS);
	}

	if (timeExp > 6) {
		SetSpriteAnim(THIS, anim_bullet, 15);
		speed = 5;
	}
	else {
		timeExp++;
	}	
}

void Destroy_SPRITE_BULLET() {
}