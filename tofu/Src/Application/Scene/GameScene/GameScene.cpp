//GameScene.cpp
#include "GameScene.h"
#include "../SceneManager.h"
#include "../../ImGui/ImGuiManager.h"
#include "../../Camera/Camera.h"
#include "../../Object/Tile/BackGroundScroller.h"
#include "../../Object/Tofu/Tofu.h"
#include "../../Object/Kitchen/KitchenManager.h"
#include "../../Object/Gimmick/GimmickManager.h" // 追加

GameScene::GameScene() { Init(); }

GameScene::~GameScene() {}

void GameScene::Event()
{
	// ポーズ画面表示
	if(KdInputManager::Instance().IsPress("Pause"))
	{
		SceneManager::Instance().PushOverlay(SceneManager::SceneType::Pause);
	}

	//リザルト画面へ遷移
	if (m_tofu->IsExpired() && !m_isChangeResultScene)
	{
		m_isChangeResultScene = true;
		SceneManager::Instance().PushOverlay(SceneManager::SceneType::Result);
	}

	// カメラ更新
	m_spCamera->Update();

	// キッチン更新（内部でGimmickManagerへの通知も行われる）
	m_kitchenMgr->Update();

	// ギミック更新（スクロール・削除）
	m_gimmickMgr->Update();

	// 新しく追加されたキッチン・ギミックをobjListへ同期
	SyncKitchensObjList();
	SyncGimmicksObjList();
}

void GameScene::Init()
{
	// 背景
	m_back = std::make_shared<C_BackGroundScroller>();
	m_back->Init();
	m_objList.push_back(m_back);

	// ギミックマネージャー（KitchenManagerより先に作る）
	m_gimmickMgr = std::make_shared<C_GimmickManager>();

	// キッチンマネージャー
	m_kitchenMgr = std::make_shared<C_KitchenManager>();
	m_kitchenMgr->SetGimmickManager(m_gimmickMgr); // 通知先を登録
	m_kitchenMgr->Init(); // Init内でキッチンが生成され、GimmickManagerへ通知が飛ぶ

	// とうふ
	m_tofu = std::make_shared<C_Tofu>();
	m_tofu->Init();
	m_objList.push_back(m_tofu);

	// カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS, CAMERA_ROTATE);
	m_spCamera->SetTofu(m_tofu);

	//=================================================

	SyncKitchensObjList();
	SyncGimmicksObjList();

	SetUpImGuiManager();
}

void GameScene::SyncKitchensObjList()
{
	for (auto& kitchen : m_kitchenMgr->GetKitchens())
	{
		auto it = std::find(m_objList.begin(), m_objList.end(), kitchen);
		if (it == m_objList.end())
			m_objList.push_back(kitchen);
	}
}

void GameScene::SyncGimmicksObjList()
{
	// SyncKitchensObjListと同じ仕組み
	// 新しく追加されたギミックだけをobjListに追加する
	for (auto& gimmick : m_gimmickMgr->GetGimmicks())
	{
		auto it = std::find(m_objList.begin(), m_objList.end(), gimmick);
		if (it == m_objList.end())
			m_objList.push_back(gimmick);
	}
}

void GameScene::SetUpImGuiManager()
{
	C_ImGuiManager::Instance().SetCamera(m_spCamera.get());
	C_ImGuiManager::Instance().SetKitchenMgr(m_kitchenMgr);
	C_ImGuiManager::Instance().SetTofu(m_tofu);
	C_ImGuiManager::Instance().SetBack(m_back);
	C_ImGuiManager::Instance().SetGimmickMgr(m_gimmickMgr);
}