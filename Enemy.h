#pragma once
#include "GameObject.h"
class SceneDev1;


class Enemy : public GameObject
{

public:
	enum class Types
	{
		Enemy1,
		Enemy2,
		Enemy3,
		Enemy4,
		Enemy5,
	};
	static const int TotalTypes = 5;


protected:
	Types type = Types::Enemy1;

	sf::Sprite body;
	std::string textureId;

	sf::Vector2f direction;
	sf::Vector2f look;
	float speed = 0.f;

	SceneDev1* sceneDev1;

	bool isEnemyActive = false;
	int hp = 0;

	float DieTimer = 0.f;
	float DieDelay = 2.f;

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
	Enemy(const std::string& name = "");
	~Enemy() = default;

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

	void SetType(Types type);

	void OnDamage(int d);

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
};

