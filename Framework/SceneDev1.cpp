#include "stdafx.h"
#include "SceneDev1.h"
#include "Tilemap.h"


SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	tilemap = AddGo(new Tilemap("Tilemap"));
	Scene::Init();
}



void SceneDev1::Enter()
{
	Scene::Enter();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
