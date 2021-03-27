#include "DXUT.h"
#include "Director.h"
#include "RankingScene.h"

void RankingScene::Init()
{
}

void RankingScene::Update()
{
	if (DXUTWasKeyPressed('P'))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
	std::cout << "ȣ����" << std::endl;
}

void RankingScene::Exit()
{
}
