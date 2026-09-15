#include "snake.h"
#include <iostream>
#include <fstream>
#include <conio.h>

//Position von snake ausgeben Funktion
void printPosition(const Position& snake)
{
    std::cout << "Neue Position Snake x: " << snake.x << std::endl;
    std::cout << "Neue Position Snake y: " << snake.y << std::endl;
}


//Hindernisse
void drawObstacle(
    std::vector<Position>& obstacles,
    const std::vector<Position>& snake,
    const Position& food)
{
    Position newObstacle;
    bool invalidPosition;

    do
    {
        newObstacle.x = rand() % WIDTH;
        newObstacle.y = rand() % HEIGHT;

        invalidPosition = false;

        // Liegt es auf der Snake?
        for (const Position& segment : snake)
        {
            if (newObstacle.x == segment.x &&
                newObstacle.y == segment.y)
            {
                invalidPosition = true;
                break;
            }
        }

        // Liegt es auf Food?
        if (newObstacle.x == food.x &&
            newObstacle.y == food.y)
        {
            invalidPosition = true;
        }

        // Liegt dort schon ein Hindernis?
        for (const Position& existingObstacle : obstacles)
        {
            if (newObstacle.x == existingObstacle.x &&
                newObstacle.y == existingObstacle.y)
            {
                invalidPosition = true;
                break;
            }
        }

    } while (invalidPosition);

    obstacles.push_back(newObstacle);
}

//Spielfeld zeichnen Funktion
void drawField(const std::vector<Position>& snake, const Position& food, const std::vector<Position>& obstacle)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            bool snakeHere = false;
            for (int i = 0; i < snake.size(); i++)
            {
                if (x == snake[i].x && y == snake[i].y)
                {
                    snakeHere = true;
                    break;
                }
            }
            if (snakeHere)
            {
                std::cout << "O";
            }
            else if (x == food.x && y == food.y)
            {
                std::cout << "*";
            }
            else
            {
                bool obstacleHere = false;

                for (int i = 0; i < obstacle.size(); i++)
                {
                    if (x == obstacle[i].x && y == obstacle[i].y)
                    {
                        obstacleHere = true;
                        break;
                    }
                }

                if (obstacleHere)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
        }
        std::cout << std::endl;
    }
}

//Snake bewegen Funktion
void moveSnake(std::vector<Position>& snake, char input)
{
    for (int i = snake.size() - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    if (input == 'w')
    {
        snake[0].y--;
    }

    if (input == 's')
    {
        snake[0].y++;
    }

    if (input == 'a')
    {
        snake[0].x--;
    }

    if (input == 'd')
    {
        snake[0].x++;
    }
}



//Check Collision Funktion
bool checkCollision(const std::vector<Position>& snake, const std::vector<Position>& obstacle)
{
    if (snake[0].x < 0 ||
        snake[0].x >= WIDTH ||
        snake[0].y < 0 ||
        snake[0].y >= HEIGHT)
    {
        return true;
    }

    for (int i = 1; i < snake.size(); i++)
    {
        if (snake[0].x == snake[i].x &&
            snake[0].y == snake[i].y)
        {
            return true;
        }
    }

    for (int i = 0; i < obstacle.size(); i++)
{
    if (snake[0].x == obstacle[i].x &&
        snake[0].y == obstacle[i].y)
    {
        return true;
    }
}

    return false;
}

//IsFoodOnSnake Funktion
bool isFoodOnSnake(const std::vector<Position>& snake, const Position& food)
{
    for (const auto& segment : snake)
    {
        if (segment.x == food.x && segment.y == food.y)
        {
            return true;
        }
    }
    return false;
}

//Spawn Food Funktion
Position spawnFood(const std::vector<Position>& snake, const std::vector<Position>& obstacle)
{
    Position food;
    bool invalidPosition;

    do
    {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;

        invalidPosition = false;

        // Liegt Food auf der Snake?
        for (const Position& segment : snake)
        {
            if (food.x == segment.x &&
                food.y == segment.y)
            {
                invalidPosition = true;
                break;
            }
        }

        // Liegt Food auf einem Hindernis?
        for (const Position& obstacleSegment : obstacle)
        {
            if (food.x == obstacleSegment.x &&
                food.y == obstacleSegment.y)
            {
                invalidPosition = true;
                break;
            }
        }

    } while (invalidPosition);

    return food;
}


//Highscore Funktion
void writeHighscoreToFile(const int& highscore)
{
    std::ofstream file("highscore.txt");
    
    file << highscore;
    file.close();
    
}

void saveHighscore(const int& score, int& highscore)
{
    if(score > highscore)
    {
        highscore = score;
        writeHighscoreToFile(highscore);
    }
}

int loadHighscore()
{
    std::ifstream file("highscore.txt");

    int loadedHighscore = 0;

    if(file.is_open())
    {
        file >> loadedHighscore;
        
    }
    file.close();
    return loadedHighscore;
}


void showMenu(int highscore, int& speed_of_snake, bool& startgame)
{
    std::cout << "Welcome to Snake Game!" << std::endl;
    std::cout << "Highscore: " << highscore << std::endl;
    std::cout << "Difficulty:" << std::endl;
    std::cout << "1. Easy (200ms)" << std::endl;
    std::cout << "2. Medium (150ms)" << std::endl;
    std::cout << "3. Hard (100ms)" << std::endl;
    std::cout << "4. Quit Game!" << std::endl;

    char pressedButton;
    do
    {
        pressedButton = _getch();
    } while (pressedButton != '1' && pressedButton != '2' && pressedButton != '3' && pressedButton != '4');

    if (pressedButton == '1')
    {
        speed_of_snake = 200;
        startgame = true;
    }
    else if (pressedButton == '2')
    {
        speed_of_snake = 150;
        startgame = true;
    }
    else if (pressedButton == '3')
    {
        speed_of_snake = 100;
        startgame = true;
    }
    else if (pressedButton == '4')
    {
        std::cout << "Quitting the game." << std::endl;
        exit(0); // Beenden des Programms, wenn der Benutzer '4' drückt
    }
}




