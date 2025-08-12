#include "pch.h"
#include "CShape.h"
#include "CVector.h"
#include "CMath.h"

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
		return;
	}

	// vertex_headと一緒ならこのまま処理を実行
	CMath math;
	if (math.isXYZ(newVertex, this->GetVertexHead())) {
		NormalAddVertex(newVertex);
		return;
	}
	
	// 頂点数が3以下の場合は設定
	if (vertexCount < 3) {
		NormalAddVertex(newVertex);
		return;
	}
	
	// 自交差しなければOK
	if (!isSelfCrossed(newVertex)) {
		NormalAddVertex(newVertex);
	}	
}

void CShape::NormalAddVertex(CVertex* newVertex) {
	// 既存の頂点リストに追加
	vertex_tail->SetNext(newVertex);
	newVertex->SetPre(vertex_tail);
	vertex_tail = newVertex; // 新しい頂点をテールとして設定
	vertexCount++; // 頂点の数を増やす
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

	// 頂点数が3以下の場合は設定
	if (vertexCount < 3) return true;

	// 自交差しなければOK
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
	// 例外処理
	if (this->GetVertexCount() <= 3) return false;

	for (CVertex* current = this->GetVertexHead()->GetNext(); current->GetNext() != this->GetVertexTail(); current = current->GetNext()) {
		if (isSelfCrossedBy2Lines(this->GetVertexTail(), this->GetVertexHead(), current, current->GetNext())) return true;
	}
	return false;
}

bool CShape::isSelfCrossedBy2Lines(CVertex* As, CVertex* Ae, CVertex* Bs, CVertex* Be) {

	// ベクトルに変換
	CVector* a = new CVector(As, Ae);
	CVector* b = new CVector(Bs, Be);
	CVector* a1 = new CVector(As, Bs);
	CVector* b1 = new CVector(Bs, As);
	CVector* a2 = new CVector(As, Be);
	CVector* b2 = new CVector(Bs, Ae);
	CMath math;

	// 外積を計算
	float ca1 = math.calcCrossProduct(a, a1);
	float ca2 = math.calcCrossProduct(a, a2);
	float cb1 = math.calcCrossProduct(b, b1);
	float cb2 = math.calcCrossProduct(b, b2);
	// メモリ解放
	delete a, b, a1, b1, a2, b2;

	if ((ca1 * ca2 <= 0) && (cb1 * cb2 <= 0)) return true;
	return false;
}

bool CShape::isMoveVertexSelfCross(CVertex* selectVertex, CVertex* nextVertex, CShape* shape_head) {
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		// 例外処理
		if (currentShape->GetVertexHead() == NULL)continue;
		if (currentShape->GetVertexCount() < 2)continue;

		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {

			// 例外処理(selectVertexと一致する場合)
			if (selectVertex == current || nextVertex == current) continue;
			if (selectVertex == vertex_head && this->GetIsClosedFlag()) selectVertex = vertex_tail;
			if (selectVertex == current->GetNext()) continue;

			if (current->GetNext() != NULL && isSelfCrossedBy2Lines(current, current->GetNext(), selectVertex, nextVertex)) {
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

void CShape::freeVertexTail() {

	vertex_tail = vertex_tail->GetPre();
	isClosedFlag = false;
	vertexCount--;
	delete vertex_tail->GetNext();
	vertex_tail->SetNext(NULL);
}
