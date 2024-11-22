#pragma once
#include "GameObject.h"
#include "Enemy.h"

class SceneDev1;
class Enemy;

class Tank : public GameObject
{

public:
	enum class Types
	{
		Tank1,
		Tank2,
		Tank3,
	};
	static const int TotalTypes = 3;

protected:
	Types type = Types::Tank1;

	sf::Sprite body;
	std::string textureId;

	sf::Vector2f direction;
	sf::Vector2f look;
	sf::Vector2f rangetank;


	SceneDev1* sceneDev1;
	Enemy* enemy;
	float shootTimer = 0.f;
	float shootDelay = 0.f;
	int range;
	int damage = 0;
	int upgradeMoney = 0;

	bool isAttack = false;
	bool isPlaced = false;
	bool isActive = true;

public:
	Tank(const std::string& name = "");
	~Tank() = default;
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
	void TankUpgrade(Tank* tank);
	void Shoot();

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	void SetActive(bool active);
	int GetMoney();
	void SetPlaced(bool placed) { isPlaced = placed; }

	bool IsPlaced() const { return isPlaced; }
	void SetAttack(bool active) { isAttack = active; }

	sf::Vector2f GetPosition() const { return position; }

	bool GetType(Types types);
	
};

