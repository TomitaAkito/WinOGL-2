#include "pch.h"
#include "CAdminControl.h"
#include <gl/GL.h>

CAdminControl::CAdminControl(){
	shape_head = NULL;
	shape_tail = NULL;
	CLOSE_DISTANCE = 0.05f;
	POINTSIZE = 10.0f;
	LINEWIDTH = 4.0f;
	AxisFlag = false;
	mouseVertex = new CVertex();
}

CAdminControl::~CAdminControl()
{
}

void CAdminControl::Draw()
{
	// 予測線
	DrawPredictLine();

	// 点の描画
	DrawVertex();
	// 線の描画
	DrawLine();

	// 座標軸の表示
	if (AxisFlag) DrawAxis();
}

void CAdminControl::DrawVertex() {

	// 色・サイズの設定
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(POINTSIZE);
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
	glLineWidth(LINEWIDTH);
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

void CAdminControl::DrawSizeChangeUP() {
	if (LINEWIDTH <= 10.0) {
		POINTSIZE += 0.7;
		LINEWIDTH += 0.4;
	}
}

void CAdminControl::DrawSizeChangeDOWN() {
	if (LINEWIDTH >= 1.0) {
		POINTSIZE -= 0.7;
		LINEWIDTH -= 0.4;
	}
}

void CAdminControl::DrawAxis() {
	glBegin(GL_LINES);
	// x軸
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y軸
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z軸
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}

void CAdminControl::DrawPredictLine() {
	bool NGFlag = false;

	// 図形が閉じている場合は終了
	if (shape_tail == NULL || shape_tail->GetIsClosedFlag() || shape_tail->GetVertexTail() == NULL)return;
	if (mouseVertex == NULL) return;

	// 破線を可能にする
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);	//破線のパターンの指定（0xF0F0の部分がそれ）
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINE_STRIP);

	// 他交差
	if (isShapeCross(mouseVertex)) NGFlag = true;
	// 内包
	if (isConnotation(mouseVertex)) NGFlag = true;
	// 図形内の処理
	if (!shape_tail->isDrawPredict(mouseVertex)) NGFlag = true;

	if(NGFlag) glColor3f(1.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);

	glVertex3f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY(), shape_tail->GetVertexTail()->GetZ());
	glVertex3f(mouseVertex->GetX(), mouseVertex->GetY(), mouseVertex->GetZ());

	glEnd();
	glDisable(GL_LINE_STIPPLE);
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

void CAdminControl::SetMouseVertex(float mouse_x, float mouse_y) {
	mouseVertex->SetVertex(mouse_x, mouse_y);
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
	
	for (CShape* currentShape = shape_head; currentShape != shape_tail; currentShape = currentShape->GetNext()) {

		/*for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			a->SetByVertex(newVertex, current);
			b->SetByVertex(newVertex, current->GetNext());

			sumAngle += math.calcAngle(a, b);
		}*/

		sumAngle = math.calcAngleByShape(currentShape, newVertex);
	}


	if (3.10 * 2 < math.absFloat(sumAngle)) return true;
	return false;
}

bool CAdminControl::isConnotationShape(CVertex* newVertex) {
	
	CMath math;
	float sumAngle = 0;
	float tanAnglel;

	// もし図形が閉じれるのであれば閉じる
	if ((shape_tail->GetVertexCount() >= 3) && (math.calcDistance(shape_tail->GetVertexHead(), newVertex) < CLOSE_DISTANCE)) {
		
		shape_tail->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // 閉じた図形にする

		for (CShape* currentShape = shape_head; currentShape->GetNext() != NULL; currentShape = currentShape->GetNext()) {
			for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
				if (math.calcAngleByShape(shape_tail, current) > 3.10 * 2) {
					shape_tail->freeVertexTail();
					return true;
				}

			}
		}
		shape_tail->freeVertexTail();
	}
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
