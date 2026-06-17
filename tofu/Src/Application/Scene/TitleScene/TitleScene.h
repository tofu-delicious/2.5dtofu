#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class C_UIBase;			//普通に表示させたいとき
class C_UIFade;			//常にフェードして表示させたいとき
class C_UIAppearFade;	//最初だけフェードさせたいとき

class TitleScene : public C_BaseScene
{
public :

	TitleScene();
	~TitleScene();

	//カーソル移動処理
	void MoveCursor();

	//更新内容
	void UpdateCursorUI();

private :

	//============ 関数 ==============
	void Event() override;
	void Init()  override;

	//============ 定数 ==============
	static constexpr Math::Vector3 CAMERA_POS = { 0.0f,0.0f,-1.0f };
	static constexpr float CAMERA_ROTATE = 0.0f;

	static constexpr Math::Vector3 TILE_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle TILE_RECT = { 0,0,1280,720 };

	static constexpr Math::Vector3 START_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle START_RECT = { 0,0,192,64 };

	static constexpr Math::Vector3 SOUND_POS = { 0.0f,-100.0f,0.0f };
	static constexpr Math::Rectangle SOUND_RECT = { 0,64,192,64 };

	//======== インスタンス ==========
	std::shared_ptr<C_UIBase> m_tile = nullptr;		//タイル（背景）
	//　通常描画
	std::shared_ptr<C_UIBase> m_startBase = nullptr;	//スタートボタン（未選択時）
	std::shared_ptr<C_UIBase> m_soundBase = nullptr;	//サウンドボタン（未選択時）

	// フェード描画
	std::shared_ptr<C_UIFade> m_startFade = nullptr;	//スタートボタン（選択時）
	std::shared_ptr<C_UIFade> m_soundFade = nullptr;	//サウンドボタン（選択時）

	//========== 状態フラグ ==========
	bool m_isUpKey = false;			//true：上キーが押された
	bool m_isDownKey = false;		//true：下キーが押された
	bool m_isSpaceKey = false;		//true：スペースキーが押された

	//=========== 動的配列 ===========
	int m_cursorIndex = 0;			//ボタンUIのUIBase・UIFadeの切り替え
};
