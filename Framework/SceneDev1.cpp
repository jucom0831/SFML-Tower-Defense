#include "stdafx.h"
#include "SceneDev1.h"
#include "Tilemap.h"
#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "UiHud.h"
#include "Button.h";

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	tilemap = AddGo(new Tilemap("Tilemap"));
	uiHud = AddGo(new UiHud("Ui"));
	button = AddGo(new Button("Button"));

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
	//std::cout << mousePos.x << "," << mousePos.y << std::endl;
	sf::Vector2f mouseUiPos = ScreenToUi(InputMgr::GetMousePosition());

	Scene::Update(dt);

	for (auto find : tanks) {
		if (find != nullptr) {
			if (find->GetGlobalBounds().contains(mousePos)) {
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left)) {
					dragOffset = mousePos - find->GetPosition();
				}


				if (isDragging == true && isDragend == false) {
					find->SetPosition(mousePos - dragOffset);
				
				}

				if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left)) {
					if (tilemap->IsValidTankTile(mousePos))
					{
						isDragend = true;
						isTankAttack = true;
					}
					else
					{
						
					}
					isDragging = false;
				}

				if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right)) {
					find->TankUpgrade(find);
				}
			}
		}
	}
	if (button->GetGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left)) {
			AddTank(1);
			isDragend = false;

	}
	spawntime += dt;
	if (spawntime > spawnDeley) {
		SpawnEnemys(1);
		spawntime = 0.f;
	}

	std::queue<Enemy*> deleteQue;
	for (auto find : enemys) {
		if (find->OnEnemyDead() == true) {
			mainHp--;
			enemyDeathCount++;
			uiHud->SetHpText(mainHp, maxHp);
			deleteQue.push(find);
		}
	}
	while (!deleteQue.empty())
	{
		OnEnemyDie(deleteQue.front());
		deleteQue.pop();
	}

	EnemyWave(enemyDeathCount);

}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


void SceneDev1::AddTank(int count)
{

	for (int i = 0; i < count; ++i)
	{
		Tank* tank = tankPool.Take();
		tanks.push_back(tank);

		sf::Vector2f pos = button->GetPosition();
		tank->SetPosition(pos);
		isTankAttack = false;
		isDragging = true;
		AddGo(tank);
	}
}

void SceneDev1::SpawnEnemys(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Take();
		enemys.push_back(enemy);

		if (wave > 0) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 5);
			enemy->SetType(enemyType);
		}
		else if (wave > 3) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 4);
			enemy->SetType(enemyType);
		}
		else if (wave > 5) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 3);
			enemy->SetType(enemyType);
		}
		else if (wave > 8) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 2);
			enemy->SetType(enemyType);
		}
		else if (wave > 10)
		{
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
			enemy->SetType(enemyType);
		}

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

void SceneDev1::ReturnTank(Tank* tank)
{
	if (tank != nullptr) {
		RemoveGo(tank);
		tankPool.Return(tank);
		tanks.remove(tank);
	}
}

void SceneDev1::EnemyWave(int count)
{
	if (count == 10 * wave) {
		waveCount++;
	}
	if (wave == waveCount) {
		wave++;
	}
	uiHud->Setwave(wave);
}

void SceneDev1::EnemyDeathActive(bool d)
{
	if (d == true) {
		enemyDeathCount++;
		std::cout << "enemyDeathCount: " << enemyDeathCount << std::endl;
	}
}

bool SceneDev1::TankAttack()
{
	return isTankAttack;
}
