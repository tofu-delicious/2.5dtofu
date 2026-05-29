//ObjectBase.h
#pragma once

class C_ObjectBase:public KdGameObject
{
public:
	C_ObjectBase(){}
	virtual ~C_ObjectBase(){}

	virtual void Init()			override;
	virtual void PreUpdate()	override;
	virtual void Update()		override;
	virtual void PostUpdate()	override;
	virtual void DrawLit()		override;

protected:

	//============== インスタンス ===============
	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;	//2Dポリゴン用：きちんと実体化して使うこと！
	std::shared_ptr<KdModelData> m_model = nullptr;			//3Dモデル用：きちんと実体化して使うこと！

	//================ 動的配列 =================
	Math::Vector3 m_pos = {};			//座標
	Math::Vector3 m_move = {};			//移動量
	Math::Color m_color = { 1,1,1,1 };	//色
	float m_radiusX = 0.0f;				//X軸方向の半径
	float m_radiusY = 0.0f;;			//Y軸方向の半径
	float m_scaleX = 1.0f;				//X軸方向の拡縮
	float m_scaleY = 1.0f;				//Y軸方向の拡縮
	float m_rotate = 0.0f;				//回転角度
	float m_alpha = 0.0f;				//不透明度
	float m_fadeStep = 0.0f;			//フェード用
	bool m_isActive = true;				//true 表示　false 非表示

	//メモ
	//行列：m_mWorld

};