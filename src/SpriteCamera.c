#pragma bank 2
#include "SpriteCamera.h"
UINT8 bank_SPRITE_CAMERA = 2;

#include "SpriteManager.h"

const UINT8 anim_camera[] = { 1, 0 };

void Start_SPRITE_CAMERA() {
}

void Update_SPRITE_CAMERA() {
		SetSpriteAnim(THIS, anim_camera, 5);
}

void Destroy_SPRITE_CAMERA() {
}