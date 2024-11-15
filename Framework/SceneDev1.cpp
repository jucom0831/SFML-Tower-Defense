#include "stdafx.h"
#include "SceneDev1.h"


SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{

	Scene::Init();
}

void SceneDev1::Enter()
{
	Scene::Enter();

	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	person p{ "Ned Flanders", "744 Evergreen Terrace", 60 };
	json j = p;
	std::cout << j.dump(4) << std::endl;

	j["name"] = "ABC";
	person p2 = j.get <person>();
	std::cout << p2.name << p2.address << p2.age << std::endl;



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
