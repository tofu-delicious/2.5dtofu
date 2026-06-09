//Camera.h
#pragma once

//前方宣言
class C_Tofu;

class C_Camera
{
public:
	C_Camera();
	~C_Camera();

	void Init();
	void Update();

	void SetShader();

	void ImGui();

	//============ セッター ===========
	void SetTofu(std::shared_ptr<C_Tofu>& a_tofu) { m_tofu = a_tofu; }

private:

	std::unique_ptr<KdCamera> m_spCamera = nullptr;
	std::weak_ptr<C_Tofu> m_tofu;

	//============= 状態フラグ ===============
	bool m_isDebugOpen = false;

	//============== 動的変数 ================
	Math::Vector3 m_pos = {};

};