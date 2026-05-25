#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int cpu_score = 0;

enum GameState {
    MENU,
    PLAYING,
    PAUSED
};

GameState current_state = MENU;
int main_menu_selection = 0;
int pause_menu_selection = 0;

class Ball{
    public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth()) // CPU Wins
        {
            cpu_score++;
            ResetBall();
        } 

        if(x - radius <= 0)
        {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }


    
};

class Paddle {
    protected:

    void LimitMovement()
    {
        if(y <= 0) {
            y = 0;
        }
        if(y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

    public:
    float x,y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() {
        if(IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }

        LimitMovement();
    }
};


class CpuPaddle: public Paddle{
    public:

    void Update(int ball_y) {
        if(y + height/2 > ball_y)
        {
            y = y - speed;
        }
        if(y + height/2 < ball_y)
        {
            y = y + speed;
        }
        LimitMovement();
    }
};

/*
class CpuPaddle: public Paddle{
    public:

    void Update() {
        if(IsKeyDown(KEY_W)) {
            y = y - speed;
        }
        if(IsKeyDown(KEY_S)) {
            y = y + speed;
        }

        LimitMovement();
    }
};
*/

Ball ball;
Paddle player;
CpuPaddle cpu;

void DrawMainMenu() {
    ClearBackground(DarkGreen);
    DrawRectangle(0, 0, GetScreenWidth()/2, GetScreenHeight(), Green);
    
    // Title
    DrawText("PONG CLASSIC", GetScreenWidth()/2 - MeasureText("PONG CLASSIC", 80)/2, 150, 80, WHITE);
    
    // Menu Options
    const char* menu_options[] = {"START GAME", "QUIT"};
    for(int i = 0; i < 2; i++) {
        Color color = (i == main_menu_selection) ? Yellow : WHITE;
        DrawText(menu_options[i], GetScreenWidth()/2 - MeasureText(menu_options[i], 40)/2, 350 + i * 80, 40, color);
    }
    
    DrawText("Use UP/DOWN arrows to navigate, ENTER to select", GetScreenWidth()/2 - MeasureText("Use UP/DOWN arrows to navigate, ENTER to select", 20)/2, GetScreenHeight() - 50, 20, LightGreen);
    DrawText("Press P during gameplay to pause", GetScreenWidth()/2 - MeasureText("Press P during gameplay to pause", 20)/2, GetScreenHeight() - 25, 20, LightGreen);
}

void DrawPauseMenu() {
    // Draw semi-transparent overlay
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 150});
    
    // Pause Title
    DrawText("PAUSED", GetScreenWidth()/2 - MeasureText("PAUSED", 80)/2, 150, 80, WHITE);
    
    // Menu Options
    const char* menu_options[] = {"RESUME", "RESTART", "QUIT TO MENU"};
    for(int i = 0; i < 3; i++) {
        Color color = (i == pause_menu_selection) ? Yellow : WHITE;
        DrawText(menu_options[i], GetScreenWidth()/2 - MeasureText(menu_options[i], 40)/2, 300 + i * 80, 40, color);
    }
    
    DrawText("Use UP/DOWN arrows to navigate, ENTER to select", GetScreenWidth()/2 - MeasureText("Use UP/DOWN arrows to navigate, ENTER to select", 20)/2, GetScreenHeight() - 50, 20, LightGreen);
}

void HandleMainMenuInput() {
    if(IsKeyPressed(KEY_DOWN)) {
        main_menu_selection = (main_menu_selection + 1) % 2;
    }
    if(IsKeyPressed(KEY_UP)) {
        main_menu_selection = (main_menu_selection - 1 + 2) % 2;
    }
    if(IsKeyPressed(KEY_ENTER)) {
        if(main_menu_selection == 0) {
            current_state = PLAYING;
            player_score = 0;
            cpu_score = 0;
        } else if(main_menu_selection == 1) {
            CloseWindow();
        }
    }
}

void HandlePauseMenuInput() {
    if(IsKeyPressed(KEY_DOWN)) {
        pause_menu_selection = (pause_menu_selection + 1) % 3;
    }
    if(IsKeyPressed(KEY_UP)) {
        pause_menu_selection = (pause_menu_selection - 1 + 3) % 3;
    }
    if(IsKeyPressed(KEY_ENTER)) {
        if(pause_menu_selection == 0) {
            current_state = PLAYING;
        } else if(pause_menu_selection == 1) {
            current_state = PLAYING;
            player_score = 0;
            cpu_score = 0;
            ball.ResetBall();
        } else if(pause_menu_selection == 2) {
            current_state = MENU;
        }
    }
}

int main () 
{
    cout << "Starting The Game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "PingPong Goes BRRRRRRR!");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width -10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if(current_state == MENU) {
            HandleMainMenuInput();
            DrawMainMenu();
        }
        else if(current_state == PLAYING) {
            // Check for pause
            if(IsKeyPressed(KEY_P)) {
                current_state = PAUSED;
                pause_menu_selection = 0;
            }

            //Updating
            ball.Update();
            player.Update();
            cpu.Update(ball.y);

            //Check Collision
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.speed_x *= -1;
            }

            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.speed_x *= -1;
            }

            //Drawing
            ClearBackground(DarkGreen);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
            DrawCircle(screen_width/2, screen_height/2, 150, LightGreen);
            DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

            ball.draw();
            cpu.Draw();
            player.Draw();
            DrawText(TextFormat("%i",cpu_score), screen_width/4 -20, 20, 80, WHITE);
            DrawText(TextFormat("%i",player_score), 3 * screen_width/4 -20, 20, 80, WHITE);
        }
        else if(current_state == PAUSED) {
            HandlePauseMenuInput();
            DrawPauseMenu();
        }

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
} 