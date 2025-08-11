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

	/// <summary>
	/// �x�N�g���̊O�ς��v�Z
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <param name="b">�x�N�g�� b</param>
	/// <returns>�O�ς̌���</returns>
	float calcCrossProduct(CVector* a, CVector* b);

	/// <summary>
	/// ���W����v���Ă��邩�m�F����
	/// </summary>
	/// <param name="a">���_ a</param>
	/// <param name="b">���_ b</param>
	/// <returns>��v���Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false</returns>
	bool isXYZ(CVertex* a, CVertex* b);
};

