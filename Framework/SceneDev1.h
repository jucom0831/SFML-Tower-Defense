#pragma once
#include "Scene.h"

class Tilemap;
class Tank;
class Bullet;
class Enemy;
class UiHud;
class Button;

class SceneDev1 : public Scene
{

protected:

	Tilemap* tilemap;
	Tank* tank;
	Enemy* enemy;
	UiHud* uiHud;
	Button* button;

	std::list<Tank*> tanks;
	ObjectPool<Tank> tankPool;

	std::list<Enemy*> enemys;
	ObjectPool<Enemy> enemyPool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	sf::Vector2f dragOffset;

	float spawnDeley = 3.f;
	float spawntime = 0.f;
	float wavetime = 0.f;

	int mainHp = 10;
	int maxHp = 10;

	int wave = 1;
	int waveCount = 0;
	int enemyDeathCount = 0;

	bool isEnemydie = false;
	bool isTankAttack = false;

public:

	bool isDragging = false;
	bool isDragend = false;

	SceneDev1();
	~SceneDev1() = default;

	void Init();
	void Release();
	void Enter();
	void Exit();
	void Update(float dt);
	void Draw(sf::RenderWindow& window) override;

	void AddTank(int count);
	void SpawnEnemys(int count);

	Bullet* TakeBullet();
	void ReturnBullet(Bullet* bullet);
	const std::list<Enemy*>& GetEnemyList() const { return enemys; }

	void OnEnemyDie(Enemy* enemy);

	void ReturnTank(Tank* tank);

	void EnemyWave(int count);

	void EnemyDeathActive(bool d);

	bool TankAttack();
};

