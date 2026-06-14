#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Asset/AssetManager.h"
#include "../../UI/UIBase/UIBase.h"
#include "../../Camera/Camera.h"

TitleScene::TitleScene() { Init(); }

TitleScene::~TitleScene(){}

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	m_spCamera->Update();
}

void TitleScene::Init()
{
	//カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS,CAMERA_ROTATE);

	//タイル
	m_tile = std::make_shared<C_UIBase>();
	std::shared_ptr<KdTexture> tex = C_AssetManager::Instance().GetTex("Tile");
	m_tile->Init(TILE_POS,TILE_RECT,tex);
	m_tile->SetCamera(m_spCamera->GetKdCamera());
	AddObject(m_tile);
}
