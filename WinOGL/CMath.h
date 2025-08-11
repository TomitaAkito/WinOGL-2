#pragma once
#include <math.h>
#include "CVertex.h"
#include "CVector.h"

class CMath{
public:
	/// <summary>
	/// 2点間の距離を計算
	/// </summary>
	/// <param name="vertex1">頂点1のX座標</param>
	/// <param name="vertex2">頂点2のY座標</param>
	/// <returns>2点間の距離</returns>
	float calcDistance(CVertex* vertex1, CVertex* vertex2);

	/// <summary>
	/// ベクトルの外積を計算
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	/// <returns>外積の結果</returns>
	float calcCrossProduct(CVector* a, CVector* b);

	/// <summary>
	/// 座標が一致しているか確認する
	/// </summary>
	/// <param name="a">頂点 a</param>
	/// <param name="b">頂点 b</param>
	/// <returns>一致している場合はtrue、していない場合はfalse</returns>
	bool isXYZ(CVertex* a, CVertex* b);
};

