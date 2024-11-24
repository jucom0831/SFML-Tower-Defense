#include "stdafx.h"
#include "SceneStart.h"
#include "UiStart.h"
#include "SceneMgr.h"

SceneStart::SceneStart() : Scene(SceneIds::Start)
{

}

void SceneStart::Init()
{
	SOUND_MGR.PlayBgm("graphics/superhappycheesyloop1of2.wav", true);
	uiStart = AddGo(new UiStart("UiStart"));
	Scene::Init();
}

void SceneStart::Enter()
{
	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	Scene::Enter();
}

void SceneStart::Exit()
{
	Scene::Exit();
}

void SceneStart::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	Scene::Update(dt);
}

void SceneStart::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
