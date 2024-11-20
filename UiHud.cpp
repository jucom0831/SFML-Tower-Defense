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


	SetHpText(10, 10);
	Setwave(1);
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
