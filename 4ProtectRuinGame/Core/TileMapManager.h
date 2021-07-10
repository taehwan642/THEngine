#pragma once
#include "Sprite.h"
#include "Singleton.h"

struct Block
{
	enum class BlockType
	{
		FLOOR,
		OBSTICLE
	};

	BlockType type;
};

class TileMapManager :
	public Singleton<TileMapManager>
{
	// 1. ���콺�� Ŭ���ϸ� �ű⿡ ���� ����� �ڸ��� ��������
	// 2. 1, 2, 3 �� ���� ������ ��� ���� �ٲ��
	// 3. Ư�� Ű ������ txt���Ϸ� ����
	// 4. Ư�� Ű ������ txt���� �ҷ�����

public:
	std::vector<Block> blocks;
	Sprite* blockss[6][20];

	float blockScale;

	TileMapManager();

	void CheckMouseCollision();
	void PlaceBlock(Vec2 position);
	void ChangeBlockType();
	void SaveBlocks();
	void LoadBlocks();
};