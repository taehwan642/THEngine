#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	b = new Board;
	b->difficulty = 2; // �������� 2��� ��
	back = new Sprite();
	back->position = { ScreenW / 2, ScreenH / 2 };
	back->layer = -3;
	back->SetTexture(L"background.png");
}

void GameScene::Update()
{
	if (DXUTWasKeyPressed(VK_F4))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
}

void GameScene::Exit()
{
	delete b;
	delete back;
}
