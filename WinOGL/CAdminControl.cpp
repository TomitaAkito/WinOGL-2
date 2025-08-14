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
	beforMoveMouseVertex = new CVertex();
	selectVertexPointer = new CVertex();
	selectLinePointer = new CVertex();
	selectShapePointer = new CShape();
	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;
	ShiftFlag = false;
	keyRFlag = false;
	selectNum = 0;
	LButtonDownVeretex = new CVertex();
	resizeShapeCopy = new CShape();
}

CAdminControl::~CAdminControl(){
	freeALLShape();
	delete MoveMouseVertex, beforMoveMouseVertex, resizeShapeCopy;
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
	beforMoveMouseVertex->SetVertex(MoveMouseVertex->GetX(), MoveMouseVertex->GetY());
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
bool CAdminControl::isConnotationFreeVertex(CVertex* vertex, CShape* shape) {

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
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
	
	if (ShiftFlag || keyRFlag)return;
	
	// �}�E�X�����W�Ƃ��Ďw�肷��
	CVertex* LMouseVertex = new CVertex(mouse_x,mouse_y);

	// ���_�̑}���p�Ɍ����_��selectLine��ۑ�
	CVertex* tmpSelectLine = selectLinePointer;

	// �T��
	bool VertexFlag = selectVertex(LMouseVertex);
	bool LineFlag = selectLine(LMouseVertex);	
	bool ShapeFlag = selectShape(LMouseVertex);

	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;


	// �D�揇�ʂ�݂���
	if (VertexFlag) selectVertexFlag = true;
	else if (LineFlag) selectLineFlag = true;
	else if (ShapeFlag) {
		selectShapeFlag = true;
		resizeShapeCopy = copyShape(selectShapePointer);
	}

	// �_��}�����邩
	if (selectLineFlag && tmpSelectLine == selectLinePointer) {
		insertVertex(LMouseVertex);
		selectLineFlag = false;
		selectVertexFlag = true;
		selectVertexPointer = LMouseVertex;
		return;
	}

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
	else if (selectShapeFlag)moveShape(MoveMouseVertex);
}

void CAdminControl::moveVertex(CVertex* mouseVertex) {

	if (!selectVertexFlag)return;

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

void CAdminControl::moveShape(CVertex* mouseVertex) {

	if (!selectShapeFlag)return;

	// �ړ��ʎZ�o
	CMath math;
	float movement[2];
	math.calcMovementByVertex(beforMoveMouseVertex, mouseVertex, movement);

	// �ړ��ʂɊ�Â��ړ�
	selectShapePointer->moveByMovement(movement[0],movement[1]);
	
	// �}�`��1�����Ȃ��ꍇ�̓X�L�b�v
	if (shape_head->GetNext() == NULL) return;

	// ��肪���邩�`�F�b�N
	bool ERRFlag = false;
	for (CVertex* current = selectShapePointer->GetVertexHead(); current != selectShapePointer->GetVertexTail(); current = current->GetNext()) {
		// �������� || �����
		if ((current->GetPre() != NULL && selectShapePointer->isMoveVertexSelfCross(current->GetPre(), current, shape_head))
			||(isConnotationMoveVertex(current))){
			ERRFlag = true;
			break;
		}
	}

	// ��肪����ꍇ�͌��̍��W�ɖ߂�
	if (ERRFlag)
		selectShapePointer->moveByMovement((-1) * movement[0], (-1) * movement[1]);
}

void CAdminControl::insertVertex(CVertex* mouseVertex) {
	if (!selectLineFlag) return;
	CShape* shape = serchShapeByVertex(selectLinePointer);
	CVertex* nextVertex = selectLinePointer->GetNext();

	selectLinePointer->SetNext(mouseVertex);
	mouseVertex->SetPre(selectLinePointer);
	mouseVertex->SetNext(nextVertex);
	nextVertex->SetPre(mouseVertex);

	shape->SetVertexCount(shape->GetVertexCount() + 1);
	selectVertexPointer = mouseVertex;
}

//void CAdminControl::deleteVertex() {
	//// ��O����
	//if (!EditFlag || !selectVertexFlag)return;
	//CShape* shape = serchShapeByVertex(selectVertexPointer);
	//if (shape->GetIsClosedFlag() && shape->GetVertexCount() <= 4) return;
	//if (!shape->GetIsClosedFlag() && shape->GetVertexCount() <= 1) return;

	//// ��U�ۑ�
	//CVertex* vertexToDelete = selectVertexPointer;
	//CVertex* preVertex = selectVertexPointer->GetPre();
	//CVertex* backupVertex = new CVertex(vertexToDelete->GetX(), vertexToDelete->GetY());

	//// GoodBye
	//shape->freeVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());
	//
	//bool ERRFlag = false;
	//// �����
	//if (shape->GetIsClosedFlag() && isConnotationFreeVertex(backupVertex, shape)) ERRFlag = true;
	//
	//// ��������
	//if (!ERRFlag && preVertex != NULL) {
	//	CVertex* nextVertex = preVertex->GetNext();
	//	if (nextVertex != NULL) {
	//		if (shape->isMoveVertexSelfCross(preVertex, nextVertex, shape_head) ||
	//			(nextVertex->GetNext() != NULL && shape->isMoveVertexSelfCross(nextVertex, nextVertex->GetNext(), shape_head))) {
	//			ERRFlag = true;
	//		}
	//	}
	//}

	//// ��肪����΂��Ƃɖ߂�
	//if (ERRFlag) {
	//	// ��肪����΁A�o�b�N�A�b�v���璸�_�𕜌�
	//	shape->insertVertex(preVertex, backupVertex);
	//	selectVertexPointer = backupVertex;
	//	return;
	//}
	//else {
	//	delete backupVertex;
	//	return;
	//}

void CAdminControl::deleteVertex() {
	/* �w������̃\�[�X�R�[�h�����ς��܂����B����ł��B�����ł��B */

	// ��O����
	if (!selectVertexFlag) return;
	
	// ���_���܂܂��}�`�̒T��
	CShape* shape = serchShapeByVertex(selectVertexPointer);

	// �ی�(����������ꍇ��Vertex)
	CVertex* BFVertex = selectVertexPointer->GetPre();
	CVertex* vertex = new CVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());
	vertex->SetNext(selectVertexPointer->GetNext());


	// �}�`���O�p�`�Ȃ�
	if (shape->GetVertexCount() <= 4 && shape->GetIsClosedFlag()) return;

	// ���_���폜
	else {
		// ����pvertex�̐ݒ�
		if (BFVertex == NULL && shape->GetIsClosedFlag()) BFVertex = shape->GetVertexTail()->GetPre();

		// ��U�폜
		shape->freeVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());

		// ����pvertex�̐ݒ�
		CVertex* nowVertex = NULL;
		if (BFVertex != NULL) {
			nowVertex = BFVertex->GetNext();
			if (nowVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) nowVertex = shape->GetVertexHead();
		}

		CVertex* AFVertex = NULL;
		if (nowVertex != NULL) {
			AFVertex = nowVertex->GetNext();
			if (AFVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) AFVertex = shape->GetVertexHead();
		}

		bool ErrFlag = false;

		// �����
		if (shape->GetIsClosedFlag() && isConnotationFreeVertex(vertex, shape)) {
			ErrFlag = true;
		}

		// ��������
		bool flag = true;
		if (BFVertex == NULL || nowVertex == NULL) flag = false;
		if (flag && shape->isMoveVertexSelfCross(BFVertex, nowVertex, shape_head)) {
			ErrFlag = true;
		}
		flag = true;
		if (AFVertex == NULL || nowVertex == NULL) flag = false;
		if (flag && shape->isMoveVertexSelfCross(nowVertex, AFVertex, shape_head)) {
			ErrFlag = true;
		}

		if (ErrFlag) {
			// ���Ƃɖ߂�(vertex��}������)
			shape->insertVertex(BFVertex, vertex);
			selectVertexPointer = vertex;
			return;
		}
	}
	// �����`�󂪕ۂĂȂ�(vertex�̐���0)�ꍇ�͌`�������
	if (shape->GetVertexCount() == 0) freeShape(shape);
	return;
}

void CAdminControl::resizeShape() {
	if (!selectShapeFlag)return;

	// �ړ��ʎZ�o
	CMath math;
	float resizeRate[2];
	math.calcResizeRate(LButtonDownVeretex, MoveMouseVertex, resizeRate);
	CShape* cpShape = copyShape(selectShapePointer);

	// �ړ��ʂɊ�Â��ړ�
	selectShapePointer->resizeShape(resizeRate[0], resizeRate[0], resizeShapeCopy);

	// �}�`��1�����Ȃ��ꍇ�̓X�L�b�v
	if (shape_head->GetNext() == NULL) return;

	// ��肪���邩�`�F�b�N
	bool ERRFlag = false;
	for (CVertex* current = selectShapePointer->GetVertexHead(); current != selectShapePointer->GetVertexTail(); current = current->GetNext()) {
		// �������� || �����
		if ((current->GetPre() != NULL && selectShapePointer->isMoveVertexSelfCross(current->GetPre(), current, shape_head))
			|| (isConnotationMoveVertex(current))) {
			ERRFlag = true;
			break;
		}
	}

	if (0.01 >= math.calcShapeArea(selectShapePointer))
		ERRFlag = true;
		
	// ��肪����ꍇ�͌��̍��W�ɖ߂�
	if (ERRFlag)
		copyShapeByShape(cpShape, selectShapePointer);

	delete cpShape;
}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < CLOSE_DISTANCE )) {

		// ����}�`�̏���
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // �����}�`�ɂ���
		CVertex* COG = math.calcCOGByShape(shape_tail);
		shape_tail->COGVertex->SetXY(COG->GetX(), COG->GetY());
		delete COG;
		
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

void CAdminControl::freeShape(CShape* shape) {
	CShape* beforShape = NULL;
	// �O�̐}�`�𒲂ׂ�
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape == shape) break;
		beforShape = currentShape;
	}

	if (shape_head == shape) {
		if (shape_head->GetNext() != NULL)shape_head = shape_head->GetNext();
		else {
			shape_head = NULL;
			shape_tail = NULL;
		}
	}
	if (shape_tail == shape) {
		// tail�̑O������=> shape_head�ƈꏏ�̏ꍇ
		if (shape_head == shape_tail) {
			shape_head = NULL;
			shape_tail = NULL;
		}
		else shape_tail = beforShape;
	}

	if (beforShape != NULL)beforShape->SetNext(shape->GetNext());
	shape->freeShape();
	delete shape;
}

void CAdminControl::freeALLShape() {
	CShape* nowShape = shape_head;

	while (nowShape != NULL) {
		if (nowShape->GetVertexHead() == NULL)break;
		// �}�`�����ׂĔj�󂷂�
		freeShape(nowShape);

		nowShape = shape_head;
	}
}

CShape* CAdminControl::copyShape(CShape* baseShape) {

	CShape* newShape = new CShape();

	for (CVertex* current = baseShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		newShape->SetVertexToCopy(current);
	}
	if(baseShape->GetIsClosedFlag())newShape->SetIsClosed(true);
	
	return newShape;
}

void CAdminControl::copyShapeByShape(CShape* baseShape, CShape* copyShape) {
	if (baseShape->GetVertexCount() != copyShape->GetVertexCount())return;

	CVertex* cpCurrent = copyShape->GetVertexHead();
	for (CVertex* current = baseShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		cpCurrent->SetXY(current->GetX(), current->GetY());
		cpCurrent = cpCurrent->GetNext();
	}
}
