#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl(){
	shape_head = NULL;
	shape_tail = NULL;
}

CAdminControl::~CAdminControl()
{
}

void CAdminControl::Draw()
{
	// �_�̕`��
	DrawVertex();
	// ���̕`��
	DrawLine();
}

void CAdminControl::DrawVertex() {

	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);

	// ���_���X�g�𑖍����Ē��_��`��
	for (CShape* current_shape = shape_head; current_shape != NULL; current_shape = current_shape->GetNext()) {
		for (CVertex* current = current_shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			glVertex3f(current->GetX(), current->GetY(), current->GetZ());
		}
	}
	
	glEnd();
}

void CAdminControl::DrawLine() {
	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	
	for (CShape* current_shape = shape_head; current_shape != NULL; current_shape = current_shape->GetNext()) {
		// ���_���X�g�𑖍����Đ���`��
		for (CVertex* current = current_shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (current->GetNext() != NULL) {
				glVertex3f(current->GetX(), current->GetY(), current->GetZ());
				glVertex3f(current->GetNext()->GetX(), current->GetNext()->GetY(), current->GetNext()->GetZ());
			}
		}
	}


	glEnd();
}

void CAdminControl::SetVertex(float mouse_x, float mouse_y) {
	CMath math;

	// �}�E�X���W���g�p���ĐV�������_���쐬
	CVertex* newVertex = new CVertex();
	newVertex->SetVertex(mouse_x, mouse_y);

	// �}�`���Ǘ�����I�u�W�F�N�g�����݂��Ȃ��ꍇ�͐V�K�쐬
	if (shape_head == NULL) {
		shape_head = new CShape();
		shape_tail = shape_head; // �ŏ��̌`��̓w�b�h�ƃe�[��������
	}
	
	// ���_����3��菬�����̂ł���Β��_�ǉ�
	if (shape_tail->GetVertexCount() < 3) {
		shape_tail->SetVertexByPointer(newVertex); // �V�������_��ǉ�
		return;
	}
	
	shape_tail->SetVertexByPointer(newVertex); // �V�������_��ǉ�

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < 0.05f )) {

		// ����}�`�̏���
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // �����}�`�ɂ���
		
		// �}�`���X�g�ɐV�����}�`��������
		CShape* newShape = new CShape();
		shape_tail->SetNext(newShape); // �V�����}�`�����ɐݒ�
		shape_tail = newShape; // �e�[����V�����}�`�ɍX�V
	}
}
