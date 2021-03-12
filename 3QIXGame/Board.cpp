#include "DXUT.h"
#include "Board.h"

void Board::CheckBoard(int _posX, int _posY, int _index)
{
	int score = 0;

	if (checkedPixels[_posX][_posY] == true)
		return;

	checkedPixels[_posX][_posY] = true;

	if ((pixels[_posX][_posY]->state == CLEARED) ||
		(pixels[_posX][_posY]->state == WALL) ||
		(pixels[_posX][_posY]->state == PATH))
	{
		return;
	}

	if (_index == 0)
		clear1.emplace_back(pixels[_posX][_posY]);
	else
		clear2.emplace_back(pixels[_posX][_posY]);

	CheckBoard(_posX + 1, _posY, _index);
	CheckBoard(_posX - 1, _posY, _index);
	CheckBoard(_posX, _posY + 1, _index);
	CheckBoard(_posX, _posY - 1, _index);

	return;
}

Board::Board(void)
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			pixels[i][j] = new Pixel();
			pixels[i][j]->indexX = i;
			pixels[i][j]->indexY = j;
			pixels[i][j]->position =
			{ 300 + ((float)i * 13),
			  20 + ((float)j * 13) };
			pixels[i][j]->state = NONE;
		}
	}

	for (int i = 0; i < 50; ++i)
	{
		pixels[i][0]->state = WALL;
		pixels[i][49]->state = WALL;
		pixels[0][i]->state = WALL;
		pixels[49][i]->state = WALL;
	}

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			checkedPixels[i][j] = false;
		}
	}

	layer = -1;
	SetTexture(L"Pixel.png");
}

Board::~Board(void)
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			delete pixels[i][j];
		}
	}
}

void Board::Update(void)
{
	if (DXUTIsKeyDown('W'))
	{
		backposX = playerX;
		backposY = playerY;
		direction = UPDOWN;
		playerY -= 1;
		if (playerY < 0)
			playerY = 0;
	}
	else if (DXUTIsKeyDown('S'))
	{
		backposX = playerX;
		backposY = playerY;
		direction = UPDOWN;
		playerY += 1;
		if (playerY > 49)
			playerY = 49;
	}
	else if (DXUTIsKeyDown('A'))
	{
		backposX = playerX;
		backposY = playerY;
		direction = LEFTRIGHT;
		playerX -= 1;
		if (playerX < 0)
			playerX = 0;
	}
	else if (DXUTIsKeyDown('D'))
	{
		backposX = playerX;
		backposY = playerY;
		direction = LEFTRIGHT;
		playerX += 1;
		if (playerX > 49)
			playerX = 49;
	}

	if (isCutting == false && pixels[playerX][playerY]->state == NONE)
	{
		isCutting = true;
		pathStartposX = backposX;
		pathStartposY = backposY;
	}

	if (isCutting == true)
	{
		if (pixels[backposX][backposY]->state == NONE)
		{
			pixels[backposX][backposY]->state = PATH;
			pixels[backposX][backposY]->direction = direction;
			paths.emplace_back(pixels[backposX][backposY]);
		}

		if (pixels[playerX][playerY]->state == PATH)
		{
			playerX = pathStartposX;
			playerY = pathStartposY;
			isCutting = false;

			// PATH 초기화
			for (auto& it : paths)
			{
				it->state = NONE;
			}

			paths.clear();
		}


	}

	if (isCutting == true && (pixels[playerX][playerY]->state == WALL) || (pixels[playerX][playerY]->state == CLEARED))
	{
		isCutting = false;
		for (auto& it : paths)
		{
			bool check = false;
			if (it->direction == UPDOWN)
			{
				// 양옆이 비어있으면 이 픽셀을 중심으로 탐색
				if ((pixels[it->indexX + 1][it->indexY]->state == NONE) &&
					(pixels[it->indexX - 1][it->indexY]->state == NONE))
				{
					check = true;
				}
			}
			else
			{
				// 위아래가 비어있으면 이 픽셀을 중심으로 탐색
				if ((pixels[it->indexX][it->indexY + 1]->state == NONE) &&
					(pixels[it->indexX][it->indexY - 1]->state == NONE))
				{
					check = true;
				}
			}

			if (check == true)
			{
				if (it->direction == UPDOWN)
				{
					CheckBoard(it->indexX + 1, it->indexY, 0);
					CheckBoard(it->indexX - 1, it->indexY, 1);
				}
				else
				{
					CheckBoard(it->indexX, it->indexY + 1, 0);
					CheckBoard(it->indexX, it->indexY - 1, 1);
				}

				if (clear1.size() > clear2.size())
				{
					for (auto& it : clear2)
					{
						it->state = CLEARED;
					}
				}
				else
				{
					for (auto& it : clear1)
					{
						it->state = CLEARED;
					}
				}
				
				clear1.clear();
				clear2.clear();

				for (int i = 0; i < 50; ++i)
				{
					for (int j = 0; j < 50; ++j)
					{
						checkedPixels[i][j] = false;
					}
				}
			}
		}

		for (auto& it : paths)
		{
			it->state = CLEARED;
		}
		paths.clear();
	}

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			switch (pixels[i][j]->state)
			{
			case NONE:
				pixels[i][j]->color = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			case WALL:
				pixels[i][j]->color = D3DCOLOR_RGBA(255, 0, 0, 255);
				break;
			case PATH:
				pixels[i][j]->color = D3DCOLOR_RGBA(0, 255, 0, 255);
				break;
			case CLEARED:
				pixels[i][j]->color = D3DCOLOR_RGBA(0, 0, 255, 255);
				break;
			default:
				break;
			}
		}
	}

	if (showplayerpos == true)
		pixels[playerX][playerY]->color = D3DCOLOR_RGBA(100, 100, 100, 255);

	for (auto& it : paths)
	{
		if (it->direction == UPDOWN)
		{
			it->color = D3DCOLOR_RGBA(0, 0, 255, 255);
		}
		else
		{
			it->color = D3DCOLOR_RGBA(200, 200, 0, 255);
		}
	}

	if (DXUTWasKeyPressed('L'))
		showplayerpos = !showplayerpos;

	isCutting == true ? cout << "YES" << endl : cout << "NO" << endl;
}
