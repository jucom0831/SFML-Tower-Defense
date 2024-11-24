#include "stdafx.h"
#include "UiBackGround.h"

UiBackGround::UiBackGround(const std::string& name)
	: GameObject(name)
{
}

void UiBackGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiBackGround::SetRotation(float angle)
{
	rotation = angle;
}

void UiBackGround::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiBackGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiBackGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiBackGround::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -2;
}

void UiBackGround::Release()
{
}

void UiBackGround::Reset()
{
	backGroundUi.setTexture(TEXTURE_MGR.Get("graphics/solid_color_background.png"));
	Utils::SetOrigin(backGroundUi, Origins::MC);
	backGroundUi.setScale(5.f, 5.f);
	backGroundUi.setPosition(0.f, 0.f);
}

void UiBackGround::Update(float dt)
{
}

void UiBackGround::Draw(sf::RenderWindow& window)
{
	window.draw(backGroundUi);
}
