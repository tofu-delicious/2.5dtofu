//UIAppearFade.cpp
#include "UIAppearFade.h"

void C_UIAppearFade::Update()
{
	if (m_isFadeEnd) return;

	//もし不透明度が1.0fになればフェード処理を行わない
	if (Fade())
	{
		m_isFadeEnd = true;
	}
}

bool C_UIAppearFade::Fade()
{
	m_alpha += FADE_STEP;

	if (m_alpha > MAX_ALPHA)
	{
		//不透明度100%になればtrueを返す
		m_alpha = MAX_ALPHA;
		return true;
	}
	return false;
}
