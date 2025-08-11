#include "pch.h"
#include "CVector.h"

CVector::CVector() {
	x = 0.0f; // X¬•ª‚Ì‰Šú‰»
	y = 0.0f; // Y¬•ª‚Ì‰Šú‰»
}

CVector::CVector(float x, float y) {
	this->x = x; // X¬•ª‚Ì‰Šú‰»
	this->y = y; // Y¬•ª‚Ì‰Šú‰»
}

CVector::CVector(CVertex* a, CVertex* b) {
	this->x = b->GetX() - a->GetX();
	this->y = b->GetY() - a->GetY();
}

CVector::~CVector() {
}


void CVector::SetX(float x) {
	this->x = x; // X¬•ª‚ðÝ’è
}

float CVector::GetX() {
	return x; // X¬•ª‚ðŽæ“¾
}

void CVector::SetY(float y) {
	this->y = y; // Y¬•ª‚ðÝ’è
}

float CVector::GetY() {
	return y; // Y¬•ª‚ðŽæ“¾
}

void CVector::SetByVertex(CVertex* a, CVertex* b) {
	this->x = b->GetX() - a->GetX();
	this->y = b->GetY() - a->GetY();
}
