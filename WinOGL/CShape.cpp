#include "pch.h"
#include "CShape.h"
#include "CVector.h"
#include "CMath.h"

CShape::CShape() {
	// ������
	vertex_head = NULL;
	vertex_tail = NULL;
	next = NULL; // ���̌`��ւ̃|�C���^��������
	isClosedFlag = false; // ������Ԃł͕��Ă��Ȃ�
	vertexCount = 0; // ���_�̐���������
}

CShape::~CShape() {
}

CVertex* CShape::GetVertexHead() {
	return vertex_head;
}

CVertex* CShape::GetVertexTail() {
	return vertex_tail;
}

void CShape::SetVertex(float x, float y) {
	CVertex* newVertex = new CVertex();
	newVertex->SetVertex(x, y);
	SetVertexByPointer(newVertex);
}

void CShape::SetVertexByPointer(CVertex* newVertex) {
	
	// ����vertex_head��NULL�Ȃ�΁A�ŏ��̒��_�Ƃ��Đݒ�
	if (vertex_head == NULL) {
		vertex_head = newVertex;
		vertex_tail = newVertex; // �ŏ��̒��_�̓w�b�h�ƃe�[��������
		vertexCount++; // ���_�̐��𑝂₷
		return;
	}

	// vertex_head�ƈꏏ�Ȃ炱�̂܂܏��������s
	CMath math;
	if (math.isXYZ(newVertex, this->GetVertexHead())) {
		NormalAddVertex(newVertex);
		return;
	}
	
	// ���_����3�ȉ��̏ꍇ�͐ݒ�
	if (vertexCount < 3) {
		NormalAddVertex(newVertex);
		return;
	}
	
	// ���������Ȃ����OK
	if (!isSelfCrossed(newVertex)) {
		NormalAddVertex(newVertex);
	}	
}

void CShape::NormalAddVertex(CVertex* newVertex) {
	// �����̒��_���X�g�ɒǉ�
	vertex_tail->SetNext(newVertex);
	newVertex->SetPre(vertex_tail);
	vertex_tail = newVertex; // �V�������_���e�[���Ƃ��Đݒ�
	vertexCount++; // ���_�̐��𑝂₷
}

CShape* CShape::GetNext() {
	return next;
}


void CShape::SetNext(CShape* nextShape) {
	this->next = nextShape;
}

void CShape::SetVertexCount(int num) {
	this->vertexCount = num;
}

int CShape::GetVertexCount() {
	return vertexCount;
}

void CShape::SetIsClosed(bool isClosedFlag) {
	this->isClosedFlag = isClosedFlag;
}

bool CShape::GetIsClosedFlag() {
	return isClosedFlag;
}

bool CShape::isDrawPredict(CVertex* MoveMouseVertex) {
	CMath math;
	if (math.isXYZ(MoveMouseVertex, this->GetVertexHead())) return true;

	// ���_����3�ȉ��̏ꍇ�͐ݒ�
	if (vertexCount < 3) return true;

	// ���������Ȃ����OK
	if (!isSelfCrossed(MoveMouseVertex)) return true;

	return false;
}

bool CShape::isSelfCrossed(CVertex* newVertex) {

	for (CVertex* current = this->GetVertexHead(); current->GetNext() != this->GetVertexTail(); current = current->GetNext()) {
		if(isSelfCrossedBy2Lines(this->GetVertexTail(),newVertex, current, current->GetNext())) return true;
	}

	return false;
}

bool CShape::isSelfCrossedByHourGlassType() {
	// ��O����
	if (this->GetVertexCount() <= 3) return false;

	for (CVertex* current = this->GetVertexHead()->GetNext(); current->GetNext() != this->GetVertexTail(); current = current->GetNext()) {
		if (isSelfCrossedBy2Lines(this->GetVertexTail(), this->GetVertexHead(), current, current->GetNext())) return true;
	}
	return false;
}

bool CShape::isSelfCrossedBy2Lines(CVertex* As, CVertex* Ae, CVertex* Bs, CVertex* Be) {

	// �x�N�g���ɕϊ�
	CVector* a = new CVector(As, Ae);
	CVector* b = new CVector(Bs, Be);
	CVector* a1 = new CVector(As, Bs);
	CVector* b1 = new CVector(Bs, As);
	CVector* a2 = new CVector(As, Be);
	CVector* b2 = new CVector(Bs, Ae);
	CMath math;

	// �O�ς��v�Z
	float ca1 = math.calcCrossProduct(a, a1);
	float ca2 = math.calcCrossProduct(a, a2);
	float cb1 = math.calcCrossProduct(b, b1);
	float cb2 = math.calcCrossProduct(b, b2);
	// ���������
	delete a, b, a1, b1, a2, b2;

	if ((ca1 * ca2 <= 0) && (cb1 * cb2 <= 0)) return true;
	return false;
}

bool CShape::isMoveVertexSelfCross(CVertex* selectVertex, CVertex* nextVertex, CShape* shape_head) {
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		// ��O����
		if (currentShape->GetVertexHead() == NULL) continue;
		if (currentShape->GetVertexCount() < 2) continue;

		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {

			// --- ��O���� ---
			if (selectVertex == current || nextVertex == current) continue;
			CVertex* checkVertex = selectVertex;
			if (checkVertex == vertex_head && this->GetIsClosedFlag()) checkVertex = vertex_tail;
			if (checkVertex == current->GetNext()) continue;

			// --- �������� ---
			if (isSelfCrossedBy2Lines(selectVertex, nextVertex, current, current->GetNext())) {
				return true;
			}
		}
	}
	return false;
}

void CShape::freeShape() {
	CVertex* current = vertex_head;
	while (current != NULL) {
		CVertex* nextVertex = current->GetNext();
		delete current; // ���݂̒��_���폜
		current = nextVertex; // ���̒��_�Ɉړ�
	}
	vertex_head = NULL; // ���_���X�g����ɂ���
	vertex_tail = NULL; // �e�[����NULL�ɐݒ�
	vertexCount = 0; // ���_�������Z�b�g
	next = NULL; // ���̌`��ւ̃|�C���^��NULL�ɐݒ�
	isClosedFlag = false; // �����}�`�t���O�����Z�b�g
}

void CShape::freeVertex(float x, float y) {
	for (CVertex* current = vertex_head; current != NULL; current = current->GetNext()) {
		if (current->GetX() == x && current->GetY() == y) {
			CVertex* prev = current->GetPre();
			CVertex* next = current->GetNext();

			if (prev != NULL && next != NULL) {
				prev->SetNext(next);
				next->SetPre(prev);
			}
			// �폜�Ώۂ��擪(head)�̏ꍇ
			else if (prev == NULL) { 
				vertex_head = next;
				if (vertex_head != NULL) vertex_head->SetPre(NULL);
				if (GetIsClosedFlag() && vertex_head != NULL) vertex_tail->SetXY(vertex_head->GetX(), vertex_head->GetY());
			}
			// �폜�Ώۂ�����(tail)�̏ꍇ
			else if (next == NULL) {
				vertex_tail = prev; 
				if (vertex_tail != NULL) vertex_tail->SetNext(NULL); 
			}

			delete current;
			vertexCount--;
			return;
		}
	}
}

void CShape::freeVertexTail() {

	vertex_tail = vertex_tail->GetPre();
	isClosedFlag = false;
	vertexCount--;
	delete vertex_tail->GetNext();
	vertex_tail->SetNext(NULL);
}

void CShape::insertVertex(CVertex* preVertex, CVertex* newVertex) {

	CVertex* nextVertex = preVertex->GetNext();

	preVertex->SetNext(newVertex);
	newVertex->SetNext(nextVertex);

	newVertex->SetPre(preVertex);
	nextVertex->SetPre(newVertex);
	vertexCount++;
}
