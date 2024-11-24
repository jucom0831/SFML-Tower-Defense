#pragma once
#include "GameObject.h"
#include "SceneDev1.h"
class BossEnemy : public GameObject
{
protected:

	sf::Sprite body;
	std::string textureId = "graphics/enemy31.png";

	sf::Vector2f direction;
	sf::Vector2f look;
	float speed = 100.f;

	SceneDev1* sceneDev1;

	bool isEnemyActive = false;
	bool isEnemyDead = false;
	int hp = 10000;
	int money = 2000;


	std::vector<sf::Vector2f> path =
	{
		{620, 0},
		{620, -390},
		{140, -390},
		{140, 380},
		{620, 380},
		{620, 0},
		{-725, 0},
		{-725, 380},
		{-245, 380},
		{-245, -390},
		{-725, -390},
		{-725, 0},
		{820, 0}
	};
	size_t currentTargetIndex = 0;

public:
	BossEnemy(const std::string& name = "");
	~BossEnemy() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
	void OnDamage(int d);
	bool OnEnemyDead();

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	int EnemyMoney();
};

