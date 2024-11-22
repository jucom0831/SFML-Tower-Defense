#pragma once
#include "GameObject.h"
#include "Animator.h"

class EnemyDie :
    public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	std::map<std::string, AnimationClip> temp;

public:
	EnemyDie(const std::string& name = "");
	~EnemyDie() = default;

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
};  

