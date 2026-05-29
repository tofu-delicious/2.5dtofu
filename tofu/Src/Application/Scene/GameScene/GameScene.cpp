#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Camera/Camera.h"
#include "../../Object/Tofu/Tofu.h"

GameScene::GameScene() { Init(); }

GameScene::~GameScene(){}

void GameScene::Event()
{
	/*if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}*/

	m_camera->Update();
}

void GameScene::Init()
{
	m_camera = std::make_unique<C_Camera>();
	m_camera->Init();

	//とうふ
	m_tofu = std::make_unique<C_Tofu>();
	m_tofu->Init();
	m_objList.push_back(std::move(m_tofu));
}
