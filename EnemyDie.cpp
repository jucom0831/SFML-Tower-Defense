#include "stdafx.h"
#include "EnemyDie.h"
#include "AnimationClip.h"

EnemyDie::EnemyDie(const std::string& name)
	: GameObject(name)
{
}

void EnemyDie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void EnemyDie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void EnemyDie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void EnemyDie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void EnemyDie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void EnemyDie::Init()
{
	animator.SetTarget(&body);
	SetScale({0.7f, 0.7f});
	std::string textureId = "graphics/explosionspritesheet8.png";
	int width = 130;
	int height = 130;

	AnimationClip clip;
	clip.id = "Enemydie";
	clip.fps = 25;
	clip.loopType = AnimationLoopTypes::Single;
	for (int j = 0; j < 5; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			clip.frames.push_back({ textureId, { i * width, j * height, width, height } });
		}
	}
	temp.insert({ "Enemydie", clip });
}

void EnemyDie::Release()
{
}

void EnemyDie::Reset()
{
	animator.Play(&temp["Enemydie"]);
	SetOrigin(Origins::MC);
}

void EnemyDie::Update(float dt)
{
	animator.Update(dt);
}

void EnemyDie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
