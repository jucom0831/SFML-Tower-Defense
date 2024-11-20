#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(const std::string& name)
	: GameObject(name)
{
}

void Tilemap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	for (auto& rect : cellBounds)
	{
		rect.setPosition(rect.getPosition() - (GetGlobalBounds().getSize() / (float)2) + pos);
	}

	UpdateTransfrom();
}

void Tilemap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransfrom();
}

void Tilemap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransfrom();
}

void Tilemap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}

	UpdateTransfrom();
}

void Tilemap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	UpdateTransfrom();
}


sf::FloatRect Tilemap::GetLocalBounds() const
{
	return { 0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y };
}

sf::FloatRect Tilemap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return transfrom.transformRect(bounds);
}

bool Tilemap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	cellCount.x = width;
	cellCount.y = height;
	cellSize = (sf::Vector2f)tileSize;

	if (!tiletexture.loadFromFile(tileset))
		return false;

	va.setPrimitiveType(sf::Quads);
	va.resize(width * height * 4);


	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			int tileNumber = tiles[i + j * width];

			int tu = tileNumber % (tiletexture.getSize().x / tileSize.x);
			int tv = tileNumber / (tiletexture.getSize().x / tileSize.x);

			sf::Vertex* Quads = &va[(i + j * width) * 4];

			Quads[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			Quads[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			Quads[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			Quads[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			Quads[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			Quads[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			Quads[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			Quads[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			cellBounds[i + j * width] = sf::RectangleShape(cellSize);
			cellBounds[i + j * width].setPosition(Quads[0].position);
			cellBounds[i + j * width].setOutlineColor(sf::Color::Blue);
			cellBounds[i + j * width].setOutlineThickness(0);
			cellBounds[i + j * width].setFillColor(sf::Color::Transparent);
			//Utils::SetOrigin(cellBounds[i + j * width], Origins::MC);
		}

	return true;
}

void Tilemap::SetType(int t, Types type)
{
	tankType[t] = type;
}

bool Tilemap::CheckIsSameType(int index, Types type)
{
	return tankType[index] == type;
}

bool Tilemap::IsValidTankTile(sf::Vector2f mousepos)
{
	for (int i = 0; i < cellBounds.size(); i++)
	{
		if (cellBounds[i].getGlobalBounds().contains(mousepos))
		{
			return CheckIsSameType(i, Types::tankTile);
		}
	}
	return false;
}

void Tilemap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
	tankType.resize(sizeof(level) / sizeof(int));
	cellBounds.resize(sizeof(level) / sizeof(int));
	load("graphics/terrain.png", sf::Vector2u(96, 96), level, 19, 11);
	SetOrigin(Origins::MC);

	for (unsigned int i = 0; i < 19 * 11; ++i) {
		int tileType = level[i];

		switch (tileType) {
		case 0:
			SetType(i, Types::tankTile);
			break;
		case 1:
			SetType(i, Types::enemyTile);
			break;
		case 2:
			SetType(i, Types::startTile);
			break;
		case 3:
			SetType(i, Types::endTile);
			break;
		default:
			break;
		}
	}
}


void Tilemap::Release()
{
}

void Tilemap::Reset()
{

	SetOrigin(originPreset);
	SetPosition({ -50.f, 0.f });

}

void Tilemap::Update(float dt)
{

}

void Tilemap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = &tiletexture;
	state.transform = transfrom;
	window.draw(va, state);
	for (auto& rect : cellBounds)
	{
		window.draw(rect);
	}
}


void Tilemap::UpdateTransfrom()
{
	transfrom = sf::Transform::Identity;
	transfrom.translate(position);
	transfrom.scale(scale);
	transfrom.rotate(rotation);
	transfrom.translate(-origin);


}
