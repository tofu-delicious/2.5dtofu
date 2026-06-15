#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Asset/AssetManager.h"
#include "../../UI/UIBase/UIBase.h"
#include "../../UI/UIFade/UIFade.h"
#include "../../UI/UIAppearFade/UIAppearFade.h"
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
	std::shared_ptr<KdTexture> tileTex = C_AssetManager::Instance().GetTex("Tile");
	m_tile->Init(TILE_POS,TILE_RECT,tileTex);
	AddObject(m_tile);

	//スタートボタン
	m_start = std::make_shared<C_UIFade>();
	std::shared_ptr<KdTexture> startTex = C_AssetManager::Instance().GetTex("TitleButton");
	m_start->Init(START_POS, START_RECT,startTex);
	AddObject(m_start);

	//音量設定ボタン
	m_sound = std::make_shared<C_UIAppearFade>();
	std::shared_ptr<KdTexture> soundTex = C_AssetManager::Instance().GetTex("TitleButton");
	m_sound->Init(SOUND_POS, SOUND_RECT,soundTex);
	AddObject(m_sound);
}
