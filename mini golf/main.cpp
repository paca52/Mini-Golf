#include "include/raylib.h"
#include "include/hole.h"
#include "include/player.h"
#include <iterator>
#include <vector>
#include <math.h>

#define delta_speed 0.1f
#define ball_mass 0.05f

typedef struct WALL{
	Texture2D texture;
	float x, y;

}WALL;

double get_distance(float x1, float y1, float x2, float y2){
	return double( sqrt( (y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1) ) );
}

void wall_collision(WALL wall, float ball_x, float ball_y, float& dir){
		DrawCircle(ball_x, ball_y, 2.0f, RED);
		
		if(ball_x >= wall.x && ball_x <= wall.x + wall.texture.width
				&&
		   ball_y >= wall.y && ball_y <= wall.y + wall.texture. height)
			dir = -dir;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 450;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "balls game");

	player ball = {
		.texture = LoadTexture("C:/Users/pavla/Desktop/raylib_test/textures/ball.png"),
		.x = (float)screenWidth / 2 - (float)ball.texture.width / 2,
	    .y = (float)screenHeight / 2 - (float)ball.texture.height / 2,
	    .radius = 4.0f,
	    .velocity = 0.0f
	};

	Texture2D back = LoadTexture("textures/back.png"); // background
	HOLE hole = {
		.texture = LoadTexture("textures/hole.png"),
		.x = (float)screenWidth / 2 - (float)hole.texture.width / 2,
		.y = 100,
		.cent_x = hole.x + (float)hole.texture.width / 2,
		.cent_y = hole.y + (float)hole.texture.height / 2
	};

	std::vector<WALL> wall;
	{
		WALL wall_tmp = {.texture = LoadTexture("textures/brick.png"), .x = 133.0f, .y = 252.0f};

		wall.push_back(wall_tmp);

		wall_tmp.x = 33;
		wall_tmp.y = 450;

		wall.push_back(wall_tmp);
	}

	float mouse_x = 0, mouse_y = 0;
	double distance = 0;

	//za odbijanje od zid
	float dir_x = 0, dir_y = 0;
	bool player_can_shoot = true, player_want_to_shoot = false;

	//levels and shit
	bool win = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

		if(player_can_shoot == true && ball.is_mouse_on_the_ball(ball, GetMouseX(), GetMouseY()) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true)
			player_want_to_shoot = true;

		if(player_want_to_shoot == true && player_can_shoot == true && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) == true){
			mouse_x = GetMouseX();
			mouse_y = GetMouseY();

			distance = get_distance(mouse_x, mouse_y, ball.x + (float)ball.texture.width/2, ball.y + (float)ball.texture.height/2);

			// bruh wtf
			ball.velocity = distance * ball_mass * 2;

			dir_x = sin(( ball.x + (float)ball.texture.width/2 - mouse_x ) / distance);
			dir_y = sin(( ball.y + (float)ball.texture.height/2 - mouse_y ) / distance);

			player_can_shoot = false;
			player_want_to_shoot = false;

		}

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
			DrawTexture(back, 0, 0, RAYWHITE);
			if(hole.check_hole_coll(hole, ball, dir_x, dir_y) == true)
				win = true;
			
			if(win)
				DrawText("YOU WON", screenWidth/2 - 10*7, screenHeight/2, 10, RED);
			else{

				DrawTexture(hole.texture, hole.x, hole.y, RAYWHITE);
				DrawTexture(ball.texture, ball.x, ball.y, RAYWHITE);

				//debugging
				DrawText(TextFormat("dir_x = %f\ndir_y = %f", dir_x, dir_y), 30, 30, 20, BLUE);

				for(WALL tmp : wall){
					DrawTexture(tmp.texture, tmp.x, tmp.y, RAYWHITE);
				}

				if(ball.velocity > 0){

					if(ball.x <= 0 || ball.x + ball.texture.width >= screenWidth) // ivica zida
						dir_x = -dir_x;

					if(ball.y <= 0 || ball.y + ball.texture.height >= screenHeight)
						dir_y = -dir_y;

					for(WALL tmp : wall){

						DrawCircle(ball.x, ball.y, 2.0f, GREEN);
						
						// provera da li je u sledecem freju x-osa usla u neki zid, ako jeste onda loptici obrnem smer
						wall_collision(
								tmp, 
								(dir_x >= 0) * ( ball.x + ball.velocity * dir_x + ball.texture.width) + (dir_x < 0) * (ball.x + ball.velocity * dir_x),
								ball.y + (float)ball.texture.height / 2,
								dir_x
						);

						//same shit samo za y-osu
						wall_collision(
								tmp,
								ball.x + (float)ball.texture.width / 2,
								(dir_y >= 0) * ( ball.y + ball.velocity * dir_y + ball.texture.height) + (dir_y < 0) * ( ball.y + ball.velocity * dir_y ), 
								dir_y
						);

					}


					ball.x += ball.velocity * dir_x;
					ball.y += ball.velocity * dir_y;

					// here too
					ball.velocity -= delta_speed;
					if(ball.velocity < 0)
						ball.velocity = 0;
				}
				else
					player_can_shoot = true;
				//DrawText(TextFormat("DISTANCE: %lf\nmouse_x = %f\nmouse_y = %f\nball vel = %lf\ndir_x = %lf\ndir_y = %lf\nwid: %f", distance, mouse_x, mouse_y, ball.velocity, dir_x, dir_y, wall[0].x + wall[0].texture.width), 10, 10, 30, BLUE);
		}

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
