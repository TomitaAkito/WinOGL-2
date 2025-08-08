#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region �����o�ϐ�
public:
	CShape* shape_head;  // �`����Ǘ�����I�u�W�F�N�g
	CShape* shape_tail;  // �`��̖����|�C���^
private:

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
#pragma endregion

#pragma region Set�n/Get�n

	/// <summary>
	/// �}�E�X���W���g�p���Ē��_��ݒ�
	/// </summary>
	/// <param name="mouse_x">�}�E�X��X���W</param>
	/// <param name="mouse_y">�}�E�X��Y���W</param>
	void SetVertex(float mouse_x, float mouse_y);

#pragma endregion
};

