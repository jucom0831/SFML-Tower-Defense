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
	hpIcon.setTexture(TEXTURE_MGR.Get("graphics/heart.png"));
	Utils::SetOrigin(hpIcon, Origins::TL);
	hpIcon.setScale(0.3f, 0.5f);
	hpText.setScale(0.7f, 1.f);
	hpIcon.setPosition(5.f, 10.f);
	hpText.setPosition(35.f, 40.f);

	SetHpText(10, 10);
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(hpText);
	window.draw(hpIcon);
}

void UiHud::SetHpText(int s, int t)
{
	hpText.setString(std::to_string(s) + " / " + std::to_string(t));
	Utils::SetOrigin(hpText, Origins::BL);
}
