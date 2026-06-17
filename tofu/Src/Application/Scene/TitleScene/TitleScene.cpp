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

	MoveCursor();

	m_spCamera->Update();
}

void TitleScene::Init()
{
	//カメラ
	m_spCamera = std::make_shared<C_Camera>();
	m_spCamera->Init(CAMERA_POS,CAMERA_ROTATE);

	//画像データロード
	std::shared_ptr<KdTexture> tileTex = C_AssetManager::Instance().GetTex("Tile");
	std::shared_ptr<KdTexture> buttonTex = C_AssetManager::Instance().GetTex("TitleButton");

	//タイル
	m_tile = std::make_shared<C_UIBase>();
	m_tile->Init(TILE_POS, TILE_RECT, tileTex);
	m_tile->SetActive(true);
	AddObject(m_tile);

	//====================== 通常描画 ============================
	//スタートボタン（デフォルト：非表示）
	m_startBase = std::make_shared<C_UIBase>();
	m_startBase->Init(START_POS, START_RECT, buttonTex);
	m_startBase->SetActive(false);
	AddObject(m_startBase);

	//サウンドボタン（デフォルト：表示）
	m_soundBase = std::make_shared<C_UIBase>();
	m_soundBase->Init(SOUND_POS, SOUND_RECT, buttonTex);
	m_soundBase->SetActive(true);
	AddObject(m_soundBase);

	//===================== フェード描画 =========================
	//スタートボタン（デフォルト：表示）
	m_startFade = std::make_shared<C_UIFade>();
	m_startFade->Init(START_POS, START_RECT, buttonTex);
	m_startFade->SetActive(true);
	AddObject(m_startFade);

	//音量設定ボタン（デフォルト：非表示）
	m_soundFade = std::make_shared<C_UIFade>();
	m_soundFade->Init(SOUND_POS, SOUND_RECT, buttonTex);
	m_soundFade->SetActive(false);
	AddObject(m_soundFade);

	//変数
	m_isUpKey = false;
	m_isDownKey = false;
	m_isSpaceKey = false;

	m_cursorIndex = 0;
}

void TitleScene::MoveCursor()
{
	bool currentUpKey = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
	bool currentDownKey = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
	bool currentSpaceKey = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

	if (currentUpKey && !m_isUpKey)
	{
		m_cursorIndex = (m_cursorIndex - 1 + 2) % 2;
		UpdateCursorUI();
	}
	if (currentDownKey && !m_isDownKey)
	{
		m_cursorIndex = (m_cursorIndex + 1) % 2;
		UpdateCursorUI();
	}

	m_isUpKey = currentUpKey;
	m_isDownKey = currentDownKey;
	m_isSpaceKey = currentSpaceKey;
}

void TitleScene::UpdateCursorUI()
{
	//startボタン：0、soundボタン：1
	bool startselected = (m_cursorIndex == 0);

	//============== 表示するUI ===============
	//選択状態のスタートボタン
	m_startFade->SetActive(startselected);
	//未選択状態のサウンドボタン
	m_soundBase->SetActive(startselected);

	//============= 表示しないUI ==============
	//選択状態のサウンドボタン
	m_soundFade->SetActive(!startselected);
	//未選択状態のスタートボタン
	m_startBase->SetActive(!startselected);

}
