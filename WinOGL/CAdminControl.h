#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region �����o�ϐ�
public:
	bool AxisFlag; // ���W����`�悷�邩
private:
	CShape* shape_head;  // �`����Ǘ�����I�u�W�F�N�g
	CShape* shape_tail;  // �`��̖����|�C���^
	float CLOSE_DISTANCE; // �ǂꂭ�炢�ŕ��邩
	float POINTSIZE; // ���_�̃T�C�Y
	float LINEWIDTH; // ���̃T�C�Y
	CVertex* mouseVertex; // �}�E�X���W
#pragma endregion

public:
#pragma region �R���X�g���N�^�E�f�X�g���N�^
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CAdminControl();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CAdminControl();

#pragma endregion

#pragma region �`��n
	/// <summary>
	/// �`�揈�������s
	/// </summary>
	void Draw();

	/// <summary>
	/// ���_��`��
	/// </summary>
	void DrawVertex();

	/// <summary>
	/// ����`��
	/// </summary>
	void DrawLine();

	/// <summary>
	/// �_�Ɛ��̃T�C�Y�ύX
	/// </summary>
	void DrawSizeChangeUP();

	/// <summary>
	/// �_�Ɛ��̃T�C�Y�ύX
	/// </summary>
	void DrawSizeChangeDOWN();

	/// <summary>
	/// ���W���̕`��
	/// </summary>
	void DrawAxis();

	/// <summary>
	/// �\�����̕`��
	/// </summary>
	void DrawPredictLine();
#pragma endregion

#pragma region Set�n/Get�n

	/// <summary>
	/// �}�E�X���W���g�p���Ē��_��ݒ�
	/// </summary>
	/// <param name="mouse_x">�}�E�X��X���W</param>
	/// <param name="mouse_y">�}�E�X��Y���W</param>
	void SetVertex(float mouse_x, float mouse_y);

	/// <summary>
	/// �}�E�X���W��ݒ�
	/// </summary>
	/// <param name="mouse_x">�}�E�X��X���W</param>
	/// <param name="mouse_y">�}�E�X��Y���W</param>
	void SetMouseVertex(float mouse_x, float mouse_y);

#pragma endregion

#pragma region ����

	/// <summary>
	/// �}�`���m������(������)���Ă��邩����
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	/// <returns>���������Ă���ꍇ��true�A���Ă��Ȃ��ꍇ��false</returns>
	bool isShapeCross(CVertex* newVertex);

	/// <summary>
	/// ���_�E�}�`������Ă��邩����
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	/// <returns>�����ꍇ��true�A���Ȃ��ꍇ��false</returns>
	bool isConnotation(CVertex* newVertex);

	/// <summary>
	/// ���_������Ă��邩����
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	/// <returns>�����ꍇ��true�A���Ȃ��ꍇ��false</returns>
	bool isConnotationVertex(CVertex* newVertex);

	/// <summary>
	/// �}�`������Ă��邩����
	/// </summary>
	/// <param name="newVertex">�V�������_</param>
	/// <returns>�����ꍇ��true�A���Ȃ��ꍇ��false</returns>
	bool isConnotationShape(CVertex* newVertex);
#pragma endregion

#pragma region ���̑�����

	/// <summary>
	/// �}�`����邩�̔�����s���A����K�v������ꍇ�͐}�`�����
	/// </summary>
	void closeShape();
#pragma endregion
};

