//UIFade.cpp
#include "UIFade.h"

void C_UIFade::Update()
{
	//フェード処理
	Fade();
}

void C_UIFade::Fade()
{
	m_alpha += m_fadeStep;

	if (m_alpha > MAX_ALPHA)
	{
		m_alpha = MAX_ALPHA;
		m_fadeStep *= -1.0f;
	}
	if (m_alpha < MIN_ALPHA)
	{
		m_alpha = MIN_ALPHA;
		m_fadeStep *= -1.0f;
	}
}
