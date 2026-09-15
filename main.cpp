#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <fstream>
#include "snake.h"

//Config
int speed_of_snake = 200; //in milliseconds

//Pause Funktion
bool paused = false;

int highscore = 0;

bool startgame = false; // Variable to control the game loop


int main() 
{
    
    std::srand(std::time(0));

    highscore = loadHighscore();

    showMenu(highscore, speed_of_snake, startgame);
    

    while(startgame){// 2. Schleife um restarten zu können
        
        
    

    std::vector<Position> snake;
    std::vector<Position> obstacle;

    snake.push_back({5, 5});
    snake.push_back({4, 5});
    snake.push_back({3, 5});
    snake.push_back({2, 5});
    

    //Food
    Position food = spawnFood(snake, obstacle);

    //Score
    int score = 0;
    
    std::cout << "Snake x: " << snake[0].x << std::endl;
    std::cout << "Snake y: " << snake[0].y << std::endl;

    bool ateFood = false;

    bool gameOver = false;

    //Steuerung
    
    char input = 'd'; // Startrichtung der Schlange auf 'd' setzen (nach rechts)
    
    while (!gameOver)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(speed_of_snake));

        
        
        if(_kbhit()){
            char pressedButton = _getch();
            if (pressedButton == 'w' || pressedButton == 'a' || pressedButton == 's' || pressedButton == 'd')
            {
                input = pressedButton;
            }
            if (pressedButton == 'p')
            {
                paused = !paused;

                if (paused)
                {

                    std::cout << "Game Paused. Press 'p' to resume." << std::endl;
                }
                else
                {
                    
                    std::cout << "Game Resumed." << std::endl;
                    
                    
                }
                
            }
        }

        if(paused)
        {
            continue; 
        }

        moveSnake(snake, input);
        
        

        

    //Collision
    gameOver = checkCollision(snake, obstacle);


//Game Over
    if(gameOver){
        std::cout << "Game Over! You collided." << std::endl;
        break;
    }

//Food eaten

    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        ateFood = true;
        food = spawnFood(snake, obstacle);
        score++;
        //Wenn Score um 5 steigt, Geschwindigkeit erhöhen
        if (score % 5 == 0 && score != 0)
    {
        speed_of_snake -= 10; // Geschwindigkeit um 10ms erhöhen
        drawObstacle(obstacle, snake, food); // Hindernis zeichnen


    }
    }

    
    system("cls");
    
    
    drawField(snake, food, obstacle);
    printPosition(snake[0]);
    std::cout << "Score: " << score << std::endl;
    
    //Food gegessen - Schlange wachsen lassen
    if (ateFood == true)
    {
        std::cout << "Food gegessen!" << std::endl;
        ateFood = false;
        snake.push_back(snake[snake.size() - 1]);
    }

    
}

    //Runde ist vorbei
    system("cls");
    saveHighscore(score, highscore);
    std::cout << "Game Over! Final Score: " << score << std::endl;
    std::cout << "Highscore: " << highscore << std::endl;
    std::cout << "Press r  to continue or q to quit." << std::endl;
    std::cout << "Speed: " << speed_of_snake << " ms" << std::endl;

    char choice;

    do
{
    choice = _getch();
}
    while (choice != 'r' && choice != 'q');

    if (choice == 'q')
{
    break;
}

    if (choice == 'r')
{
    continue;
}



    



}
}


