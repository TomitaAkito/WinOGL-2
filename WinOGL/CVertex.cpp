#include "pch.h"
#include "CVertex.h"


CVertex::CVertex() {

	// ‰Šú‰»
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
CVertex::~CVertex() {
}
float CVertex::GetX() {
	return x;
}
float CVertex::GetY() {
	return y;
}

float CVertex::GetZ() {
	return z;
}

void CVertex::SetXY(float x, float y) {
	SetX(x);
	SetY(y);
}

CVertex* CVertex::GetNext() {
	return next;
}

CVertex* CVertex::GetPre() {
	return pre;
}

void CVertex::SetX(float x) {
	this->x = x;
}

void CVertex::SetY(float y) {
	this->y = y;
}

void CVertex::SetZ(float z) {
	this->z = z;
}

void CVertex::SetNext(CVertex* nextPointer) {
	this->next = nextPointer;
}

void CVertex::SetPre(CVertex* prePointer) {
	this->pre = prePointer;
}

void CVertex::SetVertex(float x, float y) {
	this->x = x;
	this->y = y;
}
