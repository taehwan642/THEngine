#include "DXUT.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			blockss[i][j] = new Sprite;
			blockss[i][j]->SetTexture(L"box.png");
			blockss[i][j]->scale = { 0.5f, 0.5f };

			const Texture* t = blockss[i][j]->GetTexture();


			if (x > (std::size(blockss[i]) - 1))
			{
				x = 0;
				++y;
			}

			blockss[i][j]->SetPosition(
				((blockss[i][j]->scale.x * t->info.Width) / 2) + (x * t->info.Width * blockss[i][j]->scale.x),
				((blockss[i][j]->scale.y * t->info.Height) / 2) + (y * t->info.Height * blockss[i][j]->scale.y));

			++x;
		}
	}
}

void
TileMapManager::CheckMouseCollision()
{
	POINT pnt;
	GetCursorPos(&pnt);
	ScreenToClient(DXUTGetHWND(), &pnt);

	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			if (PtInRect(&blockss[i][j]->GetRect(), pnt))
			{
				blockss[i][j]->SetTexture(L"block.png");
			}
			else
			{
				blockss[i][j]->SetTexture(L"box.png");
			}
		}
	}
}

void
TileMapManager::PlaceBlock(Vec2 position)
{

}

void 
TileMapManager::ChangeBlockType()
{
}

void 
TileMapManager::SaveBlocks()
{
	
}

void 
TileMapManager::LoadBlocks()
{
#if GAMEON == true
	true;
	// Ÿ���� ���� �ε��� ����� ���� ������� �ǳʶٰ�, Ÿ���� �ִٸ� �����Ҵ�
#else
	false;
	// Ÿ���� ���� ����̶� �����Ҵ�. box.png�� �ؽ�ó ������ 
#endif 

}
