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
};

