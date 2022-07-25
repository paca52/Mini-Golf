#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef class player{
public:
	bool is_mouse_on_the_ball(player ball, float mouse_x, float mouse_y);

	Texture2D texture;
	float x, y;
	float radius;
	double velocity;

}player;

#endif // PLAYER_H
