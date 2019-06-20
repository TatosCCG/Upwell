#pragma bank 2
#include "Keys.h"
#include "SpritePlayer.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
UINT8 bank_SPRITE_PLAYER = 2;

const UINT8 anim_idle[] = { 1, 0 };
const UINT8 anim_hey[] = { 2, 1, 2 };
const UINT8 anim_jump[] = { 1, 3 };
const UINT8 anim_air[] = { 1, 4 };
const UINT8 anim_falling[] = { 1, 5 };
const UINT8 anim_walk[] = { 3, 6, 8, 7 };

UINT8 gravity = 1;
INT8 speed = 0;
UINT8 jumpStrength = 10;
UINT8 gravityDelay = 7;
UINT8 isJumping = 0;
UINT8 airAnimDelay = 0;
UINT8 landingAnimDelay = 0;
UINT8 bulletsMaxAmount = 5;
UINT8 bulletsShooted = 0;
UINT8 bulletPower = 2;
UINT8 bulletCooldown = 8;
UINT8 hasLanded = 0;

UINT16 jumpStartY = 0;

extern INT8 screenShakeTime;

UINT16 heyTime = 0;


void Start_SPRITE_PLAYER() {	
	THIS->coll_x = 2;
	THIS->coll_y = 1;
	THIS->coll_w = 12;
	THIS->coll_h = 15;

	speed = 0;
}

void UpdateOnAir() {

	hasLanded = 0;

	//aplico la gravedad a la velocidad cada "gravityDelay"
	if (speed > -4) {
		gravityDelay -= 1;
		if (gravityDelay == 0) {
			speed -= gravity;
			gravityDelay = 7;
		}
	}

	//Chequeo si toca
	if (TranslateSprite(THIS, 0, -speed) != 0) {
		//Se ha dado un cosco
		if (speed > 0) {			
			speed = 0;
		}

		//Ha caido sobre algo
		if (speed < 0) {
			PlayFx(CHANNEL_1, 30, 0x20, 0x41, 0x43, 0x32, 0x85);
			SetSpriteAnim(THIS, anim_jump, 15);
			isJumping = 0;
			speed = 0;
			gravityDelay = 7;
			landingAnimDelay = 0;
			bulletsShooted = 0;
		}		
	}
	else
	{
		//Chequeamos si esta cayendo
		if (speed <= 0) {
			SetSpriteAnim(THIS, anim_falling, 15);
			//scroll_target = 0;

			//Disparar
			if (KEY_PRESSED(J_A)) {
				if (bulletCooldown >= 8 && bulletsShooted<bulletsMaxAmount) {
					PlayFx(CHANNEL_4, 30, 0x0A, 0x44, 0x7B, 0xC0);
					screenShakeTime = 4;
					speed += bulletPower;
					airAnimDelay = 0;
					bulletCooldown = 0;
					bulletsShooted++;
					//SpriteManagerAdd(SPRITE_EXPLOSION, THIS->x , THIS->y + 8 + speed);
					SpriteManagerAdd(SPRITE_BULLET, THIS->x, THIS->y + 8 + speed);
				}
				else {
					bulletCooldown++;
				}
			}
		}/*
		else {
			scroll_target = THIS;
		}*/
	}
}

void Jump() {
	SetSpriteAnim(THIS, anim_air, 15);
	isJumping = 1;
	speed = 4;
	TranslateSprite(THIS, 0, -speed);
	airAnimDelay = 0;
	bulletsShooted = 0;
	jumpStartY = THIS->y;
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;
	
	//Está en el suelo
	if(isJumping == 0){
		if (KEY_PRESSED(J_A)) {
			isJumping = 2;					
			SetSpriteAnim(THIS, anim_jump, 15);
			airAnimDelay = 0;
		}
		else {
			if (TranslateSprite(THIS, 0, 1) == 0) {
				isJumping = 1;
			}

			//Ponemos el sprite de idle despues de caer			
			if (landingAnimDelay > 6 && hasLanded == 1) {
				SetSpriteAnim(THIS, anim_idle, 15);
				hasLanded = 0;
			}
			else {
				landingAnimDelay++;
			}			
		}

		if (KEY_PRESSED(J_RIGHT)) {
			SetSpriteAnim(THIS, anim_walk, 10);
		}
		if (KEY_PRESSED(J_LEFT)) {
			SetSpriteAnim(THIS, anim_walk, 10);
		}

		
		if (keys == 0) {
			//To-do: Animacion idle
			if (heyTime == 0) {
				SetSpriteAnim(THIS, anim_idle, 15);
			}
			heyTime++;
			if (heyTime > 200) {
				SetSpriteAnim(THIS, anim_hey, 15);
			}
		}
		else {
			heyTime = 0;
		}
	}
	//En el aire
	else if(isJumping == 1){		
		UpdateOnAir();
		if (delta_time) {
			UpdateOnAir();
		}		
	}

	//Preparando el salto
	else if (isJumping == 2) {
		//Saltamos
		if (airAnimDelay > 6) {
			Jump();
			/*SetSpriteAnim(THIS, anim_air, 15);
			isJumping = 1;
			speed = 4;
			TranslateSprite(THIS, 0, -speed);			
			airAnimDelay = 0;*/
		}
		else {
			airAnimDelay++;
		}

		////Comprobamos si está cayendo por debajo de la plataforma desde la que salto
		//if (THIS->y < jumpStartY + 64) {
		//	scroll_target = 0;
		//}
	}

	//No saltando
	if (isJumping != 2) {
		if (KEY_PRESSED(J_RIGHT)) {
			TranslateSprite(THIS, 2 << delta_time, 0);
			SPRITE_UNSET_VMIRROR(THIS);
			//SetSpriteAnim(THIS, anim_idle, 15);
		}
		if (KEY_PRESSED(J_LEFT)) {
			TranslateSprite(THIS, -2 << delta_time, 0);
			SPRITE_SET_VMIRROR(THIS);
			//SetSpriteAnim(THIS, anim_idle, 15);
		}
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SPRITE_JELLY || spr->type == SPRITE_BAT || spr->type == SPRITE_GHOST) {
			if (CheckCollision(THIS, spr)) {				
				if (speed <= 0 && isJumping == 1) {
					//screenShakeTime = 3;
					PlayFx(CHANNEL_1, 30, 0x00, 0x81, 0x64, 0x64, 0x80);
					Jump();
					SpriteManagerRemoveSprite(spr);
				}
				else if (isJumping == 0 && (THIS->y -16) > spr->y) {
					PlayFx(CHANNEL_1, 30, 0x00, 0x81, 0x64, 0x64, 0x80);
					Jump();
					SpriteManagerRemoveSprite(spr);
				}
				else {
					//PlayFx(CHANNEL_4, 60, 0x0A, 0x76, 0x62, 0x80);
					screenShakeTime = 6;
					SetState(STATE_GAME);
				}
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
	//SetState(STATE_GAME);
}

