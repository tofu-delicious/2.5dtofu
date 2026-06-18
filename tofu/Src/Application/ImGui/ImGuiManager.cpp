//ImGuiManager.cpp
#include "ImGuiManager.h"
#include "../Camera/Camera.h"
#include "../Object/Kitchen/Kitchen/Kitchen.h"
#include "../Object/Kitchen/KitchenManager.h"
#include "../Object/Tofu/Tofu.h"
#include "../Object/Tile/BackGroundScroller.h"
#include "../Object/Gimmick/Vessel/Pot/Pot.h"

void C_ImGuiManager::ImGui()
{
	if (ImGui::Begin("Log Window"))
	{
		//=======================================
		// 各クラスのImGui関数はここに呼び出す！
		//=======================================

		if (m_pCamera)					m_pCamera->ImGui();				//C_Camera
		//if (!m_wpKitchen.expired())		m_wpKitchen.lock()->ImGui();//C_Kitchen
		if (!m_wpKitchenMgr.expired())	m_wpKitchenMgr.lock()->ImGui();	//C_KitchenManager
		if (!m_wpTofu.expired())		m_wpTofu.lock()->ImGui();		//C_Tofu
		if (!m_wpBack.expired())		m_wpBack.lock()->ImGui();		//C_BackGroundScroller
		if (!m_wpPot.expired())			m_wpPot.lock()->ImGui();		//C_Pot
	}
	ImGui::End();
}
