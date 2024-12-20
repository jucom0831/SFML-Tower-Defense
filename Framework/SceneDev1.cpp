#include "stdafx.h"
#include "SceneDev1.h"
#include "Tilemap.h"
#include "Tank.h"
#include "Bullet.h"
#include "Enemy.h"
#include "UiHud.h"
#include "Button.h";
#include "EnemyDie.h"
#include "UiBackGround.h"
#include "BossEnemy.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	tilemap = AddGo(new Tilemap("Tilemap"));
	uiHud = AddGo(new UiHud("Ui"));
	button = AddGo(new Button("Button"));
	uiBackGround = AddGo(new UiBackGround("BackGround"));

	Scene::Init();

	spawntime = 3.f;
	isBossSpawn = false;
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

	SOUND_MGR.PlayBgm("graphics/superhappycheesyloop2of2.wav", true);

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
	for (auto tank : tanks) {
		RemoveGo(tank);
		tankPool.Return(tank);
	}
	tanks.clear();
	wave = 1;
	mainHp = 10;
	Coin = 100;

	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	
	sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());
	//std::cout << mousePos.x << "," << mousePos.y << std::endl;
	sf::Vector2f mouseUiPos = ScreenToUi(InputMgr::GetMousePosition());
	float adjustedDt = isDoubleSpeed ? dt * 2.0f : dt;

	Scene::Update(adjustedDt);


	if (uiHud->GetGlobalBounds().contains(mouseUiPos)) {
		if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left)) {
			isDoubleSpeed = !isDoubleSpeed;
		}
	}


	if (tank != nullptr) {
		if (tank->IsPlaced() == false && isDragend == false && isDragging == true) {
			tank->SetPosition(mousePos);
		}
		if (tank->GetGlobalBounds().contains(mousePos)) {
			if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left)) {
				if (tilemap->IsValidTankTile(mousePos))
				{
					isDragend = true;
					tank->SetPlaced(true);
					tank->SetAttack(true);

					bool isSuccess = true;
					for (auto f : tanks) {
						if (tank != nullptr) {
							if (f->GetGlobalBounds().intersects(tank->GetGlobalBounds())) {
								isSuccess = false;
								RemoveGo(tank);
								tankPool.Return(tank);
								tank = nullptr;
								Coin += 40;
								break;
							}
						}
					}

					if(isSuccess)
						tanks.push_back(tank);
					tank = nullptr;
				}
				else
				{
					RemoveGo(tank);
					tankPool.Return(tank);
					Coin += 40;
					tank = nullptr;
				}
				isDragging = false;
			}
		}
	}

	for (auto find : tanks) {
		if (find != nullptr) {
			if (find->GetGlobalBounds().contains(mousePos)) {
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right) && find->GetType(Tank::Types::Tank1) && Coin >= 100) {
					find->TankUpgrade(find);
					SubtractionCoin(find->GetMoney());
				}
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right) && find->GetType(Tank::Types::Tank2) && Coin >= 300) {
					find->TankUpgrade(find);
					SubtractionCoin(find->GetMoney());
				}
			}
		}
	}

	for (auto find : tanks) {
		if (find != nullptr) {
			if (find->GetGlobalBounds().contains(mousePos)) {
				if (InputMgr::GetKeyDown(sf::Keyboard::E)) {
					RemoveGo(find);
					tankPool.Return(find);
					Coin += find->GetMoney()/2;
				}
			}
		}
	}

	if (button->GetGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left) && Coin >= 40) {
		AddTank(1);
		SOUND_MGR.PlaySfx("graphics/cash-register.wav", false);
		Coin -= 40;
		isDragend = false;
		isDragging = true;
	}


	spawntime += adjustedDt;
	if (isEnemySpawn == true && spawntime > spawnDeley) {
		SpawnEnemys(1);
		//SpawnBossEnemys(1);
		spawntime = 0.f;
		spawnCount++;

		if (spawnCount >= 10) {
			isEnemySpawn = false;
			isCount = true;
		}
	}

	if (!isEnemySpawn && enemys.size() == 0) {
		waveDelay -= adjustedDt;
		if (waveDelay <= 0.f) {
			spawnCount = 0;
			waveDelay = 15.f;
			isEnemySpawn = true;
		}
	}

	std::queue<Enemy*> deleteQue;
	for (auto find : enemys) {
		if (find->OnEnemyDead() == true) {
			mainHp--;
			enemyDeathCount++;
			uiHud->SetHpText(mainHp, maxHp);
			if (mainHp <= 0) {
				SCENE_MGR.ChangeScene(SceneIds::Dev2);
			}
			deleteQue.push(find);
			
		}
	}
	while (!deleteQue.empty())
	{
		OnEnemyDie(deleteQue.front());
		deleteQue.pop();
	}

	EnemyWave(enemyDeathCount);
	uiHud->SetCoin(Coin);

	if (enemyDeathCount == 100) {
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}

}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}


void SceneDev1::AddTank(int count)
{

	for (int i = 0; i < count; ++i)
	{
		tank = tankPool.Take();
		//tanks.push_back(tank);

		sf::Vector2f pos = button->GetPosition();
		tank->SetPosition(pos);
		tank->SetPlaced(false);
		tank->SetAttack(false);
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

		if (wave > 9) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
			enemy->SetType(enemyType);
		}
		else if (wave >= 7) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 2);
			enemy->SetType(enemyType);
		}
		else if (wave >= 5) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 3);
			enemy->SetType(enemyType);
		}
		else if (wave >= 3 ) {
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 4);
			enemy->SetType(enemyType);
		}
		else if (wave > 0)
		{
			Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 5);
			enemy->SetType(enemyType);
		}

		sf::Vector2f pos = { -900.f, 0.f };
		enemy->SetPosition(pos);

		AddGo(enemy);
	}
}

//void SceneDev1::SpawnBossEnemys(int count) {
//	if (wave == 2) {
//		for (int i = 0; i < count; ++i) {
//			bossEnemy = AddGo(new BossEnemy("BossEnemy"));
//			if (bossEnemy) {
//				std::cout << "Boss enemy added successfully." << std::endl;
//			}
//		}
//
//	}
//}

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

void SceneDev1::OnBossEnemyDie(BossEnemy* bossEnemy)
{
	RemoveGo(bossEnemy);
}

void SceneDev1::OnEnemyDieAnimation(Enemy* enemy)
{
	enemyDie = AddGo(new EnemyDie("EnemyDie"));
	enemyDie->Init();
	enemyDie->Reset();
	enemyDie->SetPosition(enemy->GetPosition());
}

void SceneDev1::ReturnTank(Tank* tank)
{
	RemoveGo(tank);
	tankPool.Return(tank);
	tanks.remove(tank);
}

void SceneDev1::EnemyWave(int count)
{
	if (wave < 10) {
		if (!isEnemySpawn && isCount) {
			waveCount++;
			isCount = false;
		}
		if (wave == waveCount) {
			wave++;
		}
		uiHud->Setwave(wave);
	}
}

void SceneDev1::EnemyDeathActive(bool d)
{
	if (d == true) {
		enemyDeathCount++;
		std::cout << "enemyDeathCount: " << enemyDeathCount << std::endl;
	}
}

int SceneDev1::AddCoin(int c) {

	Coin += c;
	return Coin;
}

int SceneDev1::SubtractionCoin(int c) {
	Coin -= c;
	return Coin;
}