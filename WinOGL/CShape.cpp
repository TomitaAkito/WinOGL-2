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
		vertexCount++; // 頂点の数を増やす
	}
	// 頂点数が3以下の場合は設定
	else if (vertexCount < 3) {
		// 既存の頂点リストに追加
		vertex_tail->SetNext(newVertex);
		newVertex->SetPre(vertex_tail);
		vertex_tail = newVertex; // 新しい頂点をテールとして設定
		vertexCount++; // 頂点の数を増やす
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
		delete current; // 現在の頂点を削除
		current = nextVertex; // 次の頂点に移動
	}
	vertex_head = NULL; // 頂点リストを空にする
	vertex_tail = NULL; // テールもNULLに設定
	vertexCount = 0; // 頂点数をリセット
	next = NULL; // 次の形状へのポインタもNULLに設定
	isClosedFlag = false; // 閉じた図形フラグもリセット
}

void CShape::freeVertex(float x, float y) {
	CVertex* current = vertex_head;
	while (current != NULL) {
		if (current->GetX() == x && current->GetY() == y) {
			// 一致する頂点が見つかった場合
			if (current->GetPre() != NULL) {
				current->GetPre()->SetNext(current->GetNext());
			}
			else {
				vertex_head = current->GetNext(); // 先頭の頂点を更新
			}
			if (current->GetNext() != NULL) {
				current->GetNext()->SetPre(current->GetPre());
			}
			else {
				vertex_tail = current->GetPre(); // 末尾の頂点を更新
			}
			delete current; // 頂点を削除
			vertexCount--; // 頂点数を減らす
			return; // 処理終了
		}
		current = current->GetNext(); // 次の頂点へ移動
	}
}
