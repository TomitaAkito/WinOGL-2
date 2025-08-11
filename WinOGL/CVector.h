#pragma once
#include "CVertex.h"
class CVector{

#pragma region �����o�ϐ�
private:
	float x; // X����
	float y; // Y����
#pragma endregion

#pragma region �R���X�g���N�^�E�f�X�g���N�^
public:
	// �f�t�H���g�R���X�g���N�^
	CVector();
	// �R���X�g���N�^�i��������j
	CVector(float x, float y);
	// �R���X�g���N�^�i���_�^�j
	CVector(CVertex* a, CVertex* b);
	// �f�X�g���N�^
	~CVector();
#pragma endregion

#pragma region Set�n/Get�n
public:

	/// <summary>
	/// X������ݒ�
	/// </summary>
	/// <param name="x">X����</param>
	void SetX(float x);

	/// <summary>
	/// X�������擾
	/// </summary>
	/// <returns>X����</returns>
	float GetX();

	/// <summary>
	/// Y������ݒ�
	/// </summary>
	/// <param name="y">Y����</param>
	void SetY(float y);

	/// <summary>
	/// Y�������擾
	/// </summary>
	/// <returns>Y����</returns>
	float GetY();

	/// <summary>
	/// ���_����x�N�g�����Z�o���Ċi�[
	/// </summary>
	/// <param name="a">�x�N�g�� a</param>
	/// <param name="b">�x�N�g�� b</param>
	void SetByVertex(CVertex* a,CVertex* b);
};

