#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <iostream>


struct Position 
{
    int x;
    int y;
};

const int WIDTH = 20;
const int HEIGHT = 10;

void moveSnake(std::vector<Position>& snake, char input);

bool checkCollision(const std::vector<Position>& snake, const std::vector<Position>& obstacle);

Position spawnFood(const std::vector<Position>& snake, const std::vector<Position>& obstacle);

bool isFoodOnSnake(const std::vector<Position>& snake, const Position& food);

void printPosition(const Position& snake);

void drawField(const std::vector<Position>& snake, const Position& food, const std::vector<Position>& obstacle);

void writeHighscore(int score);

void saveHighscore(const int& score, int& highscore);

int loadHighscore();

void showMenu(int highscore, int& speed_of_snake, bool& startgame);

void drawObstacle(std::vector<Position>& obstacle, const std::vector<Position>& snake, const Position& food);

#endif
