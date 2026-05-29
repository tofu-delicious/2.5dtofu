//Camera.h
#pragma once

class C_Camera
{
public:
	C_Camera(){}
	~C_Camera(){}

	void Init();
	void Update();

private:

	std::unique_ptr<KdCamera> m_spCamera = nullptr;

};