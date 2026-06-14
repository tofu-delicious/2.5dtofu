//UIFade.h
#pragma once
#include "../UIBase/UIBase.h"

class C_UIFade:public C_UIBase
{
public:
	C_UIFade(){}
	~C_UIFade() override{}

	void Update()override;

	//フェード処理
	void Fade();

	void SetCamera(std::shared_ptr<KdCamera> a_spCamera) { m_wpCamera = a_spCamera; }

private:

	//============ 定数 =============
	static constexpr float MAX_ALPHA = 0.8f;
	static constexpr float MIN_ALPHA = 0.3f;

	//========== 動的変数 ===========
	float m_fadeStep = -0.01f;
};