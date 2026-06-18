//GimmickBase.cpp
#include "GimmickBase.h"

void C_GimmickBase::Update()
{
	//キッチンと同じ速度でスクロール
	Math::Vector3 pos = GetPos();
	pos.x -= m_scrollSpeed;
	SetPos(pos);

	//画面外に出たら消滅フラグ
	if (pos.x < -3.0f) { m_isExpired = true; }
}
