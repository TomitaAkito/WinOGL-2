#pragma once
#include <math.h>
#include "CVertex.h"
#include "CVector.h"
#include "CShape.h"

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
	/// �x�N�g���̓��ς��v�Z
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <param name="b">�x�N�g�� b</param>
	/// <returns>���ς̌���</returns>
	float calcInnerProduct(CVector* a, CVector* b);

	/// <summary>
	/// ���W����v���Ă��邩�m�F
	/// </summary>
	/// <param name="a">���_ a</param>
	/// <param name="b">���_ b</param>
	/// <returns>��v���Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false</returns>
	bool isXYZ(CVertex* a, CVertex* b);

	/// <summary>
	/// 2�̐����̐����p�x���v�Z
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <param name="b">�x�N�g�� b</param>
	/// <returns>�p�x</returns>
	float calcAngle(CVector* a, CVector* b);

	/// <summary>
	/// �Y���}�`�ƒ��_�̂Ȃ��p���Z�o
	/// </summary>
	/// <param name="currentShape">�}�`</param>
	/// <param name="vertex">���_</param>
	/// <returns>�p�x</returns>
	float calcAngleByShape(CShape* currentShape, CVertex* vertex);

	/// <summary>
	/// float�^�̐����̐�Βl��Ԃ�
	/// </summary>
	/// <param name="value">float�^�̐���</param>
	/// <returns>��Βl�̐���</returns>
	float absFloat(float value);

	/// <summary>
	/// ���Ɠ_�̋������Z�o����
	/// </summary>
	/// <param name="lineStart">���̎n�_</param>
	/// <param name="lineEnd">���̏I�_</param>
	/// <param name="vertex">�_</param>
	/// <returns>����</returns>
	float calcPointLineDistance(CVertex* lineStart, CVertex* lineEnd, CVertex* vertex);

	/// <summary>
	/// �x�N�g������sin�Ƃ��Z�o
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <param name="b">�x�N�g�� b</param>
	/// <returns>sin��</returns>
	float calcSinTheta(CVector* a, CVector* b);
	
	/// <summary>
	/// �x�N�g���̑傫�����Z�o
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <returns>�x�N�g���̑傫��</returns>
	float calcVectorDistance(CVector* a);

	/// <summary>
	/// �����̒��_����ړ��ʂ��Z�o���Ĕz��Ɋi�[
	/// </summary>
	/// <param name="beforVertex">���̒��_</param>
	/// <param name="afterVertex">�ړ���̒��_</param>
	/// <param name="result">���ʂ��i�[(�V���A���C�Y�E�f�V���A���C�Y�͌Ăяo�����ōs��)</param>
	void calcMovementByVertex(CVertex* beforVertex, CVertex* afterVertex, float(&result)[2]);
};

