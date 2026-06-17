// BackGroundScroller.cpp
#include "BackGroundScroller.h"
#include "../../Asset/AssetManager.h"

void C_BackGroundScroller::Init()
{
	// C_Tileと同じ取得方法
	m_polygon = C_AssetManager::Instance().GetPolygon("Tile");

	// 2枚を横に並べて初期配置
	m_panels[0].pos = INITIAL_POS;
	m_panels[1].pos = { INITIAL_POS.x + BG_WIDTH, INITIAL_POS.y, INITIAL_POS.z };

	// 初期行列を計算
	for (auto& panel : m_panels)
	{
		panel.UpdateMatrix();
	}
}

void C_BackGroundScroller::Update()
{
	for (auto& panel : m_panels)
	{
		// 左へ移動
		//panel.pos.x -= SCROLL_SPEED;

		// 左端を超えたらもう1枚の右隣へワープ
		if (panel.pos.x < RECYCLE_THRESHOLD)
		{
			panel.pos.x += BG_WIDTH * 2.0f;
		}

		panel.UpdateMatrix();
	}
}

void C_BackGroundScroller::DrawUnLit()
{
	// C_Tileと同じ描画方法
	for (auto& panel : m_panels)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, panel.mat);
	}
}

void C_BackGroundScroller::ImGui()
{
	//Sameline()：次のウィジェットを横方向に位置付ける
	ImGui::SameLine();

	if (ImGui::Button("Back")) m_isDebugOpen = !m_isDebugOpen;

	if (m_isDebugOpen)
	{
		ImGui::DragFloat("m_scaleX", &m_scaleX, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("m_scaleY", &m_scaleY, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("m_scaleZ", &m_scaleZ, 0.1f, 0.0f, 100.0f);
	}
}
