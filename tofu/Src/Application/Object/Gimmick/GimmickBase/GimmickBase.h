//GimmickBase.h
#pragma once
#include "../../ObjectBase/ObjectBase.h"

class C_GimmickBase : public C_ObjectBase
{
public:
	C_GimmickBase() {}
	virtual ~C_GimmickBase() {}

	void Init()         override {}
	void PreUpdate()    override {}
	void Update()       override {}
	void PostUpdate()   override {}
	void DrawLit()      override {}

	//座標確定処理
	virtual void UpdateMatrix(){}
};