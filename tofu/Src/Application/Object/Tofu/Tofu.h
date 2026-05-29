//Tofu.h
#pragma once
#include "../ObjectBase/ObjectBase.h"

class C_Tofu:public C_ObjectBase
{
public:
	C_Tofu(){}
	~C_Tofu(){}

	void Init()			override;
	void PreUpdate()	override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

private:

};