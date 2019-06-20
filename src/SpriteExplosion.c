#pragma bank 2
#include "SpriteExplosion.h"
UINT8 bank_SPRITE_EXPLOSION = 2;

#include "SpriteManager.h"

const UINT8 anim_explode[] = { 4, 0, 1, 2, 3 };
UINT8 lifeTime = 0;

void Start_SPRITE_EXPLOSION() {
}

void Update_SPRITE_EXPLOSION() {
	SetSpriteAnim(THIS, anim_explode, 15);
	if (THIS->current_frame == 3) {
		SpriteManagerRemoveSprite(THIS);
	}
	else {
		lifeTime++;
	}
	
}

void Destroy_SPRITE_EXPLOSION() {
}