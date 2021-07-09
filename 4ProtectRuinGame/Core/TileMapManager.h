#pragma once
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
	Vec2 blockScale;

	void PlaceBlock();

	void ChangeBlockType();

	void SaveBlocks();

	void LoadBlocks();
};