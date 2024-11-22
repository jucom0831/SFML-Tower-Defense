#include "stdafx.h"
#include "Tank.h"
#include "SceneDev1.h"
#include "Bullet.h"
#include "Scene.h"
#include "Enemy.h"

Tank::Tank(const std::string& name)
	: GameObject(name)
{
}

void Tank::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Tank::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Tank::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Tank::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Tank::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Tank::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetOrigin(Origins::MC);

}

void Tank::Release()
{

}

void Tank::Reset()
{
	SetType(Types::Tank1);
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetRotation(0.f);
	SetScale({ 1.5f, 1.5f });
}

void Tank::Update(float dt)
{
	hitbox.UpdateTr(body, GetLocalBounds());

	if (isAttack == true) {
		float lookDistance = std::numeric_limits<float>::max();
		sf::Vector2f lookEnemyPosition;
		Enemy* lookEnemy = nullptr;

		for (auto find : sceneDev1->GetEnemyList()) {
			if (find != nullptr) {
				sf::Vector2f rangeenemy = find->GetPosition() - position;
				float distance = Utils::Distance(position, find->GetPosition());
				if (distance < lookDistance && distance < Utils::Magnitude(rangetank)) {
					lookDistance = distance;
					lookEnemy = find;
					lookEnemyPosition = find->GetPosition();
				}
			}
		}

		if (lookEnemy != nullptr) {
			direction = Utils::GetNormal(lookEnemyPosition - position);
			look = Utils::GetNormal(lookEnemyPosition - position);
			SetRotation(Utils::Angle(direction));

			shootTimer += dt;
			if (shootTimer > shootDelay) {
				shootTimer = 0.f;
				Shoot();
			}
		}
	}
	
}

void Tank::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Tank::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Tank1:
		textureId = "graphics/Tank1.png";
		range = 800;
		damage = 10;
		break;
	case Types::Tank2:
		textureId = "graphics/Tank2.png";
		range = 750;
		damage = 30;
		break;
	case Types::Tank3:
		textureId = "graphics/Tank3.png";
		damage = 50;
		range = 700;
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
}

void Tank::TankUpgrade(Tank* tank)
{
	SetType((Tank::Types)(Utils::Clamp((int)type + 1, 0, 2)));
}

void Tank::Shoot()
{
	Bullet* bullet = sceneDev1->TakeBullet();
	bullet->Fire(position, look, 1000.f, damage);
}

sf::FloatRect Tank::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Tank::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Tank::SetActive(bool active)
{
	isActive = active;
}