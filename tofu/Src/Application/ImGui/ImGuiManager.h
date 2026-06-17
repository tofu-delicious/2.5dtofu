//ImGuiManager.h
#pragma once

//前方宣言
class C_Camera;
class C_Kitchen;
class C_KitchenManager;
class C_Tofu;
class C_BackGroundScroller;

class C_ImGuiManager
{
public:
	
	~C_ImGuiManager(){}

	void ImGui();

	//======================= セッター =============================
	void SetCamera(C_Camera* a_pCamera) { m_pCamera = a_pCamera; }
	//void SetKitchen(std::shared_ptr<C_Kitchen> a_spKitchen) { m_wpKitchen = a_spKitchen;}
	void SetKitchenMgr(std::shared_ptr<C_KitchenManager> a_spKitchenMgr) { m_wpKitchenMgr = a_spKitchenMgr; }
	void SetTofu(std::shared_ptr<C_Tofu> a_spTofu) { m_wpTofu = a_spTofu; }
	void SetBack(std::shared_ptr<C_BackGroundScroller> a_spBack) { m_wpBack = a_spBack; }

private:

	C_ImGuiManager(){}

	//=========== 調査したいクラスのインスタンスを記述 =============
	C_Camera* m_pCamera = nullptr;
	//std::weak_ptr<C_Kitchen> m_wpKitchen;
	std::weak_ptr<C_KitchenManager> m_wpKitchenMgr;
	std::weak_ptr<C_Tofu> m_wpTofu;
	std::weak_ptr<C_BackGroundScroller> m_wpBack;

public:

	static C_ImGuiManager& Instance()
	{
		static C_ImGuiManager instance;
		return instance;
	}
};