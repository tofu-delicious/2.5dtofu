//UIBase.h
#pragma once

class C_UIBase :public KdGameObject
{
public:
	C_UIBase();
	virtual ~C_UIBase();

	void Init();

private:

	Math::Vector2 m_pos;				//座標
	Math::Rectangle m_rect;				//画像範囲指定
	std::shared_ptr<KdTexture> m_tex;	//画像用
	float m_radiusX;					//X軸方向の半径
	float m_radiusY;					//Y軸方向の半径
	float m_scaleX;						//X軸方向の拡縮
	float m_scaleY;						//Y軸方向の拡縮
	float m_rotate;						//回転角度
	float m_alpha;						//不透明度
	float m_fadeStep;					//フェード用
	float m_maxFade;					//最大不透明度
	bool m_isActive;					//状態フラグ

	KdTexture
};