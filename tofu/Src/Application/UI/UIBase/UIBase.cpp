#include "UIBase.h"


void C_UIBase::Init(const Math::Vector3& a_pos, const Math::Rectangle& a_rect, std::shared_ptr<KdTexture> a_tex, float a_scaleX, float a_scaleY,float a_rotate, float a_alpha)
{
	m_pos = a_pos;
	m_rect = a_rect;
	m_tex = a_tex;
	m_scaleX = a_scaleX;
	m_scaleY = a_scaleY;
	m_rotate = a_rotate;
	m_alpha = a_alpha;
}

void C_UIBase::DrawSprite()
{
	//カメラが生存していなければ描画しない
	if (m_wpCamera.expired())return;

	//2D座標格納用変数
	Math::Vector3 v2DPos = Math::Vector3::Zero;

	//3D座標を2D座標に変換
	m_wpCamera.lock()->ConvertWorldToScreenDetail(m_pos, v2DPos);

	//不透明度指定
	Math::Color color(1.0f, 1.0f, 1.0f, m_alpha);

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, v2DPos.x, v2DPos.y, &m_rect, &color);
}
