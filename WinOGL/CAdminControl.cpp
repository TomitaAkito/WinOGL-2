#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl(){
	shape_head = NULL;
	shape_tail = NULL;
	CLOSE_DISTANCE = 0.05f;
	POINTSIZE = 10.0f;
	LINEWIDTH = 4.0f;
	AxisFlag = false;
	mouseVertex = new CVertex();
}

CAdminControl::~CAdminControl()
{
}

void CAdminControl::Draw()
{
	// �\����
	DrawPredictLine();

	// �_�̕`��
	DrawVertex();
	// ���̕`��
	DrawLine();

	// ���W���̕\��
	if (AxisFlag) DrawAxis();
}

void CAdminControl::DrawVertex() {

	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);

	// ���_���X�g�𑖍����Ē��_��`��
	for (CShape* current_shape = shape_head; current_shape != NULL; current_shape = current_shape->GetNext()) {
		for (CVertex* current = current_shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			//glVertex3f(current->GetX(), current->GetY(), current->GetZ());
			glVertex2f(current->GetX(), current->GetY());
		}
	}
	
	glEnd();
}

void CAdminControl::DrawLine() {
	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(LINEWIDTH);
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

void CAdminControl::DrawSizeChangeUP() {
	if (LINEWIDTH <= 10.0) {
		POINTSIZE += 0.7;
		LINEWIDTH += 0.4;
	}
}

void CAdminControl::DrawSizeChangeDOWN() {
	if (LINEWIDTH >= 1.0) {
		POINTSIZE -= 0.7;
		LINEWIDTH -= 0.4;
	}
}

void CAdminControl::DrawAxis() {
	glBegin(GL_LINES);
	// x��
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y��
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z��
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}

void CAdminControl::DrawPredictLine() {
	bool NGFlag = false;

	// �}�`�����Ă���ꍇ�͏I��
	if (shape_tail == NULL || shape_tail->GetIsClosedFlag() || shape_tail->GetVertexTail() == NULL)return;
	if (mouseVertex == NULL) return;

	// �j�����\�ɂ���
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);	//�j���̃p�^�[���̎w��i0xF0F0�̕���������j
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINE_STRIP);

	// ������
	if (isShapeCross(mouseVertex)) NGFlag = true;
	// ����
	if (isConnotation(mouseVertex)) NGFlag = true;
	// �}�`���̏���
	if (!shape_tail->isDrawPredict(mouseVertex)) NGFlag = true;

	if(NGFlag) glColor3f(1.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);

	glVertex3f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY(), shape_tail->GetVertexTail()->GetZ());
	glVertex3f(mouseVertex->GetX(), mouseVertex->GetY(), mouseVertex->GetZ());

	glEnd();
	glDisable(GL_LINE_STIPPLE);
}


void CAdminControl::SetVertex(float mouse_x, float mouse_y) {
	CMath math;

	// �}�E�X���W���g�p���ĐV�������_���쐬
	CVertex* newVertex = new CVertex(mouse_x, mouse_y);

	// �}�`���Ǘ�����I�u�W�F�N�g�����݂��Ȃ��ꍇ�͐V�K�쐬
	if (shape_head == NULL) {
		shape_head = new CShape();
		shape_tail = shape_head; // �ŏ��̌`��̓w�b�h�ƃe�[��������
	}

	// ����������ꍇ�͏I��
	if (isShapeCross(newVertex)) return;
	
	// �����ꍇ�͏I��
	if (isConnotation(newVertex)) return;

	// �V�������_��ǉ�
	shape_tail->SetVertexByPointer(newVertex);

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

void CAdminControl::SetMouseVertex(float mouse_x, float mouse_y) {
	mouseVertex->SetVertex(mouse_x, mouse_y);
}

bool CAdminControl::isShapeCross(CVertex* newVertex) {

	// 1�ڂ͋���
	if (shape_tail->GetVertexCount() < 1) return false;
	
	for (CShape* currentShape = shape_head; currentShape != shape_tail; currentShape = currentShape->GetNext()) {
		
		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			if (currentShape->isSelfCrossedBy2Lines(shape_tail->GetVertexTail(), newVertex, current, current->GetNext())) return true;
		}

	}

	return false;
}

bool CAdminControl::isConnotation(CVertex* newVertex) {
	// ���_������Ă��邩
	if(isConnotationVertex(newVertex)) return true;

	// �}�`������Ă��邩
	if (isConnotationShape(newVertex)) return true;

	return false;
}

bool CAdminControl::isConnotationVertex(CVertex* newVertex) {
	CMath math;
	float sumAngle = 0;
	
	for (CShape* currentShape = shape_head; currentShape != shape_tail; currentShape = currentShape->GetNext()) {

		/*for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			a->SetByVertex(newVertex, current);
			b->SetByVertex(newVertex, current->GetNext());

			sumAngle += math.calcAngle(a, b);
		}*/

		sumAngle = math.calcAngleByShape(currentShape, newVertex);
	}


	if (3.10 * 2 < math.absFloat(sumAngle)) return true;
	return false;
}

bool CAdminControl::isConnotationShape(CVertex* newVertex) {
	
	CMath math;
	float sumAngle = 0;
	float tanAnglel;

	// �����}�`�������̂ł���Ε���
	if ((shape_tail->GetVertexCount() >= 3) && (math.calcDistance(shape_tail->GetVertexHead(), newVertex) < CLOSE_DISTANCE)) {
		
		shape_tail->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // �����}�`�ɂ���

		for (CShape* currentShape = shape_head; currentShape->GetNext() != NULL; currentShape = currentShape->GetNext()) {
			for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
				if (math.calcAngleByShape(shape_tail, current) > 3.10 * 2) {
					shape_tail->freeVertexTail();
					return true;
				}

			}
		}
		shape_tail->freeVertexTail();
	}
	return false;
}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < CLOSE_DISTANCE )) {

		// ����}�`�̏���
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // �����}�`�ɂ���
		
		// �}�`���X�g�ɐV�����}�`��������
		CShape* newShape = new CShape();
		shape_tail->SetNext(newShape); // �V�����}�`�����ɐݒ�
		shape_tail = newShape; // �e�[����V�����}�`�ɍX�V
	}
}
