//UIAppearFade.h
#pragma once
#include "../UIBase/UIBase.h"

class C_UIAppearFade:public C_UIBase
{
public:
	C_UIAppearFade(){}
	~C_UIAppearFade()override{}

	void Update()override;

	//フェード処理
	bool Fade();

	void SetCamera(std::shared_ptr<KdCamera> a_spCamera) { m_wpCamera = a_spCamera; }

private:

	//============ 定数 =============
	static constexpr float MAX_ALPHA = 1.0f;
	static constexpr float FADE_STEP = 0.01f;

	//========== 状態フラグ =========
	bool m_isFadeEnd = false;	//フェード処理が終わればtrue

};