#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl(){
	shape_head = NULL;
	shape_tail = NULL;
	CLOSE_DISTANCE = 0.05f;
}

CAdminControl::~CAdminControl()
{
}

void CAdminControl::Draw()
{
	// 点の描画
	DrawVertex();
	// 線の描画
	DrawLine();
}

void CAdminControl::DrawVertex() {

	// 色・サイズの設定
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(10.0);
	glBegin(GL_POINTS);

	// 頂点リストを走査して頂点を描画
	for (CShape* current_shape = shape_head; current_shape != NULL; current_shape = current_shape->GetNext()) {
		for (CVertex* current = current_shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			//glVertex3f(current->GetX(), current->GetY(), current->GetZ());
			glVertex2f(current->GetX(), current->GetY());
		}
	}
	
	glEnd();
}

void CAdminControl::DrawLine() {
	// 色・サイズの設定
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	
	for (CShape* current_shape = shape_head; current_shape != NULL; current_shape = current_shape->GetNext()) {
		// 頂点リストを走査して線を描画
		for (CVertex* current = current_shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (current->GetNext() != NULL) {
				glVertex3f(current->GetX(), current->GetY(), current->GetZ());
				glVertex3f(current->GetNext()->GetX(), current->GetNext()->GetY(), current->GetNext()->GetZ());
			}
		}
	}


	glEnd();
}

void CAdminControl::SetVertex(float mouse_x, float mouse_y) {
	CMath math;

	// マウス座標を使用して新しい頂点を作成
	CVertex* newVertex = new CVertex(mouse_x, mouse_y);

	// 図形を管理するオブジェクトが存在しない場合は新規作成
	if (shape_head == NULL) {
		shape_head = new CShape();
		shape_tail = shape_head; // 最初の形状はヘッドとテールが同じ
	}

	// 他交差する場合は終了
	if (isShapeCross(newVertex)) return;
	
	// 内包する場合は終了
	if (isConnotation(newVertex)) return;

	// 新しい頂点を追加
	shape_tail->SetVertexByPointer(newVertex);

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

bool CAdminControl::isShapeCross(CVertex* newVertex) {

	// 1つ目は許す
	if (shape_tail->GetVertexCount() < 1) return false;
	
	for (CShape* currentShape = shape_head; currentShape != shape_tail; currentShape = currentShape->GetNext()) {
		
		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			if (currentShape->isSelfCrossedBy2Lines(shape_tail->GetVertexTail(), newVertex, current, current->GetNext())) return true;
		}

	}

	return false;
}

bool CAdminControl::isConnotation(CVertex* newVertex) {
	// 頂点が内包しているか
	if(isConnotationVertex(newVertex)) return true;

	// 図形が内包しているか
	if (isConnotationShape(newVertex)) return true;

	return false;
}

bool CAdminControl::isConnotationVertex(CVertex* newVertex) {
	CMath math;
	float sumAngle = 0;
	CVector* a = new CVector();
	CVector* b = new CVector();

	for (CShape* currentShape = shape_head; currentShape != shape_tail; currentShape = currentShape->GetNext()) {

		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			a->SetByVertex(newVertex, current);
			b->SetByVertex(newVertex, current->GetNext());

			sumAngle += math.calcAngle(a, b);
		}
	}
	delete a, b;

	if (3.10 * 2 < math.absFloat(sumAngle)) return true;
	return false;
}

bool CAdminControl::isConnotationShape(CVertex* newVertex) {
	
	CMath math;
	float sumAngle = 0;
	float tanAnglel;
	CVector* a = new CVector();
	CVector* b = new CVector();

	// もし図形が閉じれるのであれば閉じる
	if ((shape_tail->GetVertexCount() >= 3) && (math.calcDistance(shape_tail->GetVertexHead(), newVertex) < CLOSE_DISTANCE)) {
		
		shape_tail->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // 閉じた図形にする

		for (CShape* currentShape = shape_head; currentShape->GetNext() != NULL; currentShape = currentShape->GetNext()) {
			for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
				if (math.calcAngleByShape(shape_tail, current) > 3.10 * 2) {
					shape_tail->freeVertexTail();
					delete a, b;
					return true;
				}

			}
		}
		shape_tail->freeVertexTail();
	}
	delete a, b;
	return false;
}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < CLOSE_DISTANCE )) {

		// 閉じる図形の処理
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // 閉じた図形にする
		
		// 図形リストに新しい図形を加える
		CShape* newShape = new CShape();
		shape_tail->SetNext(newShape); // 新しい図形を次に設定
		shape_tail = newShape; // テールを新しい図形に更新
	}
}
