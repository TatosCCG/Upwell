#pragma bank 2
#include "SpriteSkull.h"
UINT8 bank_SPRITE_SKULL = 2;

#include "SpriteManager.h"

const UINT8 anim_skull[] = { 2, 0, 1 };


void Start_SPRITE_SKULL() {
	
}

void Update_SPRITE_SKULL() {
	SetSpriteAnim(THIS, anim_skull, 2);
}

void Destroy_SPRITE_SKULL() {
}