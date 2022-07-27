#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef class player{
public:
	player(int screenHeight, int screenWidth);
	bool is_mouse_on_the_ball(player ball, float mouse_x, float mouse_y);
	void reset_position(player &ball, int screenWidth, int screenHeight);

	Texture2D texture;
	float x, y;
	float radius;
	double velocity;

}player;

#endif // PLAYER_H
