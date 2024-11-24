#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	float textSize = 24.f;
	sf::Font& font = FONT_MGR.Get("fonts/NEXONLv1GothicRegular.ttf");
	hpText.setFont(font);
	hpText.setCharacterSize(textSize);
	hpText.setFillColor(sf::Color::White);
	Utils::SetOrigin(hpText, Origins::TL);
	hpText.setScale(0.7f, 1.f);
	hpText.setPosition(35.f, 40.f);
	hpIcon.setTexture(TEXTURE_MGR.Get("graphics/heart.png"));
	Utils::SetOrigin(hpIcon, Origins::TL);
	hpIcon.setScale(0.3f, 0.5f);
	hpIcon.setPosition(5.f, 10.f);
	addTank.setTexture(TEXTURE_MGR.Get("graphics/Tank1.png"));
	Utils::SetOrigin(addTank, Origins::MC);
	addTank.setPosition(970.f, 60.f);
	addTank.setScale(0.6f, 1.0f);
	textWave.setFont(font);
	textWave.setCharacterSize(textSize + 20.f );
	textWave.setFillColor(sf::Color::White);
	textWave.setOutlineThickness(1.f);
	textWave.setPosition(480.f, 20.f);
	textWave.setScale(0.6f, 1.0f);

	Cointext.setFont(font);
	Cointext.setCharacterSize(textSize);
	Cointext.setFillColor(sf::Color::White);
	Cointext.setPosition(971.5f, 435.f);
	Cointext.setScale(0.4f, 1.0f);

	CoinIcon.setTexture(TEXTURE_MGR.Get("graphics/$64.png"));
	Utils::SetOrigin(CoinIcon, Origins::MC);
	CoinIcon.setScale(0.5f, 0.7f);
	CoinIcon.setPosition(972.f, 400.f);
	SetHpText(10, 10);
	Setwave(1);

	timeSpeed.setTexture(TEXTURE_MGR.Get("graphics/speedUp_btn.png"));
	Utils::SetOrigin(timeSpeed, Origins::MC);
	timeSpeed.setScale(0.5f, 0.8f);
	timeSpeed.setPosition(972.f, 700.f);


	tank2.setTexture(TEXTURE_MGR.Get("graphics/Tank2.png"));
	Utils::SetOrigin(tank2, Origins::MC);
	tank2.setPosition(970.f, 200.f);
	tank2.setScale(0.6f, 1.0f);
	tank2UpgradeCost.setFont(font);
	tank2UpgradeCost.setCharacterSize(textSize);
	tank2UpgradeCost.setFillColor(sf::Color::White);
	tank2UpgradeCost.setPosition(960.f, 235.f);
	tank2UpgradeCost.setScale(0.4f, 1.0f);
	tank2UpgradeCost.setString("$100");
	tank3.setTexture(TEXTURE_MGR.Get("graphics/Tank2.png"));
	Utils::SetOrigin(tank3, Origins::MC);
	tank3.setPosition(970.f, 300.f);
	tank3.setScale(0.6f, 1.0f);
	tank3UpgradeCost.setFont(font);
	tank3UpgradeCost.setCharacterSize(textSize);
	tank3UpgradeCost.setFillColor(sf::Color::White);
	tank3UpgradeCost.setPosition(960.f, 335.f);
	tank3UpgradeCost.setScale(0.4f, 1.0f);
	tank3UpgradeCost.setString("$300");




}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(hpText);
	window.draw(hpIcon);
	window.draw(addTank);
	window.draw(textWave);
	window.draw(CoinIcon);
	window.draw(Cointext);
	window.draw(timeSpeed);
	window.draw(tank2);
	window.draw(tank2UpgradeCost);
	window.draw(tank3);
	window.draw(tank3UpgradeCost);
}

void UiHud::SetHpText(int s, int t)
{
	hpText.setString(std::to_string(s) + " / " + std::to_string(t));
	Utils::SetOrigin(hpText, Origins::BL);
}

void UiHud::Setwave(int w)
{
	textWave.setString("Wave : " + std::to_string(w));
	Utils::SetOrigin(textWave, Origins::MC);
}

void UiHud::SetCoin(int c)
{
	Cointext.setString(std::to_string(c));
	Utils::SetOrigin(Cointext, Origins::MC);
}

sf::FloatRect UiHud::GetLocalBounds() const
{
	return timeSpeed.getLocalBounds();
}

sf::FloatRect UiHud::GetGlobalBounds() const
{
	return timeSpeed.getGlobalBounds();
}