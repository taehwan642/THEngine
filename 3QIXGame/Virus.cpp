#include "DXUT.h"
#include "Pixel.h"
#include "Virus.h"

void Virus::SpeedMove()
{
	if (delta <= 0)
	{
		isHit = false;

		for (int i = 0; i < pixelpos.size(); ++i)
		{
			pixelpos[i].first += speedX;
			pixelpos[i].second += speedY;

			if (direction == VUP ||
				direction == VDOWN)
			{
				if (VirusManager::GetInstance()->pixels[pixelpos[i].first][pixelpos[i].second + speedY]->state == OBSTICLE)
				{
					// ���� �ִ� ���� �ٷ� �տ� ��ֹ��̴ϱ� �ݴ� Ȥ�� �ٸ� �������� ����.
				}
			}
			else
			{
				if (VirusManager::GetInstance()->pixels[pixelpos[i].first + speedX][pixelpos[i].second]->state == OBSTICLE)
				{
					// ���� �ִ� ���� �ٷ� �տ� ��ֹ��̴ϱ� �ݴ� Ȥ�� �ٸ� �������� ����.
				}
			}
			

			if (pixelpos[i].first > 48)
			{
				// movespeed ���� �� �ٽ� ����
				pixelpos[i].first = 48;
				SetRandomDirection(direction);
			}
			else if (pixelpos[i].first < 1)
			{
				// movespeed ���� �� �ٽ� ����
				pixelpos[i].first = 1;
				SetRandomDirection(direction);
			}
			
			if (pixelpos[i].second > 48)
			{
				pixelpos[i].second = 48;
				SetRandomDirection(direction);
			}
			else if (pixelpos[i].second < 1)
			{
				pixelpos[i].second = 1;
				SetRandomDirection(direction);
			}
		}
		delta = movespeed;
	}
	else
		delta -= DXUTGetElapsedTime();
}

void Virus::BigMove()
{
}

void Virus::FlashMove()
{
}

void Virus::ToxinoMove()
{
}

void Virus::SetRandomDirection(VIRUSDIRECTION _direction)
{
	// 1. X �߽����� Y �߽����� ����
	// 2. parameter�� ���� _direction�� �����ϰ� ������ 3 ������ ������.
	int xory = rand() % 2;
	if (xory == 0) // x �߽�
	{
		if (_direction == VLEFT ||
			_direction == VRIGHT)
		{
			if (_direction == VLEFT)
			{
				speedX = 1;
				direction = VRIGHT;
			}
			else
			{
				speedX = -1;
				direction = VLEFT;
			}
		}
		else
		{
			int ran = rand() % 2;
			if (ran == 0)
			{
				speedX = 1;
				direction = VRIGHT;
			}
			else
			{
				speedX = -1;
				direction = VLEFT;
			}
		}
		speedY = 0;
	}
	else // y�߽�
	{
		if (_direction == VUP ||
			_direction == VDOWN)
		{
			if (_direction == VUP)
			{
				speedY = 1;
				direction = VDOWN;
			}
			else
			{
				speedY = -1;
				direction = VUP;
			}
		}
		else
		{
			int ran = rand() % 2;
			if (ran == 0)
			{
				speedY = 1;
				direction = VDOWN;
			}
			else
			{
				speedY = -1;
				direction = VUP;
			}
		}
		speedX = 0;
	}
}

Virus::Virus()
{
	layer = -1;
	SetTexture(L"Item.png");
	scale = { 0.05f,0.05f };
	direction = VRIGHT;
}

Virus::~Virus()
{

}

void Virus::Update()
{
	switch (tag)
	{
	case SPEEDVIRUS:
		SpeedMove();
		break;
	case BIGVIRUS:
		BigMove();
		break;
	case FLASHVIRUS:
		FlashMove();
		break;
	case TOXINO:
		ToxinoMove();
		break;
	default:
		break;
	}
}

void VirusManager::SetDifficulty(int _val)
{
	difficulty = _val;
}

void VirusManager::CreateVirus()
{
	for (int i = 0; i < 20; ++i)
	{
		Virus* v = new Virus();
		v->isactive = false;
		virusVector.emplace_back(v);
	}
}

void VirusManager::SpawnVirus(Vec2 _position, int _startX, int _startY, VIRUSTAG _tag)
{
	for (int i = 0; i < virusVector.size(); ++i)
	{
		if (virusVector[i]->isactive == false)
		{
			virusVector[i]->isactive = true;
			virusVector[i]->tag = _tag;
			virusVector[i]->pixelpos.emplace_back(_startX, _startY);
			virusVector[i]->position = _position;
			switch (_tag)
			{
			case SPEEDVIRUS:
				break;
			case BIGVIRUS:
				break;
			case FLASHVIRUS:
				break;
			case TOXINO:
				break;
			default:
				break;
			}
			return;
		}
	}
	
}

void VirusManager::DeleteVirus()
{
	for (int i = 0; i < virusVector.size(); ++i)
	{
		delete virusVector[i];
	}
	virusVector.clear();
}
