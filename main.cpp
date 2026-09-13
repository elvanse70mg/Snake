#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>

//Config
int speed_of_snake = 200; //in milliseconds

const int WIDTH = 20;
const int HEIGHT = 10;

//position für schlagenkopf erstellen
struct Position 
{
    int x;
    int y;
};

//Position von snake ausgeben Funktion

void printPosition(Position snake)
{
    std::cout << "Neue Position Snake x: " << snake.x << std::endl;
    std::cout << "Neue Position Snake y: " << snake.y << std::endl;
}




//0 bewegen Funktion
void drawField(const std::vector<Position>& snake, Position food)
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
            else if (x == food.x && y == food.y )
            {
                std::cout << "*";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

//Check Collision Funktion
bool checkCollision(const std::vector<Position>& snake)
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

    return false;
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

int main() 
{
    std::srand(std::time(0));

    std::vector<Position> snake;

    snake.push_back({5, 5});
    snake.push_back({4, 5});
    snake.push_back({3, 5});
    snake.push_back({2, 5});
    

    //Food
    Position food;
    food.x = 10;
    food.y = 3;

    //Score
    int score = 0;


    char input;
    

    std::cout << "Snake x: " << snake[0].x << std::endl;
    std::cout << "Snake y: " << snake[0].y << std::endl;

    bool ateFood = false;

    bool gameOver = false;
    
    input = 'd'; // Startrichtung der Schlange auf 'd' setzen (nach rechts)
    //Steuerung
    while (!gameOver)
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(speed_of_snake));
        
        if(_kbhit()){
            input = _getch();
        }
        

        moveSnake(snake, input);

    //Collision
    gameOver = checkCollision(snake);


//Game Over
    if(gameOver == true){
        std::cout << "Game Over! You collided with yourself." << std::endl;
        break;
    }

        //Begrenzung
    if (snake[0].x < 0)
{
    snake[0].x = 0;
}

    if (snake[0].x >= WIDTH)
{
    snake[0].x = WIDTH - 1;
}

    if (snake[0].y < 0)
{
    snake[0].y = 0;
}

    if (snake[0].y >= HEIGHT)
{
    snake[0].y = HEIGHT - 1;
}

    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        ateFood = true;
        food.x = std::rand() % WIDTH;
        food.y = std::rand() % HEIGHT;
        score++;
    }

    
    system("cls");
    
    
    drawField(snake, food);
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


    




    



}
