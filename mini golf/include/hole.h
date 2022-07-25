#ifndef HOLE_H
#define HOLE_H

#include "raylib.h"
#include "player.h"

typedef class HOLE{
public:
	bool hole_collision(HOLE hole, float ball_x, float ball_y);

	bool check_hole_coll(HOLE hole, player ball, float dir_x, float dir_y);

	Texture2D texture;
	float x, y, cent_x, cent_y;
}HOLE;

#endif
