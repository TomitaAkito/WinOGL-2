#include "pch.h"
#include "CVector.h"

CVector::CVector() {
	x = 0.0f; // X�����̏�����
	y = 0.0f; // Y�����̏�����
}

CVector::CVector(float x, float y) {
	this->x = x; // X�����̏�����
	this->y = y; // Y�����̏�����
}

CVector::CVector(CVertex* a, CVertex* b) {
	this->x = b->GetX() - a->GetX();
	this->y = b->GetY() - a->GetY();
}

CVector::~CVector() {
}


void CVector::SetX(float x) {
	this->x = x; // X������ݒ�
}

float CVector::GetX() {
	return x; // X�������擾
}

void CVector::SetY(float y) {
	this->y = y; // Y������ݒ�
}

float CVector::GetY() {
	return y; // Y�������擾
}

void CVector::SetByVertex(CVertex* a, CVertex* b) {
	this->x = b->GetX() - a->GetX();
	this->y = b->GetY() - a->GetY();
}
