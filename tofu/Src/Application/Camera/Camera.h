//Camera.h
#pragma once

class C_Camera
{
public:
	C_Camera();
	~C_Camera();

	void Init();
	void Update();

	void SetShader();

private:

	std::unique_ptr<KdCamera> m_spCamera = nullptr;

	//============== 動的変数 ================
	Math::Vector3 m_pos = {};

};