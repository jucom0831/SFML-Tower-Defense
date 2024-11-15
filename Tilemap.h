#pragma once
#include "GameObject.h"

class Tilemap : public GameObject

{
protected:
	sf::VertexArray va;
	std::string spriteSheetId = "graphics/terrain_2.png";
	std::string spriteSheetId2 = "graphics/terrain_4.png";
	sf::Texture texture;
	sf::Transform transfrom;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;



public:
	Tilemap(const std::string& name = "");
	~Tilemap() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	//void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void UpdateTransfrom();
	sf::FloatRect GetLocalBounds()const override;
	sf::FloatRect GetGlobalBounds()const override;

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

};