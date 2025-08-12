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
	EditFlag = false;
	LButtonDownFlag = false;
	MoveMouseVertex = new CVertex();
	selectVertexPointer = new CVertex();
	selectLinePointer = new CVertex();
	selectShapePointer = new CShape();
	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;
}

CAdminControl::~CAdminControl(){
	delete MoveMouseVertex, selectVertexPointer, selectLinePointer;
	delete selectShapePointer;
}

void CAdminControl::Draw()
{
	// �\����
	if(!EditFlag) DrawPredictLine();

	// �_�̕`��
	DrawVertex();

	// ���̕`��
	DrawLine();

	// ���W���̕\��
	if (AxisFlag) DrawAxis();

	// �ҏW���[�h�n�̕`��
	if (EditFlag) DrawEdit();
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
	if (MoveMouseVertex == NULL) return;

	// �j�����\�ɂ���
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);	//�j���̃p�^�[���̎w��i0xF0F0�̕���������j
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINE_STRIP);

	// ������
	if (isShapeCross(MoveMouseVertex)) NGFlag = true;
	// ����
	if (isConnotation(MoveMouseVertex)) NGFlag = true;
	// �}�`���̏���
	if (!shape_tail->isDrawPredict(MoveMouseVertex)) NGFlag = true;

	if(NGFlag) glColor3f(1.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);

	glVertex3f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY(), shape_tail->GetVertexTail()->GetZ());
	glVertex3f(MoveMouseVertex->GetX(), MoveMouseVertex->GetY(), MoveMouseVertex->GetZ());

	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void CAdminControl::DrawEdit() {
	if (selectVertexFlag) DrawSelectVertex(selectVertexPointer);
	if (selectLineFlag) DrawSelectLine(selectLinePointer, selectLinePointer->GetNext());
	if (selectShapeFlag) DrawSelectShape(selectShapePointer);
}

void CAdminControl::DrawSelectVertex(CVertex* vertex) {
	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);
	glVertex3f(vertex->GetX(), vertex->GetY(), vertex->GetZ());

	glEnd();
}

void CAdminControl::DrawSelectLine(CVertex* lineStart, CVertex* lineEnd) {
	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);
	glVertex3f(lineStart->GetX(), lineStart->GetY(), lineStart->GetZ());
	glVertex3f(lineEnd->GetX(), lineEnd->GetY(), lineEnd->GetZ());


	glEnd();
}

void CAdminControl::DrawSelectShape(CShape* shape) {
	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);

	// ���_���X�g�𑖍����Ē��_��`��
	for (CVertex* current = shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		//glVertex3f(current->GetX(), current->GetY(), current->GetZ());
		glVertex2f(current->GetX(), current->GetY());
	}
	glEnd();


	// �F�E�T�C�Y�̐ݒ�
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);

	// ���_���X�g�𑖍����Đ���`��
	for (CVertex* current = shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		if (current->GetNext() != NULL) {
			glVertex3f(current->GetX(), current->GetY(), current->GetZ());
			glVertex3f(current->GetNext()->GetX(), current->GetNext()->GetY(), current->GetNext()->GetZ());
		}
	}
	glEnd();
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

	// ���������邩�C�����ꍇ�͏I��
	if (isShapeCross(newVertex)|| isConnotation(newVertex)) {
		delete newVertex;
		return;
	}

	// �V�������_��ǉ�
	shape_tail->SetVertexByPointer(newVertex);

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

void CAdminControl::SetMouseVertex(float mouse_x, float mouse_y) {
	MoveMouseVertex->SetVertex(mouse_x, mouse_y);
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

bool CAdminControl::isConnotationMoveVertex(CVertex* vertex) {
	
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL) continue;
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			for (CShape* surchShape = shape_head; surchShape != NULL; surchShape = surchShape->GetNext()) {
				if (surchShape->GetVertexHead() == NULL) continue;
				if (surchShape == currentShape) continue;
				CMath math;
				if (math.calcAngleByShape(surchShape, current) > 6) return true;
			}
		}
	}
	return false;
}
void CAdminControl::Edit(float mouse_x, float mouse_y) {
	// �}�E�X�����W�Ƃ��Ďw�肷��
	CVertex* LMouseVertex = new CVertex(mouse_x,mouse_y);
	selectVertexPointer = NULL;
	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;

	// �T��
	bool VertexFlag = selectVertex(LMouseVertex);
	bool LineFlag = selectLine(LMouseVertex);	
	bool ShapeFlag = selectShape(LMouseVertex);

	// �D�揇�ʂ�݂���
	if (VertexFlag) selectVertexFlag = true;
	else if (LineFlag) selectLineFlag = true;
	else if (ShapeFlag) selectShapeFlag = true;	
	delete LMouseVertex;
}

bool CAdminControl::selectVertex(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (math.calcDistance(current, LMouseVertex) < CLOSE_DISTANCE) {
				selectVertexPointer = current;
				return true;
			}
		}
	}

	return false;
}

bool CAdminControl::selectLine(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL) break;

		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			if (math.calcPointLineDistance(current, current->GetNext(), LMouseVertex) < CLOSE_DISTANCE) {
				CVector* a = new CVector(current, LMouseVertex);
				CVector* b = new CVector(current, current->GetNext());
				float theta1 = math.calcAngle(a,b);

				a->SetByVertex(current->GetNext(), LMouseVertex);
				b->SetByVertex(current->GetNext(), current);
				float theta2 = math.calcAngle(a, b);
				delete a, b;
				
				if ((-3.15 / 2 < theta1 && theta1 < 3.15 / 2) && (-3.15 / 2 < theta2 && theta2 < 3.15 / 2)) {
					selectLinePointer = current;
					return true;

				}

			}
		}
	}

	return false;
}

bool CAdminControl::selectShape(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL)break;

		if (math.calcAngleByShape(currentShape, LMouseVertex) > 6) {
			selectShapePointer = currentShape;
			return true;
		}
	}
	return false;
}

void CAdminControl::moveByMouse() {
	if (selectVertexFlag)moveVertex(MoveMouseVertex);
}

void CAdminControl::moveVertex(CVertex* mouseVertex) {

	//== ���W���ꎞ�ۑ����A���_���ړ� ==
	// ���̍��W��ۑ�
	float originalX = selectVertexPointer->GetX();
	float originalY = selectVertexPointer->GetY();

	CShape* shape = serchShapeByVertex(selectVertexPointer); // �I�𒆂̒��_���܂܂��}�`���擾
	CMath math;

	// �I���������_���A�����}�`�̎n�_�^�I�_�Ɠ����ʒu�ɂ��邩����
	bool isClosedShapeEndpoint = false;
	if (shape->GetIsClosedFlag() && math.isXYZ(selectVertexPointer, shape->GetVertexHead())) isClosedShapeEndpoint = true;

	// �ŏ��ɒ��_���}�E�X���W�ֈړ�������
	selectVertexPointer->SetXY(mouseVertex->GetX(), mouseVertex->GetY());

	// ���������}�`�̒[�_�Ȃ�A�΂ɂȂ钸�_�iTail�j��������
	if (isClosedShapeEndpoint) shape->GetVertexTail()->SetXY(mouseVertex->GetX(), mouseVertex->GetY());

	//== ���Ȃ������`�F�b�N ==
	bool ERRFlag = false;

	// �O�̒��_���擾
	CVertex* preVertex = selectVertexPointer->GetPre();
	if (preVertex == NULL && isClosedShapeEndpoint) preVertex = shape->GetVertexTail()->GetPre();

	// ���̒��_���擾
	CVertex* nextVertex = selectVertexPointer->GetNext();
	if (nextVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) nextVertex = shape->GetVertexHead();

	
	// ��������
	if (nextVertex != NULL && shape->isMoveVertexSelfCross(selectVertexPointer, nextVertex, shape_head)) ERRFlag = true;
	if (!ERRFlag && preVertex != NULL && shape->isMoveVertexSelfCross(preVertex, selectVertexPointer, shape_head)) ERRFlag = true;

	// �����
	if (isConnotationMoveVertex(selectVertexPointer)) ERRFlag = true;
	

	//== ��肪����ꍇ�͌��̍��W�ɖ߂� ==
	if (ERRFlag) {
		selectVertexPointer->SetXY(originalX, originalY);
		if (isClosedShapeEndpoint) shape->GetVertexTail()->SetXY(originalX, originalY);
	}
		
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

CShape* CAdminControl::serchShapeByVertex(CVertex* vertex) {
	CMath math;
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (math.isXYZ(current, vertex)) return currentShape;
		}
	}
	return NULL;
}
