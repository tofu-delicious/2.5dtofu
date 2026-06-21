//SettingScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

class C_UIBase;
class C_UIFade;

class C_SettingScene :public C_BaseScene
{
public:

	//ボタンの種類
	enum class SettingData
	{
		SE,
		BGM,
		Back,
	};

	//音量の種類
	enum class SoundMode
	{
		Up,		//音量アップ
		Down,	//音量ダウン
	};


	C_SettingScene();
	~C_SettingScene();

	//カーソル処理
	void MoveCursor();
	void UpdateCursorPos();

	//ボリューム調整（初期化用）
	void ApplySEVolume();
	void ApplyBGMVolume();

	//ボリューム調整（更新）
	void SEVolume(const SoundMode& a_soundMode);
	void BGMVolume(const SoundMode& a_soundMode);

private:

	//============ 関数 ==============
	void Event() override;
	void Init()  override;

	//============ 定数 ==============
	static constexpr Math::Vector3 BACKGROUND_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACKGROUND_RECT = { 0,0,1280,720 };
	static constexpr float BACKGROUND_ALPHA = 0.6f;

	static constexpr Math::Vector3 BACK_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACK_RECT = { 0,0,850,500 };

	static constexpr Math::Vector3 LINE_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle LINE_RECT = { 0,0,256,16 };

	static constexpr Math::Vector3 SE_POS = { -300.0f,130.0f,0.0f };
	static constexpr Math::Rectangle SE_RECT = { 0,0,112,64 };

	static constexpr Math::Vector3 SE_FRAME_POS = { 100.0f,130.0f,0.0f };
	static constexpr Math::Rectangle SE_FRAME_RECT = { 0,0,604,64 };

	static constexpr Math::Vector3 SE_BAR_POS = { 100.0f,130.0f,0.0f };
	static constexpr Math::Rectangle SE_BAR_RECT = { 0,0,600,60 };

	static constexpr Math::Vector3 BGM_POS = { -300.0f,-30.0f,0.0f };
	static constexpr Math::Rectangle BGM_RECT = { 0,64,112,64 };

	static constexpr Math::Vector3 BGM_FRAME_POS = { 100.0f,-30.0f,0.0f };
	static constexpr Math::Rectangle BGM_FRAME_RECT = { 0,0,604,64 };

	static constexpr Math::Vector3 BGM_BAR_POS = { 100.0f,-30.0f,0.0f };
	static constexpr Math::Rectangle BGM_BAR_RECT = { 0,0,600,60 };

	static constexpr Math::Vector3 BACKBUTTON_POS = { -300.0f,-190.0f,0.0f };
	static constexpr Math::Rectangle BACKBUTTON_RECT = { 0,128,112,64 };

	static constexpr float SE_FRAME_WIDTH = 604.0f;
	static constexpr float BGM_FRAME_WIDTH = 604.0f;

	static constexpr int MAX_VOLUME = 10;	//最大ボリューム
	static constexpr int MIN_VOLUME = 0;	//最小ボリューム

	float SE_POSX = 0.0f;	//座標補正のX軸方向の座標値
	float BGM_POSX = 0.0f;	//座標補正のY軸方向の座標値

	//======== インスタンス ==========
	std::shared_ptr<C_UIBase> m_backGround = nullptr;	//薄い背景
	std::shared_ptr<C_UIBase> m_back = nullptr;			//背景
	std::shared_ptr<C_UIBase> m_line = nullptr;			//カーソル
	std::shared_ptr<C_UIBase> m_se = nullptr;			//「SE」テキスト
	std::shared_ptr<C_UIBase> m_seFrame = nullptr;		//SEフレーム
	std::shared_ptr<C_UIBase> m_seBar = nullptr;		//SEバー
	std::shared_ptr<C_UIBase> m_bgm = nullptr;			//「BGM」テキスト
	std::shared_ptr<C_UIBase> m_bgmFrame = nullptr;		//BGMフレーム
	std::shared_ptr<C_UIBase> m_bgmBar = nullptr;		//BGMバー
	std::shared_ptr<C_UIBase> m_backButton = nullptr;	//戻るボタン
	
	//========== 状態フラグ ==========
	bool m_isUpKey = false;			//true：上キーが押された
	bool m_isDownKey = false;		//true：下キーが押された
	bool m_isRightKey = false;		//true：右キーが押された
	bool m_isLeftKey = false;		//true：左キーが押された

	//=========== 動的変数 ===========
	SettingData m_settingData = SettingData::SE;

	int m_seVolumeLevel;			//SEボリューム
	int m_bgmVolumeLevel;			//BGMボリューム

};