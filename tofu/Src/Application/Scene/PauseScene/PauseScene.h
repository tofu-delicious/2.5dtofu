//PauseScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

//前方宣言
class C_UIBase;
class C_UIFade;

class C_PauseScene :public C_BaseScene
{
public:
	C_PauseScene();
	~C_PauseScene();

private:

	//============ 関数 ==============
	void Event() override;
	void Init()  override;

	//============ 定数 ==============
	static constexpr Math::Vector3 BACKGROUND_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACKGROUND_RECT = { 0,0,1280,720 };
	static constexpr float BACKGROUND_ALPHA = 0.6f;

	static constexpr Math::Vector3 BACK_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACK_RECT = { 0,0,224,288 };

	static constexpr Math::Vector3 RESUME_POS = { 0.0f,85.0f,0.0f };
	static constexpr Math::Rectangle RESUME_RECT = { 0,0,192,64 };

	static constexpr Math::Vector3 RETRY_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle RETRY_RECT = { 0,64,192,64 };

	static constexpr Math::Vector3 TITLE_POS = { 0.0f,-85.0f,0.0f };
	static constexpr Math::Rectangle TITLE_RECT = { 0,128,192,64 };

	//======== インスタンス ==========
	std::shared_ptr<C_UIBase> m_backGround = nullptr;	//半透明の背景
	std::shared_ptr<C_UIBase> m_back = nullptr;			//背景
	std::shared_ptr<C_UIBase> m_resume = nullptr;		//続けるボタン
	std::shared_ptr<C_UIBase> m_retry = nullptr;		//リトライボタン
	std::shared_ptr<C_UIBase> m_title = nullptr;		//タイトルボタン
};