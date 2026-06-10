//ImGuiManager.cpp
#include "ImGuiManager.h"
#include "../Camera/Camera.h"
#include "../Object/Kitchen/Kitchen/Kitchen.h"
#include "../Object/Kitchen/KitchenManager.h"
#include "../Object/Tofu/Tofu.h"

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

	}
	ImGui::End();
}
