#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum class BlockType
{
	NONE,
	FLOOR,
	OBSTICLE
};

#define Row 3
#define Column 10

class TileMapManager :
	public Singleton<TileMapManager>
{
	// 1. ���콺�� Ŭ���ϸ� �ű⿡ ���� ����� �ڸ��� ��������
	// 2. 1, 2, 3 �� ���� ������ ��� ���� �ٲ��
	// 3. Ư�� Ű ������ txt���Ϸ� ����
	// 4. Ư�� Ű ������ txt���� �ҷ�����


public:
	Sprite* blockss[Row][Column];
	BlockType blockTypes[Row][Column];

	float blockScale;

	TileMapManager();

	void CheckMouseCollision();
	void ChangeBlockType();
	void UpdateManager();
	void SaveBlocks();
	void LoadBlocks();

	void DeleteBlocks();
};