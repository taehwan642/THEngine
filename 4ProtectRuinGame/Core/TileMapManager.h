#pragma once
#include "Sprite.h"
#include "Singleton.h"

enum class BlockType
{
	NONE,
	FLOOR,
	OBSTICLE
};

struct Block
{
	BlockType type;
	Sprite* sprite;
};

#define Row 6
#define Column 20

class TileMapManager :
	public Singleton<TileMapManager>
{
	// 1. ���콺�� Ŭ���ϸ� �ű⿡ ���� ����� �ڸ��� ��������
	// 2. 1, 2, 3 �� ���� ������ ��� ���� �ٲ��
	// 3. Ư�� Ű ������ txt���Ϸ� ����
	// 4. Ư�� Ű ������ txt���� �ҷ�����

private:
	std::vector<Block> blocks;

	Sprite* blockss[Row][Column];
	BlockType blockTypes[Row][Column];
	
	float blockScale;
public:
	TileMapManager();

	void Initialize();

	void UpdateManager();

	std::vector<Block>& GetBlockVector();

	void SaveBlocks();
	void LoadBlocks();

	void DeleteBlocks();
};