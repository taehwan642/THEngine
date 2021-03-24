#pragma once
#include "Sprite.h"
#include "Singleton.h"

class Virus :
    public Sprite
{
private:
    void SpeedMove();
    void BigMove();
    void FlashMove();
    void ToxinoMove();
public:
    float delta = 0.f;
    float movespeed = 0.1f;
    int speed = 1;
    
    bool isHit = false;

    std::vector<std::pair<int, int>> pixelpos; // first = X, second = Y

    VIRUSTAG tag;
    Virus();
    virtual ~Virus();

    void Update() override;
};

class VirusManager :
    public Singleton<VirusManager>
{
private:
    int difficulty = 1;
public:
    std::vector<Virus*> virusVector;
    void SetDifficulty(int _val);
    void CreateVirus();
    void SpawnVirus(Vec2 _position, int _startX, int _startY, VIRUSTAG _tag);
    void DeleteVirus();
};