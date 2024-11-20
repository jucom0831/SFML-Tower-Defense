#pragma once
#include "GameObject.h"

class Tilemap : public GameObject


{
public:
enum class Types {
	tankTile,
	enemyTile,
	startTile,
	endTile,
};

protected:
	Types type;

	sf::VertexArray va;
	sf::Texture tiletexture;
	sf::Transform transfrom;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

	std::vector<Types> tankType;
	std::vector<sf::RectangleShape> cellBounds;

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
	void SetType(int t, Types type);
	bool CheckIsSameType(int index, Types type);
	size_t GetTypeVecSize() const { return tankType.size(); }

	int level[209] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};

	bool IsValidTankTile(sf::Vector2f mousepos);

};