#include <iostream>
#include <vector>
#include <cmath>

#include "raylib.h"

#include "constants.hpp"
#include "segment.hpp"

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
    SetTargetFPS(10);

    // Grid
    std::vector<Rectangle> grid;
    for (int i=0; i < ROW_COL; i++ )
    {
        for (int j=0; j < ROW_COL; j++)
        {
            grid.insert(grid.begin(),
                (Rectangle)
                {
                    (j * ((float)550/ROW_COL)),
                    (i * ((float)550/ROW_COL)),
                    ((float)550/ROW_COL),
                    ((float)550/ROW_COL)
                }
            );
        }
    }

    std::vector<Segment> player;
    Segment head = Segment();
    head.velocity = { 0.0, 1.0 };
    player.push_back(head);

    Segment tail = Segment();
    //tail.y = head.y - ((float)550/(float)ROW_COL);
    //player.push_back(tail);
    //tail.y = head.y - (((float)550/(float)ROW_COL) * 2.0);
    //player.push_back(tail);

    Rectangle food = { 0.0 };
    food.x = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
    food.y = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
    food.width = ((float)550/(float)ROW_COL);
    food.height = ((float)550/(float)ROW_COL);

    Vector2 previous = { player[0].x, player[0].y };

    bool showGrid = false;

    bool gameOver = false;
    bool newGame = true;

    while(!WindowShouldClose())
    {
        if (gameOver || newGame)
        {
            BeginDrawing();
                ClearBackground(RAYWHITE);
                if (gameOver)
                {
                    DrawText("Game Over", 220, 550/2, 20, BLACK);
                    DrawText("Press R to Restart", 170, (550/2) + 30, 20, BLACK);
                }
                else
                {
                    DrawText("Press R to Start", 170, (550/2), 20, BLACK);
                }
                
            EndDrawing();
            if (IsKeyPressed(KEY_R))
            {
                player.clear();
                player.push_back(head);
                food.x = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
                food.y = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
                gameOver = false;
                newGame = false;
            }
        }
        else {
            // Handle Input
            if (IsKeyPressed(KEY_DOWN) && player[0].velocity.y != -1) player[0].velocity = { 0 , 1 };
            if (IsKeyPressed(KEY_UP) && player[0].velocity.y != 1) player[0].velocity = { 0, -1 };
            if (IsKeyPressed(KEY_RIGHT) && player[0].velocity.x != -1) player[0].velocity = { 1, 0 };
            if (IsKeyPressed(KEY_LEFT) && player[0].velocity.x != 1) player[0].velocity = { -1 , 0 };

            if(IsKeyPressed(KEY_G)) showGrid = !showGrid;
            
            // Food collision
            if (player[0].x == food.x && player[0].y == food.y)
            {
                food.x = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
                food.y = (float)GetRandomValue(0, ROW_COL - 1) * ((float)550/(float)ROW_COL);
                tail.x = player[player.size() -1].x;
                tail.y = player[player.size() -1].y;
                player.push_back(tail);
            }
        
            // Player movement
            for (int i = 1; i < player.size(); i++)
            {
                float tmpX = player[i].x;
                float tmpY = player[i].y;
                player[i].x = previous.x;
                player[i].y = previous.y;
                previous.x = tmpX;
                previous.y = tmpY;
            }
            player[0].x += player[0].velocity.x * ((float)550/ROW_COL);
            player[0].y += player[0].velocity.y * ((float)550/ROW_COL);
            previous = { player[0].x, player[0].y };

            // Self collision
            if (player.size() > 1)
            {
                for (int i = 1; i < player.size(); i++)
                {
                    if (player[i].x == player[0].x && player[i].y == player[0].y)
                    {
                        gameOver = true;
                    }
                }
            }

            // Wall collision
            if (player[0].x >= 550 || player[0].x < 0 || player[0].y >= 550 || player[0].y < 0)
            {
                gameOver = true;
            }
        
            // Drawing
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (showGrid)
            {
                // Draw grid
                for (int i=0; i < grid.size(); i++)
                {
                    DrawRectangleLinesEx(grid[i], 1,GREEN);
                }
            }

            // Draw food
            DrawRectangleRec(food, PINK);
            
            // Draw Player
            for (int i = 0; i < player.size(); i++)
            {
                if (i == 0)
                {
                    DrawRectangle(player[i].x, player[i].y, player[i].width, player[i].height, GRAY);
                }
                else
                {
                    DrawRectangle(player[i].x, player[i].y, player[i].width, player[i].height, BLACK);
                }
                
            }

            if (gameOver) {
                DrawRectangle(player[0].x, player[0].y, player[0].width, player[0].height, RED);
            }
            
            EndDrawing();
        }
        
    }
}
