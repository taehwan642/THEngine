#pragma once
#include "Pixel.h"
#include "VIM.h"
#include "Items.h"
#include "Virus.h"
#include "Effects.h"
#include "Sprite.h"

class Board :
    public Sprite
{
private:

    bool checkedPixels[50][50];
    bool showplayerpos = true; // debug

    PIXELDIRECTION direction;

    list<Pixel*> paths;
    list<Pixel*> clear1;
    list<Pixel*> clear2;

    float deltatime = 0.f;

    int item[5];

    void CheckBoard(int _posX, int _posY, int _index); // ��� �κ��� �� ������ Ȯ��
    void SpawnObsticle(int _posX, int _posY, OBSTICLETAG _tag); // Ư�� ��ġ�� ��ֹ� ����
    // �ڸ��� ���� �� ���̷����� �浹�ϴ���
    bool CheckPathPlayerAndVirusCollision(std::pair<int,int> _viruspos);
    // �ڸ��� ���� ���� �� ���̷����� �浹�ϴ���
    bool CheckPlayerAndVirusCollision(std::pair<int, int> _viruspos);
    // ���̷����� ���� ���� �� �ӿ� �ִ���
    bool CheckVirusInClearedArea(Pixel* _pixel, std::pair<int, int> _viruspos);
    // ���� ���� ��� CLEARED�� ä��� item ����
    void PathstoClearAndSpawnItem(std::list<Pixel*> _list);
    // �÷��̾� �̵���Ű��
    void MovePlayer();

    void Initalize();

    bool clearedBoard = false;
protected:
public:
    float boardclear = 2.f;
    float cleartime = 180.f;
    VIM* vim = nullptr;

    int difficulty = 1;
    int score = 0;

    int pathStartposX = 0;
    int pathStartposY = 0;

    int backposX = 0; // �ٷ� ����
    int backposY = 0; // �ٷ� ����

    int playerX = 49;
    int playerY = 49;
    bool isCutting = false;

    Board(void);
    virtual ~Board(void);
    Pixel* pixels[50][50];
    void Update(void) override;

    void SetDifficulty(int _val);
};

