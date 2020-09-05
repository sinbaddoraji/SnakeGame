#include <cstddef>
#pragma once

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
