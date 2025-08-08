#pragma once
#include <math.h>
#include "CVertex.h"
#include "CVector.h"

class CMath{
public:
	/// <summary>
	/// 2�_�Ԃ̋������v�Z
	/// </summary>
	/// <param name="vertex1">���_1��X���W</param>
	/// <param name="vertex2">���_2��Y���W</param>
	/// <returns>2�_�Ԃ̋���</returns>
	float calcDistance(CVertex* vertex1, CVertex* vertex2);
};

