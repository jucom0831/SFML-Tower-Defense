#pragma once
#include "Scene.h"

class UiStart;

class SceneStart :
    public Scene
{
protected:
	UiStart* uiStart;

public:
	SceneStart();
	~SceneStart() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

