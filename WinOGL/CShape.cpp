#include "pch.h"
#include "CShape.h"

CShape::CShape() {
	// 初期化
	vertex_head = NULL;
	vertex_tail = NULL;
	next = NULL; // 次の形状へのポインタも初期化
	isClosedFlag = false; // 初期状態では閉じていない
	vertexCount = 0; // 頂点の数も初期化
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
	// もしvertex_headがNULLならば、最初の頂点として設定
	if (vertex_head == NULL) {
		vertex_head = newVertex;
		vertex_tail = newVertex; // 最初の頂点はヘッドとテールが同じ

	}
	else {
		// 既存の頂点リストに追加
		vertex_tail->SetNext(newVertex);
		newVertex->SetPre(vertex_tail);
		vertex_tail = newVertex; // 新しい頂点をテールとして設定
	}
	vertexCount++; // 頂点の数を増やす
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
