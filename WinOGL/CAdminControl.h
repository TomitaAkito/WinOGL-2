#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region �����o�ϐ�
public:
	bool AxisFlag; // ���W����`�悷�邩
	bool EditFlag; // �ҏW���[�h�ɂ��邩
	bool LButtonDownFlag; // ���N���b�N����������Ă��邩
private:
	CShape* shape_head;  // �`����Ǘ�����I�u�W�F�N�g
	CShape* shape_tail;  // �`��̖����|�C���^
	float CLOSE_DISTANCE; // �ǂꂭ�炢�ŕ��邩
	float POINTSIZE; // ���_�̃T�C�Y
	float LINEWIDTH; // ���̃T�C�Y
	CVertex* MoveMouseVertex; // �}�E�X���W
	CVertex* selectVertexPointer; // �I�����ꂽ���_
	CVertex* selectLinePointer; // �I�����ꂽ�Ő��̎n�_
	CShape* selectShapePointer; // �I�����ꂽ�}�`
	bool selectVertexFlag; // ���_��I�����Ă��邩
	bool selectLineFlag; // �Ő���I�����Ă��邩
	bool selectShapeFlag; // �}�`��I�����Ă��邩
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

	/// <summary>
	/// �I�����ʂ�`�悷��
	/// </summary>
	void DrawEdit();

	/// <summary>
	/// �����̒��_�̐F��ύX���ĕ`��
	/// </summary>
	/// <param name="vertex">���_</param>
	void DrawSelectVertex(CVertex* vertex);

	/// <summary>
	/// �����̗Ő��̐F��ύX���ĕ`��
	/// </summary>
	/// <param name="lineStart">�Ő��̎n�_</param>
	/// <param name="lineEnd">�Ő��̏I�_</param>
	void DrawSelectLine(CVertex* lineStart,CVertex* lineEnd);

	/// <summary>
	/// �����̐}�`�̐F��ύX���ĕ`��
	/// </summary>
	/// <param name="shape">�}�`</param>
	void DrawSelectShape(CShape* shape);
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

	/// <summary>
	/// ���_�𓮂������ۂɓ���邩����
	/// </summary>
	/// <param name="vertex">�ړ����Ă��钸�_</param>
	/// <returns>�����ꍇ��true�A���Ȃ��ꍇ��false</returns>
	bool isConnotationMoveVertex(CVertex* vertex);

	/// <summary>
	/// �폜�����ۂɓ���邩����
	/// </summary>
	/// <param name="vertex">�������_</param>
	/// <param name="shape">�폜�Ώۂ̐}�`</param>
	/// <returns>�����ꍇ��true�A���Ȃ��ꍇ��false</returns>
	bool isConnotationFreeVertex(CVertex* vertex, CShape* shape);
#pragma endregion

#pragma region �ҏW
	
	/// <summary>
	/// �ҏW���[�h���i��֐�
	/// </summary>
	/// <param name="mouse_x">�}�E�X��X���W</param>
	/// <param name="mouse_y">�}�E�X��Y���W</param>
	void Edit(float mouse_x, float mouse_y);

	/// <summary>
	/// �_�̑I��
	/// </summary>
	/// <param name="LMouseVertex">�}�E�X���W</param>
	/// <returns>�I���ł����ꍇ��true�A�ł��Ȃ������ꍇ��false</returns>
	bool selectVertex(CVertex* LMouseVertex);

	/// <summary>
	/// ���̑I��
	/// </summary>
	/// <param name="LMouseVertex">�}�E�X���W</param>
	/// <returns>�I���ł����ꍇ��true�A�ł��Ȃ������ꍇ��false</returns>
	bool selectLine(CVertex* LMouseVertex);

	/// <summary>
	/// �}�`�̑I��
	/// </summary>
	/// <param name="LMouseVertex">�}�E�X���W</param>
	/// <returns>�I���ł����ꍇ��true�A�ł��Ȃ������ꍇ��false</returns>
	bool selectShape(CVertex* LMouseVertex);

	/// <summary>
	/// �ړ��n���i��֐�
	/// </summary>
	void moveByMouse();

	/// <summary>
	/// ���_���ړ�
	/// </summary>
	/// <param name="mouseVertex">�}�E�X���W</param>
	void moveVertex(CVertex* mouseVertex);

	/// <summary>
	/// �_�̑}��
	/// </summary>
	/// <param name="mouseVertex">�}�E�X���W</param>
	void insertVertex(CVertex* mouseVertex);

	/// <summary>
	/// �I�����ꂽ���_���폜
	/// </summary>
	void deleteVertex();
#pragma endregion

#pragma region ���̑�����

	/// <summary>
	/// �}�`����邩�̔�����s���A����K�v������ꍇ�͐}�`�����
	/// </summary>
	void closeShape();

	/// <summary>
	/// ���_����}�`��T�����ĕԂ�
	/// </summary>
	/// <param name="vertex">���_</param>
	/// <returns>�}�`</returns>
	CShape* serchShapeByVertex(CVertex* vertex);

	/// <summary>
	/// �}�`�̍폜
	/// </summary>
	void freeShape(CShape* shape);

	/// <summary>
	/// ���ׂĂ̐}�`���폜
	/// </summary>
	void freeALLShape();
#pragma endregion
};

