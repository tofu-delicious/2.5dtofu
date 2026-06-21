//ResultScene.cpp
#include "ResultScene.h"
#include "../../Asset/AssetManager.h"
#include "../../UI/UIBase/UIBase.h"
#include "../../UI/UIFade/UIFade.h"

C_ResultScene::C_ResultScene() { Init(); }

C_ResultScene::~C_ResultScene(){}

void C_ResultScene::Event()
{
}

void C_ResultScene::Init()
{
	//画像ロード
	std::shared_ptr<KdTexture> backGroundTex = C_AssetManager::Instance().GetTex("BackGround");
	std::shared_ptr<KdTexture> backTex = C_AssetManager::Instance().GetTex("ResultBack");
	std::shared_ptr<KdTexture> buttonTex = C_AssetManager::Instance().GetTex("ResultButton");
	
	//薄い背景
	m_backGround = std::make_shared<C_UIBase>();
	m_backGround->Init(BACKGROUND_POS, BACKGROUND_RECT, backGroundTex, BACKGROUND_ALPHA);
	m_backGround->SetActive(true);
	AddObject(m_backGround);

	//背景
	m_back = std::make_shared<C_UIBase>();
	m_back->Init(BACK_POS, BACK_RECT, backTex);
	m_back->SetActive(true);
	AddObject(m_back);


	//リトライ
	m_retry = std::make_shared<C_UIBase>();
	m_retry->Init(RETRY_POS, RETRY_RECT, buttonTex);
	m_retry->SetActive(true);
	AddObject(m_retry);

	//タイトル
	m_title = std::make_shared<C_UIBase>();
	m_title->Init(TITLE_POS, TITLE_RECT, buttonTex);
	m_title->SetActive(true);
	AddObject(m_title);
}
