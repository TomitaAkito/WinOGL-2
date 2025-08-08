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
		vertexCount++; // ���_�̐��𑝂₷
	}
	// ���_����3�ȉ��̏ꍇ�͐ݒ�
	else if (vertexCount < 3) {
		// �����̒��_���X�g�ɒǉ�
		vertex_tail->SetNext(newVertex);
		newVertex->SetPre(vertex_tail);
		vertex_tail = newVertex; // �V�������_���e�[���Ƃ��Đݒ�
		vertexCount++; // ���_�̐��𑝂₷
	}
	else if (isSelfCrossed(newVertex)){



	}
	
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

bool CShape::isSelfCrossed(CVertex* newVertex) {
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
	CVertex* current = vertex_head;
	while (current != NULL) {
		if (current->GetX() == x && current->GetY() == y) {
			// ��v���钸�_�����������ꍇ
			if (current->GetPre() != NULL) {
				current->GetPre()->SetNext(current->GetNext());
			}
			else {
				vertex_head = current->GetNext(); // �擪�̒��_���X�V
			}
			if (current->GetNext() != NULL) {
				current->GetNext()->SetPre(current->GetPre());
			}
			else {
				vertex_tail = current->GetPre(); // �����̒��_���X�V
			}
			delete current; // ���_���폜
			vertexCount--; // ���_�������炷
			return; // �����I��
		}
		current = current->GetNext(); // ���̒��_�ֈړ�
	}
}
