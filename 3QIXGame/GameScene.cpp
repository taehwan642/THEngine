#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	b = new Board;
	b->SetDifficulty(1);
	back = new Sprite();
	back->position = { ScreenW / 2, ScreenH / 2 };
	back->layer = -3;
	back->SetTexture(L"background.png");
	font = new Font();
	font->layer = 10;
	font->Createfont(5, 5, L"Arial");
	font->SetFont("Press R to Restart");
	font->isactive = false;
}

void GameScene::Update()
{
	// Ŭ���� ���� �����ߴ��� Ȯ��
	if (b->score >= 2000) //��ֹ��� 2500���� �ȼ��� �ӿ��� 500�� �̸��̾����.
	{
		int difficulty = b->difficulty;
		delete b;
		b = new Board();
		b->SetDifficulty(difficulty + 1);
	}

	if (b->vim->HP <= 0)
	{
		font->isactive = true;
		if (DXUTWasKeyPressed('R'))
		{
			int difficulty = b->difficulty;
			delete b;
			b = new Board;
			b->SetDifficulty(difficulty);
			font->isactive = false;
		}
	}

	// 4. �޴� ��ȯ
	if (DXUTWasKeyPressed(VK_F4))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
	// 5. 1�������� ��ȯ
	if (DXUTWasKeyPressed(VK_F5))
	{
		delete b;
		b = new Board();
		b->SetDifficulty(1);
	}
	// 6. 2�������� ��ȯ
	if (DXUTWasKeyPressed(VK_F6))
	{
		delete b;
		b = new Board();
		b->SetDifficulty(2);
	}
}

void GameScene::Exit()
{
	delete b;
	delete back;
	delete font;
}
