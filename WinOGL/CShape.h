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
	/// �ʏ�̒��_�ǉ����@
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	void NormalAddVertex(CVertex* newVertex);

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
	/// ���_����ݒ�
	/// </summary>
	/// <param name="num">���_��</param>
	void SetVertexCount(int num);

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

#pragma region ����n

	/// <summary>
	/// �`��ł��邩�𔻒�
	/// </summary>
	/// <param name="MoveMouseVertex">�}�E�X���W</param>
	/// <returns>�ݒu�ł���ꍇ��true�A�ł��Ȃ��ꍇ��false</returns>
	bool isDrawPredict(CVertex* MoveMouseVertex);

	/// <summary>
	/// �������𔻒�
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	/// <returns>���������Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false</returns>
	bool isSelfCrossed(CVertex* newVertex);

	/// <summary>
	/// �����v�̂悤�Ɏn�_�ƏI�_��z�u�����ꍇ�Ɏ��������Ȃ�������
	/// </summary>
	/// <returns>���������Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false</returns>
	bool isSelfCrossedByHourGlassType();

	/// <summary>
	/// ��̐������������Ă��邩����
	/// </summary>
	/// <param name="As">����A�̊J�n�n�_</param>
	/// <param name="Ae">����A�̏I���n�_</param>
	/// <param name="Bs">����B�̊J�n�n�_</param>
	/// <param name="Be">����B�̏I���n�_</param>
	/// <returns></returns>
	bool isSelfCrossedBy2Lines(CVertex* As, CVertex* Ae, CVertex* Bs, CVertex* Be);

	/// <summary>
	/// �}�`���������E���������Ă��Ȃ�������
	/// </summary>
	/// <param name="selectVertex">�I�𒆂̒��_</param>
	/// <param name="nextVertex">�I�𒆂̒��_�̎��̒��_</param>
	/// <param name="shape_head">�}�`���X�g�̓�</param>
	/// <returns>�������Ă�����true�A���Ă��Ȃ����false</returns>
	bool isMoveVertexSelfCross(CVertex* selectVertex, CVertex* nextVertex, CShape* shape_head);


#pragma endregion

#pragma region ���̑��̃��\�b�h

	/// <summary>
	/// �}�`�����
	/// </summary>
	void freeShape();

	/// <summary>
	/// ���W����v���钸�_���폜
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	void freeVertex(float x,float y);

	/// <summary>
	/// vertex_tail���폜
	/// </summary>
	void freeVertexTail();

	/// <summary>
	/// �O�̒��_�̎��ɒ��_��}��
	/// </summary>
	/// <param name="preVertex">�O�̒��_</param>
	/// <param name="newVertex">�V�����}�����钸�_</param>
	void insertVertex(CVertex* preVertex,CVertex* newVertex);
#pragma endregion
};

