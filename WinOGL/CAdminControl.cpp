#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl(){
	shape_head = NULL;
	shape_tail = NULL;
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
			glVertex3f(current->GetX(), current->GetY(), current->GetZ());
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
	CVertex* newVertex = new CVertex();
	newVertex->SetVertex(mouse_x, mouse_y);

	// 図形を管理するオブジェクトが存在しない場合は新規作成
	if (shape_head == NULL) {
		shape_head = new CShape();
		shape_tail = shape_head; // 最初の形状はヘッドとテールが同じ
	}
	
	// 頂点数が3より小さいのであれば頂点追加
	if (shape_tail->GetVertexCount() < 3) {
		shape_tail->SetVertexByPointer(newVertex); // 新しい頂点を追加
		return;
	}
	
	shape_tail->SetVertexByPointer(newVertex); // 新しい頂点を追加

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < 0.05f )) {

		// 閉じる図形の処理
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // 閉じた図形にする
		
		// 図形リストに新しい図形を加える
		CShape* newShape = new CShape();
		shape_tail->SetNext(newShape); // 新しい図形を次に設定
		shape_tail = newShape; // テールを新しい図形に更新
	}
}
