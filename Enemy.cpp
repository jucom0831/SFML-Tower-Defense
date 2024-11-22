#include "stdafx.h"
#include "Enemy.h"
#include "SceneDev1.h"

Enemy::Enemy(const std::string& name)
	: GameObject(name)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Enemy::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Enemy::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Enemy::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Enemy::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
	isEnemyActive = true;
	SetType(type);

}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(Origins::MC);
	SetRotation(0.f);
	SetScale({ 1.5f, 1.5f });
	isEnemyDead = false;
	currentTargetIndex = 0;
}

void Enemy::Update(float dt)
{

	sf::Vector2f target = path[currentTargetIndex];
	direction = target - position;
	if (direction != sf::Vector2f(0, 0)) {
		direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
	}
	SetPosition(position + direction * speed * dt);
	if (std::abs(position.x - target.x) < 1.0f && std::abs(position.y - target.y) < 1.0f) {
		currentTargetIndex = (currentTargetIndex + 1) % path.size();
	}

	SetRotation(Utils::Angle(direction));
	if ((std::abs(position.x - path[12].x) < 1.0f && std::abs(position.y - path[12].y) < 1.0f)) {
		isEnemyDead = true;
		//sceneDev1->OnEnemyDie(this);
	}
	hitbox.UpdateTr(body, GetLocalBounds());
	if (hp <= 0 && sceneDev1 != nullptr)
	{
		isEnemyActive = false;
		//body.setTexture(TEXTURE_MGR.Get("graphics/blood.png"), true);
		sceneDev1->OnEnemyDie(this);
		sceneDev1->EnemyDeathActive(true);
		sceneDev1->OnEnemyDieAnimation(this);
	}

	sf::FloatRect localBounds = GetLocalBounds();
	float hitboxscale = 0.4f;

	
	sf::FloatRect scaledBounds = {
		localBounds.left ,
		localBounds.top + 23.f,
		localBounds.width,
		localBounds.height * hitboxscale,
	};

	hitbox.UpdateTrForEnemy(body, scaledBounds);


}


void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void Enemy::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Enemy1:
		textureId = "graphics/enemy1.png";
		hp = 150;
		speed = 120.f;
		break;
	case Types::Enemy2:
		textureId = "graphics/enemy3.png";
		hp = 300;
		speed = 150.f;
		break;
	case Types::Enemy3:
		textureId = "graphics/enemy5.png";
		hp = 1000;
		speed = 70.f;
		break;
	case Types::Enemy4:
		textureId = "graphics/enemy8.png";
		hp = 500;
		speed = 250.f;
		break;
	case Types::Enemy5:
		textureId = "graphics/enemy15.png";
		hp = 1500;
		speed = 150.f;
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
}

void Enemy::OnDamage(int d)
{
	hp -= d;
}

bool Enemy::OnEnemyDead()
{
	return isEnemyDead;
}

sf::FloatRect Enemy::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Enemy::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}
