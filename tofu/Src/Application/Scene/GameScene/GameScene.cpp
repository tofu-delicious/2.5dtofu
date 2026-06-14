#include "GameScene.h"
#include"../SceneManager.h"
#include "../../ImGui/ImGuiManager.h"
#include "../../Camera/Camera.h"
#include "../../Object/Tofu/Tofu.h"
#include "../../Object/Kitchen/KitchenManager.h"

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

	//カメラ更新処理
	m_spCamera->Update();

	//キッチン処理
	m_kitchenMgr->Update();

	//新しく追加されたキッチンを「objList」へ同期
	SyncKitchensObjList();
}

void GameScene::Init()
{
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

void GameScene::SetUpImGuiManager()
{
	C_ImGuiManager::Instance().SetCamera(m_spCamera.get());
	//C_ImGuiManager::Instance().SetKitchen(m_kitchen);
	C_ImGuiManager::Instance().SetKitchenMgr(m_kitchenMgr);
	C_ImGuiManager::Instance().SetTofu(m_tofu);
}
