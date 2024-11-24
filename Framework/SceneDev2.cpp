#include "stdafx.h"
#include "SceneDev2.h"
#include "UiEnd.h"
SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	uiEnd = AddGo(new UiEnd("UiEnd"));
	Scene::Init();
}

void SceneDev2::Enter()
{
	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	Scene::Enter();
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Start);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape)) {
		SCENE_MGR.ChangeScene(SceneIds::None);
	}
	Scene::Update(dt);
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
