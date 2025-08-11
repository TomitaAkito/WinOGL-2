#include "pch.h"
#pragma once

class CVertex{
#pragma region �����o�ϐ�
private:
	float x;  // X���W
	float y;  // Y���W
	float z;  // Z���W
	CVertex* next; // ���̒��_�ւ̃|�C���^
	CVertex* pre; // �O�̒��_�ւ̃|�C���^

#pragma endregion

#pragma region �R���X�g���N�^�E�f�X�g���N�^
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CVertex();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CVertex();
#pragma endregion

#pragma region Set�n/Get�n
	/// <summary>
	/// X���W���擾
	/// </summary>
	/// <returns>X���W</returns>
	float GetX();
		
	/// <summary>
	/// Y���W���擾
	/// </summary>
	/// <returns>Y���W</returns>
	float GetY();
		
	/// <summary>
	/// Z���W���擾
	/// </summary>
	/// <returns>Z���W</returns>
	float GetZ();

	/// <summary>
	/// X���W�EY���W��ݒ�
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	void SetXY(float x, float y);

	/// <summary>
	///	���̒��_�A�h���X���擾
	/// </summary>
	/// <returns>�A�h���X</returns>
	CVertex* GetNext();

	/// <summary>
	/// ���O�̃|�C���^���擾
	/// </summary>
	/// <returns>���O�̃|�C���^</returns>
	CVertex* GetPre();

	/// <summary>
	/// X���W��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	void SetX(float x);

	/// <summary>
	/// Y���W��ݒ�
	/// </summary>
	/// <param name="x">Y���W</param>
	void SetY(float y);

	/// <summary>
	/// Z���W��ݒ�
	/// </summary>
	/// <param name="x">Z���W</param>
	void SetZ(float z);

	/// <summary>
	/// ���̒��_�A�h���X��ݒ�
	/// </summary>
	/// <param name="x">���̒��_�A�h���X</param>
	void SetNext(CVertex* nextPointer);

	/// <summary>
	/// ���O�̃|�C���^��ݒ�
	/// </summary>
	/// <param name="x">���O�̃|�C���^</param>
	void SetPre(CVertex* prePointer);

	/// <summary>
	/// Vertex�̍��W��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetVertex(float x, float y);
#pragma endregion


};

