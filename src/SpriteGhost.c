#pragma bank 2
#include "SpriteGhost.h"
UINT8 bank_SPRITE_GHOST = 2;

#include "SpriteManager.h"

const UINT8 anim_ghost[] = { 1, 0 };

struct GhostCustomData {
	UINT8 timeDelayCounter;
	UINT8 timeDelay;
	UINT8 delayTimeDelaySign;
	INT8 ghostTimeDelaySign;
	INT8 ghostSpeed;
	INT8 ghostX;
	UINT8 ghostDelayX;
};

void Start_SPRITE_GHOST() {

	struct GhostCustomData* data = (struct GhostCustomData*)THIS->custom_data;
	data->timeDelayCounter = 0;
	data->timeDelay = 10;
	data->delayTimeDelaySign = 0;
	data->ghostTimeDelaySign = -1;
	data->ghostSpeed = 2;
	data->ghostDelayX = 2;

	if (THIS->x > 80) {
		data->ghostX = -1;
	}
	else {
		data->ghostX = 1;
	}
}

void Update_SPRITE_GHOST() {
	struct GhostCustomData* data = (struct GhostCustomData*)THIS->custom_data;

	SetSpriteAnim(THIS, anim_ghost, 1);

	if (data->timeDelayCounter > data->timeDelay) {
		THIS->y = THIS->y - data->ghostSpeed;
		if (data->delayTimeDelaySign > 5) {
			data->delayTimeDelaySign = 0;
			data->timeDelay += data->ghostTimeDelaySign;
			if (data->timeDelay == 0) {
				data->ghostTimeDelaySign = -data->ghostTimeDelaySign;
			}
			else if (data->timeDelay > 10) {
				data->ghostSpeed = -data->ghostSpeed;
				data->ghostTimeDelaySign = -data->ghostTimeDelaySign;
			}
		}	
		else {
			data->delayTimeDelaySign++;
		}
		data->timeDelayCounter = 0;
	}
	else {
		data->timeDelayCounter++;
		if (delta_time) {
			data->timeDelayCounter++;
		}
	}

	if (data->ghostDelayX > 1) {
		THIS->x = THIS->x + data->ghostX;
		data->ghostDelayX = 0;
	}
	else {
		data->ghostDelayX++;
	}
}

void Destroy_SPRITE_GHOST() {
}