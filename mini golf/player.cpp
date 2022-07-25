#include "include/player.h"

bool player::is_mouse_on_the_ball(player ball, float mouse_x, float mouse_y){
	if(
			mouse_x >= ball.x && mouse_x <= ball.x + ball.texture.width
			&&
			mouse_y >= ball.y && mouse_y <= ball.y + ball.texture.height
	) return true;
	return false;
}
