#include "pch.h"
#include "CVertex.h"
#pragma once
class CShape{
#pragma region �����o�ϐ�
private:
	CVertex* vertex_head;  // ���_�̐擪�|�C���^
	CVertex* vertex_tail;  // ���_�̖����|�C���^
	CShape* next;  // ���̌`��ւ̃|�C���^
	bool isClosedFlag; // �����}�`���ǂ���
	int vertexCount; // ���_�̐�
#pragma endregion

#pragma region �R���X�g���N�^�E�f�X�g���N�^
	public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CShape();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CShape();

#pragma endregion

#pragma region Set�n/Get�n
	/// <summary>
	/// ���_�̐擪�|�C���^���擾
	/// </summary>
	/// <returns>���_�̐擪�|�C���^</returns>
	CVertex* GetVertexHead();

	/// <summary>
	/// ���_�̖����|�C���^���擾
	/// </summary>
	/// <returns>���_�̖����|�C���^</returns>
	CVertex* GetVertexTail();

	/// <summary>
	/// Vertex�̍��W��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetVertex(float x,float y);

	/// <summary>
	/// Vertex�̍��W��ݒ�
	/// </summary>
	/// <param name="newVertex">�V����vertex</param>
	void SetVertexByPointer(CVertex* newVertex);

	/// <summary>
	/// ���̃|�C���^���擾
	/// </summary>
	/// <returns>���̃|�C���^</returns>
	CShape* GetNext();

	/// <summary>
	/// ���̐}�`��ݒ�
	/// </summary>
	/// <param name="nextShape">�ݒ肷�鎟�� CShape �I�u�W�F�N�g�ւ̃|�C���^</param>
	void SetNext(CShape* nextShape);

	/// <summary>
	/// ���_�����擾
	/// </summary>
	/// <returns>���_��</returns>
	int GetVertexCount();

	/// <summary>
	/// �I�u�W�F�N�g�����Ă��邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="isClosedFlag">�I�u�W�F�N�g�����Ă���ꍇ�� true�A�J���Ă���ꍇ�� false ���w��</param>
	void SetIsClosed(bool isClosedFlag);

	/// <summary>
	/// �I�u�W�F�N�g�����Ă��邩�ǂ������擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�����Ă���ꍇ�� true�A�J���Ă���ꍇ�� false</returns>
	bool GetIsClosedFlag();
#pragma endregion
};

