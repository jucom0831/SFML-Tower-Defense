#include "stdafx.h"
#include "UiStart.h"

UiStart::UiStart(const std::string& name)
	: GameObject(name)
{
}

void UiStart::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiStart::SetRotation(float angle)
{
	rotation = angle;
}

void UiStart::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiStart::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiStart::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiStart::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiStart::Release()
{
}

void UiStart::Reset()
{
	float textSize = 40.f;
	sf::Font& font = FONT_MGR.Get("fonts/NEXONLv1GothicRegular.ttf");
	startText.setFont(font);
	startText.setCharacterSize(textSize);
	startText.setFillColor(sf::Color::Black);
	Utils::SetOrigin(startText, Origins::MC);
	startText.setScale(0.7f, 1.f);
	startText.setPosition(360.f, 480.f);
	StartSceneUi.setTexture(TEXTURE_MGR.Get("graphics/title-screen.png"));
	Utils::SetOrigin(StartSceneUi, Origins::MC);
	StartSceneUi.setScale(0.55f, 0.7f);
	StartSceneUi.setPosition(480.f, 500.f);
	startText.setString("Press to Enter Start");
	//startText.
}

void UiStart::Update(float dt)
{
}

void UiStart::Draw(sf::RenderWindow& window)
{
	window.draw(StartSceneUi);
	window.draw(startText);
}
