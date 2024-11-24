#pragma once
#include "GameObject.h"
class UiHud : public GameObject
{
protected:
	sf::Sprite hpIcon;
	sf::Text hpText;

	TextGo text;
	sf::Sprite addTank;

	sf::Sprite tank2;
	sf::Text tank2UpgradeCost;
	sf::Sprite tank3;
	sf::Text tank3UpgradeCost;

	sf::Text textWave;

	sf::Sprite CoinIcon;
	sf::Text Cointext;

	sf::Sprite timeSpeed;

public:
	UiHud(const std::string& name = "");
	~UiHud() = default;

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

	void SetHpText(int s, int t);
	void Setwave(int w);
	void SetCoin(int c);

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
};
