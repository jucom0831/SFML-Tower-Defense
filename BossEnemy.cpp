#include "stdafx.h"
#include "BossEnemy.h"
#include "SceneDev1.h"

BossEnemy::BossEnemy(const std::string& name)
	: GameObject(name)
{
}

void BossEnemy::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void BossEnemy::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void BossEnemy::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void BossEnemy::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BossEnemy::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BossEnemy::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
	isEnemyActive = true;
}

void BossEnemy::Release()
{
}

void BossEnemy::Reset()
{
	sceneDev1 = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(Origins::MC);
	SetRotation(0.f);
	SetScale({ 1.5f, 1.5f });
	isEnemyDead = false;
	currentTargetIndex = 0;
}

void BossEnemy::Update(float dt)
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
		sceneDev1->EnemyDeathActive(true);
		sceneDev1->OnBossEnemyDie(this);
		sceneDev1->AddCoin(money);
		SOUND_MGR.PlaySfx("graphics/explosion.wav", false);
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
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


void BossEnemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}

void BossEnemy::OnDamage(int d)
{
	hp -= d;
}

bool BossEnemy::OnEnemyDead()
{
	return isEnemyDead;
}

sf::FloatRect BossEnemy::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect BossEnemy::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

int BossEnemy::EnemyMoney()
{
	return money;
}
