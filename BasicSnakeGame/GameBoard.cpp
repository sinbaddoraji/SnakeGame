#include "GameBoard.h"
#include <cstddef>

class SnakeBlock
{
public:
	int x;
	int y;
	int parentX;
	int parentY;
	SnakeBlock* follower = NULL;

	void Move(int direction, bool isHead)
	{
		int xCopy = x;
		int yCopy = y;

		if (!isHead)
		{
			x = parentX;
			y = parentY;
		}
		else if (direction == 0)
		{
			if (x <= 0)
				x = 40;
			x--;
		}
		else if (direction == 1)
		{
			if (y <= 0)
				y = 40;
			y--;
		}
		else if (direction == 2)
		{
			if (x >= 40)
				x = 0;
			x++;
		}
		else if (direction == 3)
		{
			if (y >= 40)
				y = 0;
			y++;
		}

		if (follower != NULL)
		{
			follower->parentX = xCopy;
			follower->parentY = yCopy;
			follower->Move(direction, false);
		}
	}
};

class Snake
{
public:

	Snake()
	{
		head = new SnakeBlock;
		head->x = 25;
		head->y = 25;
	}

	SnakeBlock* head;
	SnakeBlock* tail = NULL;
	int direction = 1;

	int length = 1;
	bool hasDied;
	void Move()
	{
		if (!hasDied)
		{
			head->Move(direction, true);
			hasDied = HasBittenSelf();
		}
	}

	bool HasBittenSelf()
	{
		SnakeBlock* current = head->follower;

		while (current != NULL)
		{
			if (current->x == head->x && current->y == head->y)
			{
				return true;
			}
			current = current->follower;
		}
		return false;
	}

	void AddMember()
	{
		length++;

		if (tail == NULL)
		{
			tail = new SnakeBlock;
			head->follower = tail;
			SetupSnakePart(tail, head);
		}
		else
		{
			SnakeBlock* newSnakeBlock = new SnakeBlock;
			tail->follower = newSnakeBlock;

			SetupSnakePart(newSnakeBlock, tail);
			tail = newSnakeBlock;
		}
	}

	void SetupSnakePart(SnakeBlock* snakePart, SnakeBlock* elder)
	{
		if (direction == 0)
		{
			//if going left
			snakePart->y = elder->y;
			snakePart->x = elder->x + 1;
		}
		else if (direction == 1)
		{
			//if going up
			snakePart->y = elder->y + 1;
			snakePart->x = elder->x;
		}
		else if (direction == 2)
		{
			//if going right
			snakePart->x = elder->x - 1;
			snakePart->y = elder->y;
		}
		else if (direction == 3)
		{
			//if going down
			snakePart->y = elder->y - 1;
			snakePart->x = elder->x;
		}
	}
};

class Food
{
public:
	int index;
	int x;
	int y;
};

Snake snake;
bool isRunning = false;

Food foodList[5];
Food nullFood;
int lastFreeIndex = 0;

void InitalizeFoodList()
{
	nullFood.index = nullFood.x = nullFood.y = -1;
	for (int i = 0; i < 5; i++) foodList[i] = nullFood;
}

System::Void BasicSnakeGame::GameBoard::foodGen_Tick(System::Object^ sender, System::EventArgs^ e)
{
	//foodGen->Interval = BasicSnakeGame::GameBoard::gameTimer->Interval * rand->Next(1, 5);
	if(lastFreeIndex == -1) return System::Void();

	Food food;

	food.index = lastFreeIndex;
	food.x = rand->Next(0, 40);
	food.y = rand->Next(0, 40);

	foodList[lastFreeIndex] = food;
	lastFreeIndex++;

	if (lastFreeIndex > 4) lastFreeIndex = -1;
	return System::Void();
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

void AssertEatenFood()
{
	for (int i = 0; i < 5; i++)
	{
		if (foodList[i].x == snake.head->x && foodList[i].y == snake.head->y)
		{
			lastFreeIndex = i;
			foodList[i] = nullFood;
		}
	}
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

void BasicSnakeGame::GameBoard::Move(int direction)
{
	snake.direction = direction;
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
	else if (e->KeyCode == Keys::M)
	{
		snake.AddMember();
	}

	//Move snake and redraw graphics
	snake.Move();
	PaintToGrid();

	return System::Void();
}

