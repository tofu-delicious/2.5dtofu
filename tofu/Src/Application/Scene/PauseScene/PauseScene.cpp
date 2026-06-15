//PauseScene.cpp
#include "PauseScene.h"
#include "../SceneManager.h"
#include "../../Asset/AssetManager.h"
#include "../../UI/UIBase/UIBase.h"
#include "../../UI/UIFade/UIFade.h"
#include "../../UI/UIAppearFade/UIAppearFade.h"
#include "../../Camera/Camera.h"

C_PauseScene::C_PauseScene() { Init(); }

C_PauseScene::~C_PauseScene(){}

void C_PauseScene::Event()
{
	m_spCamera->Update();
}

void C_PauseScene::Init()
{
	//カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS, CAMERA_ROTATE);

	//背景
	m_back = std::make_shared<C_UIBase>();
	std::shared_ptr<KdTexture> backTex = C_AssetManager::Instance().GetTex("PauseBack");
	m_back->Init(BACK_POS,BACK_RECT,backTex);
	AddObject(m_back);

	//続けるボタン
	m_resume = std::make_shared<C_UIBase>();
	std::shared_ptr<KdTexture> resumeTex = C_AssetManager::Instance().GetTex("PauseButton");
	m_resume->Init(RESUME_POS, RESUME_RECT, resumeTex);
	AddObject(m_resume);

	//リトライボタン
	m_retry = std::make_shared<C_UIBase>();
	std::shared_ptr<KdTexture> retryTex = C_AssetManager::Instance().GetTex("PauseButton");
	m_retry->Init(RETRY_POS, RETRY_RECT, retryTex);
	AddObject(m_retry);

	//タイトルボタン
	m_title = std::make_shared<C_UIBase>();
	std::shared_ptr<KdTexture> titleTex = C_AssetManager::Instance().GetTex("PauseButton");
	m_title->Init(TITLE_POS, TITLE_RECT, titleTex);
	AddObject(m_title);
}
