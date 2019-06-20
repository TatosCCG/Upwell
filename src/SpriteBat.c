#pragma bank 2
#include "SpriteBat.h"
UINT8 bank_SPRITE_BAT = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 anim_bat[] = { 2, 0, 1 };

struct BatCustomData {
	UINT8 batDelayCounter;
	INT8 batspeedX;
	INT8 batspeedY;
	INT8 batDistanceX;

	UINT8 timeDelayX;
	UINT8 timeDelayY;
};


void Start_SPRITE_BAT() {
	struct BatCustomData* data = (struct BatCustomData*)THIS->custom_data;
	data->batDelayCounter = 0;
	data->batspeedX = 1;
	data->batspeedY = 1;
	data->batDistanceX = 0;
	data->timeDelayX = 0;
	data->timeDelayY = 0;

	THIS->coll_x = 0;
	THIS->coll_y = 5;
	THIS->coll_w = 16;
	THIS->coll_h = 8;
}

void Update_SPRITE_BAT() {
	struct BatCustomData* data = (struct BatCustomData*)THIS->custom_data;

	if (data->batspeedX < 0) {
		SPRITE_SET_VMIRROR(THIS);
	}
	else {
		SPRITE_UNSET_VMIRROR(THIS);
	}
	SetSpriteAnim(THIS, anim_bat, 10);

	if (data->batDelayCounter > 1) {
		THIS->x = THIS->x - data->batspeedX;
		data->batDelayCounter = 0;
		data->batDistanceX++;

		if (data->batDistanceX > 64){
			data->batspeedX = -data->batspeedX;
			data->batDistanceX = 0;
		}
		data->batDelayCounter = 0;
	}
	else {
		data->batDelayCounter++;
		if (delta_time) {
			data->batDelayCounter++;
		}
	}
}

void Destroy_SPRITE_BAT() {
}




















//#pragma bank 2
//#include "SpriteBat.h"
//UINT8 bank_SPRITE_BAT = 2;
//
//#include "SpriteManager.h"
//#include "ZGBMain.h"
//
//const UINT8 anim_bat[] = { 2, 0, 1 };
//
//UINT8 timeDelayX = 2;
//UINT8 timeDelayY = 5;
//UINT16 xStart = 0;
//UINT16 yStart = 0;
//INT8 batspeedX = 1;
//INT8 batspeedY = 1;
//INT8 batDistanceX = 0;
//
//void Start_SPRITE_BAT() {
//	xStart = THIS->x;
//	yStart = THIS->y;
//	batspeedX = -1;
//}
//


//void Update_SPRITE_BAT() {
//	struct BatCustomData* data = (struct BatCustomData*)THIS->custom_data;
//	//THIS->x = THIS->x + batspeedX;
//	//batDistanceX++;
//	//if (batDistanceX > (8 >> 3)) {
//	//	batspeedX = -batspeedX;
//	//}
//
//	if (data->batspeedX > 0) {
//		SPRITE_SET_VMIRROR(THIS);
//	}
//	else {
//		SPRITE_UNSET_VMIRROR(THIS);
//	}
//
//	SetSpriteAnim(THIS, anim_bat, 15);
//
//	//THIS->x = THIS->x + batspeedX;
//	//batDistanceX++;
//	//if (batDistanceX > (8 >> 3)) {
//	//	batspeedX = -batspeedX;
//	//}
//
//
//	//THIS->x = THIS->x + data->batspeedX;
//
//
//
//	//Movimiento horizontal
//	if (data->timeDelayX > 2) {
//		THIS->x = THIS->x - data->batspeedX;
//		data->timeDelayX = 0;
//	}
//	else {
//		data->timeDelayX++;
//		if (delta_time) {
//			data->timeDelayX++;
//		}
//	}
//
//	//Movimiento vertical
//	if (data->timeDelayY > 5) {
//		THIS->y = THIS->y - data->batspeedY;
//		data->batDistanceX++;
//		data->timeDelayY = 0;
//	}
//	else {
//		data->timeDelayY++;
//		if (delta_time) {
//			data->timeDelayY++;
//		}
//	}
//
//	
//	if (data->batDistanceX > (8 >> 3)) {
//		data->batDistanceX = 0;
//		data->batspeedX = -data->batspeedX;
//	}
//
//	//if (THIS->x < xStart - 32 || THIS->x > xStart + 32) {
//	//	data->batspeedX = -data->batspeedX;
//	//}
//	//if (THIS->y < yStart - 4 || THIS->y > yStart + 4) {
//	//	data->batspeedY = -data->batspeedY;
//	//}
//}
//
//void Destroy_SPRITE_BAT() {
//}