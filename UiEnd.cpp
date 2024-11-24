#include "stdafx.h"
#include "UiEnd.h"

UiEnd::UiEnd(const std::string& name)
	: GameObject(name)
{
}

void UiEnd::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiEnd::SetRotation(float angle)
{
	rotation = angle;
}

void UiEnd::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiEnd::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiEnd::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiEnd::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiEnd::Release()
{
}

void UiEnd::Reset()
{
	float textSize = 60.f;
	sf::Font& font = FONT_MGR.Get("fonts/NEXONLv1GothicRegular.ttf");
	endText.setFont(font);
	endText.setCharacterSize(textSize);
	endText.setFillColor(sf::Color::Black);
	Utils::SetOrigin(endText, Origins::MC);
	endText.setScale(0.7f, 1.f);
	endText.setPosition(300.f, 370.f);
	EndSceneUi.setTexture(TEXTURE_MGR.Get("graphics/tank_battle_game_over.png"));
	Utils::SetOrigin(EndSceneUi, Origins::MC);
	EndSceneUi.setScale(0.55f, 0.7f);
	EndSceneUi.setPosition(480.f, 500.f);
	endText.setString("Thank You to Play!");
}

void UiEnd::Update(float dt)
{
}

void UiEnd::Draw(sf::RenderWindow& window)
{
	window.draw(EndSceneUi);
	window.draw(endText);
}
