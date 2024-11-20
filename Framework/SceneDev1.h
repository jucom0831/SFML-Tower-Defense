#pragma once
#include "Scene.h"

class Tilemap;
class Tank;
class Bullet;
class Enemy;
class UiHud;

class SceneDev1 : public Scene
{

protected:

	Tilemap* tilemap;
	Tank* tank;
	Tank* tank2;
	Enemy* enemy;
	UiHud* uiHud;

	std::list<Enemy*> enemys;
	ObjectPool<Enemy> enemyPool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	bool isDragging = false;

	sf::Vector2f dragOffset;

	float spawnDeley = 3.f;
	float spawntime = 0.f;

public:
	SceneDev1();
	~SceneDev1() = default;

	void Init();
	void Release();
	void Enter();
	void Exit();
	void Update(float dt);
	void Draw(sf::RenderWindow& window) override;

	void SpawnEnemys(int count);

	Bullet* TakeBullet();
	void ReturnBullet(Bullet* bullet);
	const std::list<Enemy*>& GetEnemyList() const { return enemys; }

	void OnEnemyDie(Enemy* enemy);

};

