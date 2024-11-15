#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(const std::string& name)
	: GameObject(name)
{
}

void Tilemap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
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

	if (!texture.loadFromFile(tileset))
	     return false;

	va.setPrimitiveType(sf::Triangles);
	va.resize(width * height * 6);

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (texture.getSize().x / tileSize.x);
			int tv = tileNumber / (texture.getSize().x / tileSize.x);

			// get a pointer to the triangles' vertices of the current tile
			sf::Vertex* triangles = &va[(i + j * width) * 6];

			// define the 6 corners of the two triangles
			triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

			// define the 6 matching texture coordinates
			triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}


void Tilemap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;


	const int level[] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,
		0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};

	load("graphics/terrain_1.png", sf::Vector2u(96, 96), level, 19, 11);
	SetOrigin(Origins::MC);
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
	state.texture = &texture;//&TEXTURE_MGR.Get("graphics/terrain_1.png)");
	state.transform = transfrom;
	window.draw(va, state);
}

//void Tilemap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
//{
//	cellCount = count;
//	cellSize = size;
//
//	va.clear();
//	va.setPrimitiveType(sf::Quads);
//	va.resize(count.x * count.y * 4);
//
//	sf::Vector2f posOffset[4] = {
//		{0.f, 0.f},
//		{size.x , 0.f},
//		{size.x, size.y},
//		{0.f, size.y},
//	};
//
//	sf::Vector2f texCoords[4] = {
//		{0, 0},
//		{96.f, 0},
//		{96.f, 96.f},
//		{0, 96.f},
//	};
//
//	for (int i = 0; i < count.y ; ++i) {
//		for (int j = 0; j < count.x; ++j) {
//			int quadIndex = i * count.x + j;
//			sf::Vector2f quadPos(j * size.x, i * size.y);
//			for (int k = 0; k < 4; ++k) {
//				int vertexIndex = quadIndex * 4 + k;
//				va[vertexIndex].position = quadPos + posOffset[k];
//				va[vertexIndex].texCoords = texCoords[k];
//			}
//		}
//	}
//
//	va2.clear();
//	va2.setPrimitiveType(sf::Quads);
//	va2.resize(count.x * 4);
//
//	for (int j = 0; j < count.x; ++j) {
//		sf::Vector2f quadPos(j * size.x, 5 * size.y);
//		for (int k = 0; k < 4; ++k) {
//			int vertexIndex = j * 4 + k;
//			va2[vertexIndex].position = quadPos + posOffset[k];
//			va2[vertexIndex].texCoords = texCoords[k];
//		}
//	}
//
//
//}

void Tilemap::UpdateTransfrom()
{
	transfrom = sf::Transform::Identity;
	transfrom.translate(position);
	transfrom.scale(scale);
	transfrom.rotate(rotation);
	transfrom.translate(-origin);
}
