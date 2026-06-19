//GimmickFactory.h
#pragma once
#include "../GimmickBase/GimmickBase.h"
#include "../Liquid/Water/Water.h"
#include "../Liquid/Oil/Oil.h"
#include "../Vessel/Pot/Pot.h"
#include "../Tool/CuttingBoard/CuttingBoard.h"

class C_GimmickFactory
{
public:
	C_GimmickFactory() {}
	~C_GimmickFactory() {}

	// 「コンロありキッチン」が来るたびに呼ぶ
	// キッチンの先頭X座標を受け取り、パターンに従ってギミックを生成して返す
	std::vector<std::shared_ptr<C_GimmickBase>> GetNextPattern(float a_kitchenBaseX, float a_scrollSpeed);

private:

	// 1ギミック分の配置データ
	struct GimmickPlacement
	{
		C_GimmickBase::GimmickType type;    // 大分類（Vessel / Liquid / Tool）
		int    subType;                     // 小分類（種類ごとの番号）
		float  offsetX;                     // キッチン先頭からの相対X座標
		float  offsetY;                     // 高さ
		float  offsetZ;                     // 奥行き
	};

	// 小分類の番号定義
	enum LiquidSubType { Water = 0, Oil = 1 };
	enum VesselSubType { Pot = 0 };
	enum ToolSubType { CuttingBoard = 0 };

	// コンロありキッチンのパターン定義
	// 外側vector = コンロありキッチンの何番目か
	// 内側vector = そのキッチンに置くギミックの一覧
	static const std::vector<std::vector<GimmickPlacement>> PATTERN;

	// 現在どのパターンを使うかのインデックス（コンロありキッチンが来るたびに進む）
	int m_currentIndex = 0;
};