#pragma once

class HitBox
{
public:
	HitBox();

	sf::RectangleShape rect;

	void UpdateTr(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void UpdateTrForEnemy(const sf::Transformable& tr, const sf::FloatRect& localBound);
	void UpdateTankTr(const sf::Transformable& tr, const sf::FloatRect& localBounds);
	void Draw(sf::RenderWindow& window);
};