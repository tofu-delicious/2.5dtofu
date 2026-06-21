#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Sound/SoundManager.h"
#include "../../UI/UIBase/UIBase.h"
#include "../../UI/UIFade/UIFade.h"
#include "../../UI/UIAppearFade/UIAppearFade.h"
#include "../../Camera/Camera.h"

TitleScene::TitleScene() { Init(); }

TitleScene::~TitleScene(){}

void TitleScene::Event()
{
	MoveCursor();
}

void TitleScene::Init()
{
	//画像データロード
	std::shared_ptr<KdTexture> tileTex = C_AssetManager::Instance().GetTex("Tile");
	std::shared_ptr<KdTexture> lineTex = C_AssetManager::Instance().GetTex("Line");	
	std::shared_ptr<KdTexture> buttonTex = C_AssetManager::Instance().GetTex("TitleButton");

	//タイル
	m_tile = std::make_shared<C_UIBase>();
	m_tile->Init(TILE_POS, TILE_RECT, tileTex);
	m_tile->SetActive(true);
	AddObject(m_tile);

	//カーソル
	m_line = std::make_shared<C_UIBase>();
	m_line->Init(LINE_POS, LINE_RECT, lineTex);
	m_line->SetActive(true);
	AddObject(m_line);

	//スタートボタン（デフォルト：非表示）
	m_start = std::make_shared<C_UIBase>();
	m_start->Init(START_POS, START_RECT, buttonTex);
	m_start->SetActive(true);
	AddObject(m_start);

	//サウンドボタン（デフォルト：表示）
	m_sound = std::make_shared<C_UIBase>();
	m_sound->Init(SOUND_POS, SOUND_RECT, buttonTex);
	m_sound->SetActive(true);
	AddObject(m_sound);

	//変数
	m_isUpKey = false;
	m_isDownKey = false;

	//BGM再生
	C_SoundManager::Instance().PlayBGM("Asset/Sounds/title.wav");
}

void TitleScene::MoveCursor()
{
	bool currentUpKey = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
	bool currentDownKey = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;

	if (currentUpKey && !m_isUpKey)
	{
		if (m_titleData == TitleData::Sound)
		{
			m_titleData = TitleData::Start;
		}
	}
	else if (currentDownKey && !m_isDownKey)
	{
		if (m_titleData == TitleData::Start)
		{
			m_titleData = TitleData::Sound;
		}
	}
	else if (KdInputManager::Instance().IsPress("Select"))
	{
		if (m_titleData == TitleData::Start)
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
		else if (m_titleData == TitleData::Sound)
		{
			SceneManager::Instance().PushOverlay(SceneManager::SceneType::Setting);
		}
	}

	UpdateCursorPos();

	m_isUpKey = currentUpKey;
	m_isDownKey = currentDownKey;
}

void TitleScene::UpdateCursorPos()
{
	if (m_titleData == TitleData::Start)
	{
		m_line->SetPos(m_start->GetPos());
	}
	else if (m_titleData == TitleData::Sound)
	{
		m_line->SetPos(m_sound->GetPos());
	}
}
