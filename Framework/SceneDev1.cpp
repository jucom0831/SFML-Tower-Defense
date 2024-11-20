#include "stdafx.h"
#include "SceneDev1.h"
#include "Tilemap.h"
#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "UiHud.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	tank = AddGo(new Tank("Tank"));
	tank2 = AddGo(new Tank("Tank"));
	tilemap = AddGo(new Tilemap("Tilemap"));
	uiHud = AddGo(new UiHud("Ui"));

	tank2->SetPosition(sf::Vector2f(910.f, -470.f));
	Scene::Init();
	spawntime = 3.f;
}

void SceneDev1::Release()
{
	Scene::Release();

}



void SceneDev1::Enter()
{
	Scene::Enter();
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(0.f, 0.f);
}

void SceneDev1::Exit()
{
	for (auto enemy : enemys)
	{
		RemoveGo(enemy);
		enemyPool.Return(enemy);
	}
	enemys.clear();
	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();

	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());
	std::cout << mousePos.x << "," << mousePos.y << std::endl;


	Scene::Update(dt);
	if (tank->GetGlobalBounds().contains(mousePos)) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left)) {
					isDragging = true;
					dragOffset = mousePos - tank->GetPosition();
		}
	}

	if (isDragging) {
		tank->SetPosition(mousePos - dragOffset);
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left)) {
		if (tilemap->IsValidTankTile(mousePos))
		{

		}
		else
		{
			tank->SetPosition({ 0,0 });
		}
		isDragging = false;
	}

	if (tank2->GetGlobalBounds().contains(mousePos)) {
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left)) {
			Tank* newTank = new Tank(*tank);
			newTank->SetPosition(mousePos);
		}
	}
	spawntime += dt;
	if (spawntime > spawnDeley) {
		SpawnEnemys(1);
		spawntime = 0.f;
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


void SceneDev1::SpawnEnemys(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Take();
		enemys.push_back(enemy);

		//Enemy::Types enemyType = (Enemy::Types)Utils::Clamp();
		//enemy->SetType(enemyType);

		sf::Vector2f pos = { -900.f, 0.f };
		enemy->SetPosition(pos);

		AddGo(enemy);
	}
}

Bullet* SceneDev1::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

void SceneDev1::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

void SceneDev1::OnEnemyDie(Enemy* enemy)
{
	RemoveGo(enemy);
	enemyPool.Return(enemy);
	enemys.remove(enemy);
}

