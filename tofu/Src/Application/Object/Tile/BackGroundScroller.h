//BackGroundScroller.h
#pragma once
#include "../ObjectBase/ObjectBase.h"

class C_BackGroundScroller :public C_ObjectBase
{
public:

	C_BackGroundScroller(){}
	~C_BackGroundScroller(){}

	void Init();
	void Update();
	void DrawUnLit();
	
	void ImGui();

private:
	//背景1枚分の状態を持つ内部構造体
	struct backGroundPanel
	{
		Math::Vector3 pos;
		Math::Matrix mat;

		void UpdateMatrix()
		{
			Math::Matrix scaleMat = Math::Matrix::CreateScale(7,7,1);
			Math::Matrix transMat = Math::Matrix::CreateTranslation(pos);
			mat = scaleMat * transMat;
		}
	};

	//板ポリゴンのデータ（2枚で使いまわす）
	std::shared_ptr<KdSquarePolygon> m_polygon = nullptr;

	//2枚のパネル
	std::array<backGroundPanel, 2> m_panels;

	//=============== 定数 ===================
	static constexpr Math::Vector3 INITIAL_POS = { 0.0f,0.0f,2.0f };
	static constexpr float BG_WIDTH = 10.0f;							//背景画像の横幅
	static constexpr float SCROLL_SPEED = 0.01f;						//スクロール速度
	static constexpr float RECYCLE_THRESHOLD = -BG_WIDTH;
	
};