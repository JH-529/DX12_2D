#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);

	GET_SINGLE(SceneManager)->LoadScene(SCENE_TYPE::MAIN);
}

void Game::Update()
{
	GEngine->Update();	
}
