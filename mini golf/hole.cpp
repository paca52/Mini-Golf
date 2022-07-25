#include "include/raylib.h"
#include "include/hole.h"

bool HOLE::hole_collision(HOLE hole, float ball_x, float ball_y){
	DrawCircle(ball_x, ball_y, 2.0f, RED);
	
	if(ball_x >= hole.x && ball_x <= hole.x + hole.texture.width
			&&
	   ball_y >= hole.y && ball_y <= hole.y + hole.texture. height)
		return true;
	return false;
}

bool HOLE::check_hole_coll(HOLE hole, player ball, float dir_x, float dir_y){
	return
		hole_collision(
				hole, 
				(dir_x >= 0) * ( ball.x + ball.velocity * dir_x + ball.texture.width) + (dir_x < 0) * (ball.x + ball.velocity * dir_x),
				ball.y + (float)ball.texture.height / 2
		) == true
		||
		hole_collision(
				hole,
				ball.x + (float)ball.texture.width / 2,
				(dir_y >= 0) * ( ball.y + ball.velocity * dir_y + ball.texture.height) + (dir_y < 0) * ( ball.y + ball.velocity * dir_y )
		) == true;
}

