//SettingScene.cpp
#include "SettingScene.h"
#include "../BaseScene/BaseScene.h"
#include "../SceneManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Sound/SoundManager.h"
#include "../../Camera/Camera.h"
#include "../../UI/UIBase/UIBase.h"

C_SettingScene::C_SettingScene() { Init(); }

C_SettingScene::~C_SettingScene(){}

void C_SettingScene::Event()
{
	//カーソル移動
	MoveCursor();
}

void C_SettingScene::Init()
{
	//画像ロード
	std::shared_ptr<KdTexture> backGroundTex = C_AssetManager::Instance().GetTex("BackGround");
	std::shared_ptr<KdTexture> backTex = C_AssetManager::Instance().GetTex("SettingBack");
	std::shared_ptr<KdTexture> lineTex = C_AssetManager::Instance().GetTex("Line");
	std::shared_ptr<KdTexture> buttonTex = C_AssetManager::Instance().GetTex("SettingButton");
	std::shared_ptr<KdTexture> frameTex = C_AssetManager::Instance().GetTex("Frame");
	std::shared_ptr<KdTexture> barTex = C_AssetManager::Instance().GetTex("Bar");

	//インスタンス化
	m_backGround = std::make_unique<C_UIBase>();
	m_back = std::make_unique<C_UIBase>();
	m_line = std::make_unique<C_UIBase>();
	m_se = std::make_unique<C_UIBase>();
	m_seFrame = std::make_unique<C_UIBase>();
	m_seBar = std::make_unique<C_UIBase>();
	m_bgm = std::make_unique<C_UIBase>();
	m_bgmFrame = std::make_unique<C_UIBase>();
	m_bgmBar = std::make_unique<C_UIBase>();
	m_backButton = std::make_unique<C_UIBase>();
	
	//初期化
	m_backGround->Init(BACKGROUND_POS,BACKGROUND_RECT,backGroundTex, BACKGROUND_ALPHA);
	m_back->Init(BACK_POS, BACK_RECT, backTex);
	m_line->Init(LINE_POS, LINE_RECT, lineTex);
	m_se->Init(SE_POS, SE_RECT, buttonTex);
	m_seFrame->Init(SE_FRAME_POS, SE_FRAME_RECT, frameTex);
	m_seBar->Init(SE_BAR_POS, SE_BAR_RECT, barTex);
	m_bgm->Init(BGM_POS, BGM_RECT, buttonTex);
	m_bgmFrame->Init(BGM_FRAME_POS, BGM_FRAME_RECT, frameTex);
	m_bgmBar->Init(BGM_BAR_POS, BGM_BAR_RECT, barTex);
	m_backButton->Init(BACKBUTTON_POS, BACKBUTTON_RECT, buttonTex);
	
	//表示
	m_backGround->SetActive(true);
	m_back->SetActive(true);
	m_line->SetActive(true);
	m_se->SetActive(true);
	m_seFrame->SetActive(true);
	m_seBar->SetActive(true);
	m_bgm->SetActive(true);
	m_bgmFrame->SetActive(true);
	m_bgmBar->SetActive(true);
	m_backButton->SetActive(true);

	//m_objListへ追加
	AddObject(m_backGround);
	AddObject(m_back);
	AddObject(m_line);
	AddObject(m_se);
	AddObject(m_seFrame);
	AddObject(m_seBar);
	AddObject(m_bgm);
	AddObject(m_bgmFrame);
	AddObject(m_bgmBar);
	AddObject(m_backButton);

	ApplySEVolume();
	ApplyBGMVolume();
}

void C_SettingScene::MoveCursor()
{
	//現在のキー状態を取得
	bool currentUp = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
	bool currentDown = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
	bool currentRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
	bool currentLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;

	//上下移動
	if (currentUp && !m_isUpKey)
	{
		//元のカーソルが「BGM」の場合
		if (m_settingData == SettingData::BGM)
		{
			m_settingData = SettingData::SE;
		}
		else if (m_settingData == SettingData::Back)
		{
			m_settingData = SettingData::BGM;
		}
	}
	else if (currentDown && !m_isDownKey)
	{
		if (m_settingData == SettingData::SE)
		{
			m_settingData = SettingData::BGM;
		}
		else if (m_settingData == SettingData::BGM)
		{
			m_settingData = SettingData::Back;
		}
	}
	else if (KdInputManager::Instance().IsPress("Select"))
	{
		if (m_settingData == SettingData::Back)
		{
			SceneManager::Instance().PopOverlay();
		}
	}
	//左右移動（音量調整）
	else if (currentRight && !m_isRightKey)
	{
		if (m_settingData == SettingData::SE)
		{
			SEVolume(SoundMode::Up);
		}
		else if (m_settingData == SettingData::BGM)
		{
			BGMVolume(SoundMode::Up);
		}
	}
	else if (currentLeft && !m_isLeftKey)
	{
		if (m_settingData == SettingData::SE)
		{
			SEVolume(SoundMode::Down);
		}
		else if (m_settingData == SettingData::BGM)
		{
			BGMVolume(SoundMode::Down);
		}
	}

	UpdateCursorPos();

	//状態を次フレームに引き継ぐ
	m_isUpKey = currentUp;
	m_isDownKey = currentDown;
	m_isRightKey = currentRight;
	m_isLeftKey = currentLeft;
}

void C_SettingScene::UpdateCursorPos()
{
	if (m_settingData == SettingData::SE)
	{
		m_line->SetPos(m_se->GetPos());
	}
	else if (m_settingData == SettingData::BGM)
	{
		m_line->SetPos(m_bgm->GetPos());
	}
	else if (m_settingData == SettingData::Back)
	{
		m_line->SetPos(m_backButton->GetPos());
	}
}

void C_SettingScene::ApplySEVolume()
{
	m_seVolumeLevel = static_cast<int>(C_SoundManager::Instance().GetSEVolume() * MAX_VOLUME);
	float ratio = static_cast<float>(m_seVolumeLevel) / static_cast<float>(MAX_VOLUME);
	float newPosX = m_seFrame->GetPos().x - (SE_FRAME_WIDTH * 0.5f) * (1.0f - ratio);
	m_seBar->SetScale(ratio);
	m_seBar->SetPos({ newPosX,130.0f,0.0f });
}

void C_SettingScene::ApplyBGMVolume()
{
	m_bgmVolumeLevel = static_cast<int>(C_SoundManager::Instance().GetBGMVolume() * MAX_VOLUME);
	float ratio = static_cast<float>(m_bgmVolumeLevel) / static_cast<float>(MAX_VOLUME);;
	float newPosX = m_seFrame->GetPos().x - (BGM_FRAME_WIDTH * 0.5f) * (1.0f - ratio);
	m_bgmBar->SetScale(ratio);
	m_bgmBar->SetPos({ newPosX,-30.0f ,0.0f});
}

void C_SettingScene::SEVolume(const SoundMode& a_soundMode)
{
	if (a_soundMode == SoundMode::Up)
	{
		//音量レベルを1つ分上げる
		if (m_seVolumeLevel < MAX_VOLUME)m_seVolumeLevel += 1;
	}
	else
	{
		if (m_seVolumeLevel > MIN_VOLUME)m_seVolumeLevel -= 1;
	}

	//音量レベルから直接scaleと座標を決定
	float ratio = static_cast<float>(m_seVolumeLevel) / static_cast<float>(MAX_VOLUME);
	float newPosX = m_seFrame->GetPos().x - (SE_FRAME_WIDTH * 0.5f) * (1.0f - ratio);
	m_seBar->SetScale(ratio);
	m_seBar->SetPos({ newPosX,130.0f,0.0f });
	
	C_SoundManager::Instance().GroupVolume(C_SoundManager::SoundType::SE,m_seVolumeLevel * 0.1f);
}

void C_SettingScene::BGMVolume(const SoundMode& a_soundMode)
{
	if (a_soundMode == SoundMode::Up)
	{
		//音量レベルを1つ分上げる
		if (m_bgmVolumeLevel < MAX_VOLUME)m_bgmVolumeLevel += 1;
	}
	else
	{
		if (m_bgmVolumeLevel > MIN_VOLUME)m_bgmVolumeLevel -= 1;
	}

	//音量レベルから直接scaleと座標を決定
	float ratio = static_cast<float>(m_bgmVolumeLevel) / static_cast<float>(MAX_VOLUME);;
	float newPosX = m_bgmFrame->GetPos().x - (BGM_FRAME_WIDTH * 0.5f) * (1.0f - ratio);
	m_bgmBar->SetScale(ratio);
	m_bgmBar->SetPos({ newPosX,-30.0f ,0.0f});

	C_SoundManager::Instance().GroupVolume(C_SoundManager::SoundType::BGM, m_bgmVolumeLevel * 0.1f);
}
