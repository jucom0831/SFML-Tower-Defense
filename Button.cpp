#include "stdafx.h"
#include "Button.h"
#include "SceneDev1.h"

Button::Button(const std::string& name)
	: GameObject(name)
{
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Button::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Button::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Button::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Button::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}
void Button::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

}

void Button::Release()
{
}

void Button::Reset()
{
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetRotation(0.f);
	SetScale({ 0.2f, 0.2f });
	SetPosition({ 905.f, -415.f });
}

void Button::Update(float dt)
{
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::FloatRect Button::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Button::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}
