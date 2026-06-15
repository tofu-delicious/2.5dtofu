//UIBase.h
#pragma once

class C_UIBase :public KdGameObject
{
public:
	C_UIBase(){}
	~C_UIBase()override{}

	void Init(
		const Math::Vector3& a_pos,
		const Math::Rectangle& a_rect,
		std::shared_ptr<KdTexture> a_tex,
		float a_alpha = 1.0f,
		float a_scaleX = 1.0f,
		float a_scaleY = 1.0f,
		float a_rotate = 0.0f);

	void DrawSprite()override;

protected:

	//============== 動的変数 ===============
	Math::Vector3 m_pos;				//座標
	Math::Rectangle m_rect;				//画像範囲指定
	std::shared_ptr<KdTexture> m_tex;	//画像用
	float m_scaleX;						//X軸方向の拡縮
	float m_scaleY;						//Y軸方向の拡縮
	float m_rotate;						//回転角度
	float m_alpha;						//不透明度
};