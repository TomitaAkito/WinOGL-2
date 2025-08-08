#include "pch.h"
#include "CShape.h"

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

	}
	else {
		// �����̒��_���X�g�ɒǉ�
		vertex_tail->SetNext(newVertex);
		newVertex->SetPre(vertex_tail);
		vertex_tail = newVertex; // �V�������_���e�[���Ƃ��Đݒ�
	}
	vertexCount++; // ���_�̐��𑝂₷
}

CShape* CShape::GetNext() {
	return next;
}


void CShape::SetNext(CShape* nextShape) {
	this->next = nextShape;
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
