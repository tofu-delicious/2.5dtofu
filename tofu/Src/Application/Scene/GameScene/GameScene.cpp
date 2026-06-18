#include "GameScene.h"
#include"../SceneManager.h"
#include "../../ImGui/ImGuiManager.h"
#include "../../Camera/Camera.h"
#include "../../Object/Tile/BackGroundScroller.h"
#include "../../Object/Tofu/Tofu.h"
#include "../../Object/Kitchen/KitchenManager.h"

GameScene::GameScene() { Init(); }

GameScene::~GameScene(){}

void GameScene::Event()
{
	//ポーズ画面表示
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		SceneManager::Instance().PushOverlay(SceneManager::SceneType::Pause);
	}

	//カメラ更新処理
	m_spCamera->Update();

	//キッチン処理
	m_kitchenMgr->Update();

	//新しく追加されたキッチンを「objList」へ同期
	SyncKitchensObjList();

	//ギミック関連をm_objListに格納
	SyncGimmicksObjList();
}

void GameScene::Init()
{
	//背景
	m_back = std::make_shared<C_BackGroundScroller>();
	m_back->Init();
	m_objList.push_back(m_back);

	//キッチン
	m_kitchenMgr = std::make_shared<C_KitchenManager>();
	m_kitchenMgr->Init();

	//とうふ
	m_tofu = std::make_shared<C_Tofu>();
	m_tofu->Init();
	m_objList.push_back(m_tofu);

	//カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS,CAMERA_ROTATE);
	m_spCamera->SetTofu(m_tofu);

	SyncKitchensObjList();

	SyncGimmicksObjList();

	SetUpImGuiManager();
}

void GameScene::SyncKitchensObjList()
{
	for (auto& kitchen : m_kitchenMgr->GetKitchens())
	{
		//既に登録済みならスキップ
		auto it = std::find(m_objList.begin(), m_objList.end(), kitchen);
		if (it == m_objList.end())
			m_objList.push_back(kitchen);
	}
}

void GameScene::SyncGimmicksObjList()
{
	for (auto& gimmick : m_kitchenMgr->GetGimmicks())
	{
		auto it = std::find(m_objList.begin(), m_objList.end(), gimmick);
		if (it == m_objList.end())
			m_objList.push_back(gimmick);
	}
}

void GameScene::SetUpImGuiManager()
{
	C_ImGuiManager::Instance().SetCamera(m_spCamera.get());
	//C_ImGuiManager::Instance().SetKitchen(m_kitchen);
	C_ImGuiManager::Instance().SetKitchenMgr(m_kitchenMgr);
	C_ImGuiManager::Instance().SetTofu(m_tofu);
	C_ImGuiManager::Instance().SetBack(m_back);
}
