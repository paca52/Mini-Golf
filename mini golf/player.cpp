#include "include/player.h"

bool player::is_mouse_on_the_ball(player ball, float mouse_x, float mouse_y){
	if(
		mouse_x >= ball.x && mouse_x <= ball.x + ball.texture.width
		&&
		mouse_y >= ball.y && mouse_y <= ball.y + ball.texture.height
	) return true;
	return false;
}

void player::reset_position(player &ball, int screenWidth, int screenHeight){
	ball.x = (float)screenWidth / 2 - (float)ball.texture.width / 2;
	ball.y = (float)screenHeight / 2 - (float)ball.texture.height / 2;
	ball.velocity = 0.0f;
}

player::player(int screenHeight, int screenWidth){
	texture = LoadTexture("textures/ball.png");
	radius = 4.0f;
	x = (float)screenWidth / 2 - (float)texture.width / 2;
	y = (float)screenHeight / 2 - (float)texture.height / 2;
	velocity = 0.0f;
}
