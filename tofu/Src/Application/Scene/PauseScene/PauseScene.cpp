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
	if (KdInputManager::Instance().IsPress("Pause"))
	{
		SceneManager::Instance().PopOverlay();
	}

	m_spCamera->Update();
}

void C_PauseScene::Init()
{
	//画像ロード
	std::shared_ptr<KdTexture> backGroundTex = C_AssetManager::Instance().GetTex("BackGround");
	std::shared_ptr<KdTexture> backTex = C_AssetManager::Instance().GetTex("PauseBack");
	std::shared_ptr<KdTexture> buttonTex = C_AssetManager::Instance().GetTex("PauseButton");

	//カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS, CAMERA_ROTATE);

	//半透明の背景
	m_backGround = std::make_shared<C_UIBase>();
	m_backGround->Init(BACKGROUND_POS, BACKGROUND_RECT, backGroundTex, BACKGROUND_ALPHA);
	m_backGround->SetActive(true);
	AddObject(m_backGround);

	//背景
	m_back = std::make_shared<C_UIBase>();
	m_back->Init(BACK_POS,BACK_RECT,backTex);
	m_back->SetActive(true);
	AddObject(m_back);

	//続けるボタン
	m_resume = std::make_shared<C_UIBase>();
	m_resume->Init(RESUME_POS, RESUME_RECT, buttonTex);
	m_resume->SetActive(true);
	AddObject(m_resume);

	//リトライボタン
	m_retry = std::make_shared<C_UIBase>();
	m_retry->Init(RETRY_POS, RETRY_RECT, buttonTex);
	m_retry->SetActive(true);
	AddObject(m_retry);

	//タイトルボタン
	m_title = std::make_shared<C_UIBase>();
	m_title->Init(TITLE_POS, TITLE_RECT, buttonTex);
	m_title->SetActive(true);
	AddObject(m_title);
}
