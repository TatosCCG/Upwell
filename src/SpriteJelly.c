#pragma bank 2
#include "SpriteJelly.h"
UINT8 bank_SPRITE_JELLY = 2;

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 anim_jelly[] = { 2, 0, 1 };


struct JellyCustomData {
	UINT8 timeDelayCounter;
	UINT8 timeDelay;
	INT8 timeDelaySign;
	INT8 jellySpeed;
	UINT16 startY;
};



void Start_SPRITE_JELLY() {
	struct JellyCustomData* data = (struct JellyCustomData*)THIS->custom_data;
	data->timeDelayCounter = 0;
	data->timeDelay = 11;
	data->timeDelaySign = -1;
	data->jellySpeed = 1;
	data->startY = THIS->y;

	THIS->coll_x = 0;
	THIS->coll_y = 4;
	THIS->coll_w = 16;
	THIS->coll_h = 10;
}

void Update_SPRITE_JELLY() {

	struct JellyCustomData* data = (struct JellyCustomData*)THIS->custom_data;
	SetSpriteAnim(THIS, anim_jelly, 8);

	if (data->timeDelayCounter > data->timeDelay) {
		THIS->y = THIS->y - data->jellySpeed;
		data->timeDelay += data->timeDelaySign;
		if (data->timeDelay == 0) {
			data->timeDelaySign = -data->timeDelaySign;
		}
		else if (data->timeDelay > 12) {
			data->jellySpeed = -data->jellySpeed;
			data->timeDelaySign = -data->timeDelaySign;
		}
		data->timeDelayCounter = 0;
	}
	else {
		data->timeDelayCounter++;
		if (delta_time) {
			data->timeDelayCounter++;
		}
	}	
}

void Destroy_SPRITE_JELLY() {
}