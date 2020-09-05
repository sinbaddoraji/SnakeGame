#include "GameBoard.h"
#include <cstddef>
#include "Snake.h"
#include "Food.h"

Food foodList[5]; //Food in the game (Only 5 at a time for now)
bool isRunning = false; //Game is running
Snake snake; //Snake being controlled
int lastFreeFoodIndex = 0; 

Food GetNullFood()
{
	Food nullFood;
	nullFood.index = nullFood.x = nullFood.y = -1;
	return nullFood;
}

void InitalizeFoodList()
{
	for (int i = 0; i < 5; i++) foodList[i] = GetNullFood();
	lastFreeFoodIndex = 0;
}

void AssertEatenFood()
{
	for (int i = 0; i < 5; i++)
	{
		if (foodList[i].x == snake.head->x && foodList[i].y == snake.head->y)
		{
			lastFreeFoodIndex = i;
			foodList[i] = GetNullFood();
			snake.AddMember();
			break;
		}
	}
}

System::Void BasicSnakeGame::GameBoard::GameBoard_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	//0 -> Left
	//1 -> Up
	//2 -> Right
	//3 -> Down
	if (e->KeyCode == Keys::A)
	{
		snake.direction = 0;
	}
	if (e->KeyCode == Keys::W)
	{
		snake.direction = 1;
	}
	else if (e->KeyCode == Keys::D)
	{
		snake.direction = 2;
	}
	else if (e->KeyCode == Keys::S)
	{
		snake.direction = 3;
	}
	else if (e->KeyCode == Keys::Space)
	{
		StartGame();
	}

	//Move snake and redraw graphics
	snake.Move();
	PaintToGrid();

	return System::Void();
}

System::Void BasicSnakeGame::GameBoard::gameTimer_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (snake.hasDied)
	{
		gameTimer->Stop();
		foodGen->Stop();
	}

	AssertEatenFood();
	snake.Move();



	PaintToGrid();
	return System::Void();
}

System::Void BasicSnakeGame::GameBoard::foodGen_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (lastFreeFoodIndex == -1 || lastFreeFoodIndex > 4) return System::Void();

	

	while(foodList[lastFreeFoodIndex + 1].index != -1 && lastFreeFoodIndex < 5)
		lastFreeFoodIndex++;

	if (lastFreeFoodIndex > 4) lastFreeFoodIndex = -1;

	if (lastFreeFoodIndex != -1)
	{
		Food food;
		food.index = lastFreeFoodIndex;
		food.x = rand->Next(0, 40);
		food.y = rand->Next(0, 40);
		foodList[lastFreeFoodIndex] = food;
		lastFreeFoodIndex++;
	}

	foodGen->Interval = BasicSnakeGame::GameBoard::gameTimer->Interval * rand->Next(3, 10);
	return System::Void();
}

void BasicSnakeGame::GameBoard::Move(int direction)
{
	snake.direction = direction;
}

void BasicSnakeGame::GameBoard::PaintToGrid()
{
	ClearGrid();
	//Paint food
	for (int i = 0; i < 5; i++)
	{
		if (foodList[i].index != -1)
		{
			PaintPoint(foodList[i].x, foodList[i].y, true);
		}
	}

	//A 9 X 9 grid
	SnakeBlock* current = snake.head;


	while (current != NULL)
	{
		PaintPoint(current->x, current->y, false);
		current = current->follower;
	}
}

void BasicSnakeGame::GameBoard::StartGame()
{
	if (!snake.hasDied && isRunning) return;

	isRunning = true;

	delete snake.head->follower;
	snake.head->follower = NULL;

	delete snake.tail;
	snake.tail = NULL;

	snake.length = 1;

	snake.hasDied = false;
	gameTimer->Start();

	InitalizeFoodList();
	foodGen->Start();
}

