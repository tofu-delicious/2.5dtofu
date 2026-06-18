//GimmickFactory.h
#pragma once
#include "../GimmickBase/GimmickBase.h"
#include "../Liquid/Water/Water.h"				//水
#include "../Liquid/Oil/Oil.h"					//油
#include "../Vessel/Pot/Pot.h"					//鍋
#include "../Tool/CuttingBoard/CuttingBoard.h"	//まな板

class C_GimmickFactory
{
public:
	C_GimmickFactory() {}
	~C_GimmickFactory() {}

	// 1キッチン分のギミックリストを取得
	// キッチンのX座標を受け取り、相対位置でギミックを配置する
	std::vector<std::shared_ptr<C_GimmickBase>> GetNextPattern(float kitchenBaseX, float scrollSpeed);

private:
	// ギミック配置データ（1エントリ = 1ギミック）
	struct GimmickPlacement
	{
		C_GimmickBase::GimmickType type;	//大分類
		int subType;						//小分類（種類ごとに番号で管理）
		float offsetX;	// キッチン先頭からの相対X
		float offsetY;
		float offsetZ;
	};

	//小分類の番号定義
	enum LiquidSubType { Water = 0,Oil = 1};
	enum VesselSubType { Pot = 0};
	enum ToolSubType   { Obstacle = 0};

	// キッチンごとのパターン定義
	// 外側vector = キッチン番号、内側vector = そのキッチンのギミック配置
	static const std::vector<std::vector<GimmickPlacement>> PATTERN;

	int m_currentIndex = 0;
};
