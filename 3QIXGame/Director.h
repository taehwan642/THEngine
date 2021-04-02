#include "Scene.h"
#include "Camera.h"
#include "Singleton.h"
#pragma once
class Director : // �� ������. ���� �̵� ������ ����մϴ�.
	public Singleton<Director>
{
private:
	map<SceneTag, Scene*> sceneMap;
	Scene* currentScene; // ���� ���̷�Ʈx���� ���ư��� ��
public:
	LPD3DXSPRITE sprite;

	std::vector<Rank> ranking;
	static bool Comp(Rank a, Rank b) { return a.score > b.score; };

	int latestScore = 0;
	bool isgameend = false;

	void Init();
	void AddScene(SceneTag _sceneTag, Scene* _scene);
	void ChangeScene(SceneTag _sceneTag);
	void UpdateScene();

	void ReleaseAllScenes();
};
