#pragma once
#include "GameObject.h"
class SceneDev1;

class Button : public GameObject
{

protected:
	sf::Sprite body;
	std::string textureId = "graphics/Button1.png";

	SceneDev1* sceneDev1;

public:
	Button(const std::string& name = "");
	~Button() = default;

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

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
};

