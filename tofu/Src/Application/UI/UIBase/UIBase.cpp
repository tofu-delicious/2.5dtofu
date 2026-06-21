#include "UIBase.h"


void C_UIBase::Init(const Math::Vector3& a_pos, const Math::Rectangle& a_rect, std::shared_ptr<KdTexture> a_tex, float a_alpha, float a_scaleX, float a_scaleY,float a_rotate)
{
	m_pos = a_pos;
	m_rect = a_rect;
	m_tex = a_tex;
	m_alpha = a_alpha;
	m_scaleX = a_scaleX;
	m_scaleY = a_scaleY;
	m_rotate = a_rotate;
	m_isActive = false;
}

void C_UIBase::Update()
{
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;   // 先にスケール(原点基準)、その後で平行移動
}

void C_UIBase::DrawSprite()
{
	if (!m_isActive)return;

	//不透明度指定
	Math::Color color(1.0f, 1.0f, 1.0f, m_alpha);

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mWorld);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex,0,0,m_rect.width,m_rect.height, &m_rect, &color);
}
