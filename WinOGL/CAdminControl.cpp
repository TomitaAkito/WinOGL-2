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
	EditFlag = false;
	LButtonDownFlag = false;
	MoveMouseVertex = new CVertex();
	beforMoveMouseVertex = new CVertex();
	selectVertexPointer = new CVertex();
	selectLinePointer = new CVertex();
	selectShapePointer = new CShape();
	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;
	ShiftFlag = false;
	keyRFlag = false;
	selectNum = 0;
	LButtonDownVeretex = new CVertex();
	resizeShapeCopy = new CShape();
}

CAdminControl::~CAdminControl(){
	freeALLShape();
	delete MoveMouseVertex, beforMoveMouseVertex, resizeShapeCopy;
}

void CAdminControl::Draw()
{
	// 予測線
	if(!EditFlag) DrawPredictLine();

	// 点の描画
	DrawVertex();

	// 線の描画
	DrawLine();

	// 座標軸の表示
	if (AxisFlag) DrawAxis();

	// 編集モード系の描画
	if (EditFlag) DrawEdit();
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
	if (MoveMouseVertex == NULL) return;

	// 破線を可能にする
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);	//破線のパターンの指定（0xF0F0の部分がそれ）
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINE_STRIP);

	// 他交差
	if (isShapeCross(MoveMouseVertex)) NGFlag = true;
	// 内包
	if (isConnotation(MoveMouseVertex)) NGFlag = true;
	// 図形内の処理
	if (!shape_tail->isDrawPredict(MoveMouseVertex)) NGFlag = true;

	if(NGFlag) glColor3f(1.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);

	glVertex3f(shape_tail->GetVertexTail()->GetX(), shape_tail->GetVertexTail()->GetY(), shape_tail->GetVertexTail()->GetZ());
	glVertex3f(MoveMouseVertex->GetX(), MoveMouseVertex->GetY(), MoveMouseVertex->GetZ());

	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void CAdminControl::DrawEdit() {
	if (selectVertexFlag) DrawSelectVertex(selectVertexPointer);
	if (selectLineFlag) DrawSelectLine(selectLinePointer, selectLinePointer->GetNext());
	if (selectShapeFlag) DrawSelectShape(selectShapePointer);
}

void CAdminControl::DrawSelectVertex(CVertex* vertex) {
	// 色・サイズの設定
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);
	glVertex3f(vertex->GetX(), vertex->GetY(), vertex->GetZ());

	glEnd();
}

void CAdminControl::DrawSelectLine(CVertex* lineStart, CVertex* lineEnd) {
	// 色・サイズの設定
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);
	glVertex3f(lineStart->GetX(), lineStart->GetY(), lineStart->GetZ());
	glVertex3f(lineEnd->GetX(), lineEnd->GetY(), lineEnd->GetZ());


	glEnd();
}

void CAdminControl::DrawSelectShape(CShape* shape) {
	// 色・サイズの設定
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);

	// 頂点リストを走査して頂点を描画
	for (CVertex* current = shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		//glVertex3f(current->GetX(), current->GetY(), current->GetZ());
		glVertex2f(current->GetX(), current->GetY());
	}
	glEnd();


	// 色・サイズの設定
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(LINEWIDTH);
	glBegin(GL_LINES);

	// 頂点リストを走査して線を描画
	for (CVertex* current = shape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		if (current->GetNext() != NULL) {
			glVertex3f(current->GetX(), current->GetY(), current->GetZ());
			glVertex3f(current->GetNext()->GetX(), current->GetNext()->GetY(), current->GetNext()->GetZ());
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

	// 他交差するか，内包する場合は終了
	if (isShapeCross(newVertex)|| isConnotation(newVertex)) {
		delete newVertex;
		return;
	}

	// 新しい頂点を追加
	shape_tail->SetVertexByPointer(newVertex);

	if (!shape_tail->isSelfCrossedByHourGlassType()) closeShape();

}

void CAdminControl::SetMouseVertex(float mouse_x, float mouse_y) {
	beforMoveMouseVertex->SetVertex(MoveMouseVertex->GetX(), MoveMouseVertex->GetY());
	MoveMouseVertex->SetVertex(mouse_x, mouse_y);
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

bool CAdminControl::isConnotationMoveVertex(CVertex* vertex) {
	
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL) continue;
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			for (CShape* surchShape = shape_head; surchShape != NULL; surchShape = surchShape->GetNext()) {
				if (surchShape->GetVertexHead() == NULL) continue;
				if (surchShape == currentShape) continue;
				CMath math;
				if (math.calcAngleByShape(surchShape, current) > 6) return true;
			}
		}
	}
	return false;
}
bool CAdminControl::isConnotationFreeVertex(CVertex* vertex, CShape* shape) {

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			for (CShape* surchShape = shape_head; surchShape != NULL; surchShape = surchShape->GetNext()) {
				if (surchShape->GetVertexHead() == NULL) continue;
				if (surchShape == currentShape) continue;
				CMath math;
				if (math.calcAngleByShape(surchShape, current) > 6) return true;
			}
		}
	}

	return false;
}
void CAdminControl::Edit(float mouse_x, float mouse_y) {
	
	if (ShiftFlag || keyRFlag)return;
	
	// マウスを座標として指定する
	CVertex* LMouseVertex = new CVertex(mouse_x,mouse_y);

	// 頂点の挿入用に現時点のselectLineを保存
	CVertex* tmpSelectLine = selectLinePointer;

	// 探索
	bool VertexFlag = selectVertex(LMouseVertex);
	bool LineFlag = selectLine(LMouseVertex);	
	bool ShapeFlag = selectShape(LMouseVertex);

	selectVertexFlag = false;
	selectLineFlag = false;
	selectShapeFlag = false;


	// 優先順位を設ける
	if (VertexFlag) selectVertexFlag = true;
	else if (LineFlag) selectLineFlag = true;
	else if (ShapeFlag) {
		selectShapeFlag = true;
		resizeShapeCopy = copyShape(selectShapePointer);
	}

	// 点を挿入するか
	if (selectLineFlag && tmpSelectLine == selectLinePointer) {
		insertVertex(LMouseVertex);
		selectLineFlag = false;
		selectVertexFlag = true;
		selectVertexPointer = LMouseVertex;
		return;
	}

	delete LMouseVertex;
}

bool CAdminControl::selectVertex(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (math.calcDistance(current, LMouseVertex) < CLOSE_DISTANCE) {
				selectVertexPointer = current;
				return true;
			}
		}
	}

	return false;
}

bool CAdminControl::selectLine(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL) break;

		for (CVertex* current = currentShape->GetVertexHead(); current->GetNext() != NULL; current = current->GetNext()) {
			if (math.calcPointLineDistance(current, current->GetNext(), LMouseVertex) < CLOSE_DISTANCE) {
				CVector* a = new CVector(current, LMouseVertex);
				CVector* b = new CVector(current, current->GetNext());
				float theta1 = math.calcAngle(a,b);

				a->SetByVertex(current->GetNext(), LMouseVertex);
				b->SetByVertex(current->GetNext(), current);
				float theta2 = math.calcAngle(a, b);
				delete a, b;
				
				if ((-3.15 / 2 < theta1 && theta1 < 3.15 / 2) && (-3.15 / 2 < theta2 && theta2 < 3.15 / 2)) {
					selectLinePointer = current;
					return true;

				}

			}
		}
	}

	return false;
}

bool CAdminControl::selectShape(CVertex* LMouseVertex) {
	CMath math;

	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape->GetVertexHead() == NULL)break;

		if (math.calcAngleByShape(currentShape, LMouseVertex) > 6) {
			selectShapePointer = currentShape;
			return true;
		}
	}
	return false;
}

void CAdminControl::moveByMouse() {
	if (selectVertexFlag)moveVertex(MoveMouseVertex);
	else if (selectShapeFlag)moveShape(MoveMouseVertex);
}

void CAdminControl::moveVertex(CVertex* mouseVertex) {

	if (!selectVertexFlag)return;

	//== 座標を一時保存し、頂点を移動 ==
	// 元の座標を保存
	float originalX = selectVertexPointer->GetX();
	float originalY = selectVertexPointer->GetY();

	CShape* shape = serchShapeByVertex(selectVertexPointer); // 選択中の頂点が含まれる図形を取得
	CMath math;

	// 選択した頂点が、閉じた図形の始点／終点と同じ位置にあるか判定
	bool isClosedShapeEndpoint = false;
	if (shape->GetIsClosedFlag() && math.isXYZ(selectVertexPointer, shape->GetVertexHead())) isClosedShapeEndpoint = true;

	// 最初に頂点をマウス座標へ移動させる
	selectVertexPointer->SetXY(mouseVertex->GetX(), mouseVertex->GetY());

	// もし閉じた図形の端点なら、対になる頂点（Tail）も動かす
	if (isClosedShapeEndpoint) shape->GetVertexTail()->SetXY(mouseVertex->GetX(), mouseVertex->GetY());

	//== 問題ないかをチェック ==
	bool ERRFlag = false;

	// 前の頂点を取得
	CVertex* preVertex = selectVertexPointer->GetPre();
	if (preVertex == NULL && isClosedShapeEndpoint) preVertex = shape->GetVertexTail()->GetPre();

	// 次の頂点を取得
	CVertex* nextVertex = selectVertexPointer->GetNext();
	if (nextVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) nextVertex = shape->GetVertexHead();

	
	// 交差判定
	if (nextVertex != NULL && shape->isMoveVertexSelfCross(selectVertexPointer, nextVertex, shape_head)) ERRFlag = true;
	if (!ERRFlag && preVertex != NULL && shape->isMoveVertexSelfCross(preVertex, selectVertexPointer, shape_head)) ERRFlag = true;

	// 内包判定
	if (isConnotationMoveVertex(selectVertexPointer)) ERRFlag = true;
	

	//== 問題がある場合は元の座標に戻す ==
	if (ERRFlag) {
		selectVertexPointer->SetXY(originalX, originalY);
		if (isClosedShapeEndpoint) shape->GetVertexTail()->SetXY(originalX, originalY);
	}
		
}

void CAdminControl::moveShape(CVertex* mouseVertex) {

	if (!selectShapeFlag)return;

	// 移動量算出
	CMath math;
	float movement[2];
	math.calcMovementByVertex(beforMoveMouseVertex, mouseVertex, movement);

	// 移動量に基づき移動
	selectShapePointer->moveByMovement(movement[0],movement[1]);
	
	// 図形が1つしかない場合はスキップ
	if (shape_head->GetNext() == NULL) return;

	// 問題があるかチェック
	bool ERRFlag = false;
	for (CVertex* current = selectShapePointer->GetVertexHead(); current != selectShapePointer->GetVertexTail(); current = current->GetNext()) {
		// 交差判定 || 内包判定
		if ((current->GetPre() != NULL && selectShapePointer->isMoveVertexSelfCross(current->GetPre(), current, shape_head))
			||(isConnotationMoveVertex(current))){
			ERRFlag = true;
			break;
		}
	}

	// 問題がある場合は元の座標に戻す
	if (ERRFlag)
		selectShapePointer->moveByMovement((-1) * movement[0], (-1) * movement[1]);
}

void CAdminControl::insertVertex(CVertex* mouseVertex) {
	if (!selectLineFlag) return;
	CShape* shape = serchShapeByVertex(selectLinePointer);
	CVertex* nextVertex = selectLinePointer->GetNext();

	selectLinePointer->SetNext(mouseVertex);
	mouseVertex->SetPre(selectLinePointer);
	mouseVertex->SetNext(nextVertex);
	nextVertex->SetPre(mouseVertex);

	shape->SetVertexCount(shape->GetVertexCount() + 1);
	selectVertexPointer = mouseVertex;
}

//void CAdminControl::deleteVertex() {
	//// 例外処理
	//if (!EditFlag || !selectVertexFlag)return;
	//CShape* shape = serchShapeByVertex(selectVertexPointer);
	//if (shape->GetIsClosedFlag() && shape->GetVertexCount() <= 4) return;
	//if (!shape->GetIsClosedFlag() && shape->GetVertexCount() <= 1) return;

	//// 一旦保存
	//CVertex* vertexToDelete = selectVertexPointer;
	//CVertex* preVertex = selectVertexPointer->GetPre();
	//CVertex* backupVertex = new CVertex(vertexToDelete->GetX(), vertexToDelete->GetY());

	//// GoodBye
	//shape->freeVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());
	//
	//bool ERRFlag = false;
	//// 内包判定
	//if (shape->GetIsClosedFlag() && isConnotationFreeVertex(backupVertex, shape)) ERRFlag = true;
	//
	//// 交差判定
	//if (!ERRFlag && preVertex != NULL) {
	//	CVertex* nextVertex = preVertex->GetNext();
	//	if (nextVertex != NULL) {
	//		if (shape->isMoveVertexSelfCross(preVertex, nextVertex, shape_head) ||
	//			(nextVertex->GetNext() != NULL && shape->isMoveVertexSelfCross(nextVertex, nextVertex->GetNext(), shape_head))) {
	//			ERRFlag = true;
	//		}
	//	}
	//}

	//// 問題があればもとに戻す
	//if (ERRFlag) {
	//	// 問題があれば、バックアップから頂点を復元
	//	shape->insertVertex(preVertex, backupVertex);
	//	selectVertexPointer = backupVertex;
	//	return;
	//}
	//else {
	//	delete backupVertex;
	//	return;
	//}

void CAdminControl::deleteVertex() {
	/* 学部時代のソースコードを改変しました。難しいです。無理です。 */

	// 例外処理
	if (!selectVertexFlag) return;
	
	// 頂点が含まれる図形の探索
	CShape* shape = serchShapeByVertex(selectVertexPointer);

	// 保険(もし内包した場合のVertex)
	CVertex* BFVertex = selectVertexPointer->GetPre();
	CVertex* vertex = new CVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());
	vertex->SetNext(selectVertexPointer->GetNext());


	// 図形が三角形なら
	if (shape->GetVertexCount() <= 4 && shape->GetIsClosedFlag()) return;

	// 頂点を削除
	else {
		// 判定用vertexの設定
		if (BFVertex == NULL && shape->GetIsClosedFlag()) BFVertex = shape->GetVertexTail()->GetPre();

		// 一旦削除
		shape->freeVertex(selectVertexPointer->GetX(), selectVertexPointer->GetY());

		// 判定用vertexの設定
		CVertex* nowVertex = NULL;
		if (BFVertex != NULL) {
			nowVertex = BFVertex->GetNext();
			if (nowVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) nowVertex = shape->GetVertexHead();
		}

		CVertex* AFVertex = NULL;
		if (nowVertex != NULL) {
			AFVertex = nowVertex->GetNext();
			if (AFVertex == shape->GetVertexTail() && shape->GetIsClosedFlag()) AFVertex = shape->GetVertexHead();
		}

		bool ErrFlag = false;

		// 内包判定
		if (shape->GetIsClosedFlag() && isConnotationFreeVertex(vertex, shape)) {
			ErrFlag = true;
		}

		// 交差判定
		bool flag = true;
		if (BFVertex == NULL || nowVertex == NULL) flag = false;
		if (flag && shape->isMoveVertexSelfCross(BFVertex, nowVertex, shape_head)) {
			ErrFlag = true;
		}
		flag = true;
		if (AFVertex == NULL || nowVertex == NULL) flag = false;
		if (flag && shape->isMoveVertexSelfCross(nowVertex, AFVertex, shape_head)) {
			ErrFlag = true;
		}

		if (ErrFlag) {
			// もとに戻す(vertexを挿入する)
			shape->insertVertex(BFVertex, vertex);
			selectVertexPointer = vertex;
			return;
		}
	}
	// もし形状が保てない(vertexの数が0)場合は形状を消す
	if (shape->GetVertexCount() == 0) freeShape(shape);
	return;
}

void CAdminControl::resizeShape() {
	if (!selectShapeFlag)return;

	// 移動量算出
	CMath math;
	float resizeRate[2];
	math.calcResizeRate(LButtonDownVeretex, MoveMouseVertex, resizeRate);
	CShape* cpShape = copyShape(selectShapePointer);

	// 移動量に基づき移動
	selectShapePointer->resizeShape(resizeRate[0], resizeRate[0], resizeShapeCopy);

	// 図形が1つしかない場合はスキップ
	if (shape_head->GetNext() == NULL) return;

	// 問題があるかチェック
	bool ERRFlag = false;
	for (CVertex* current = selectShapePointer->GetVertexHead(); current != selectShapePointer->GetVertexTail(); current = current->GetNext()) {
		// 交差判定 || 内包判定
		if ((current->GetPre() != NULL && selectShapePointer->isMoveVertexSelfCross(current->GetPre(), current, shape_head))
			|| (isConnotationMoveVertex(current))) {
			ERRFlag = true;
			break;
		}
	}

	if (0.01 >= math.calcShapeArea(selectShapePointer))
		ERRFlag = true;
		
	// 問題がある場合は元の座標に戻す
	if (ERRFlag)
		copyShapeByShape(cpShape, selectShapePointer);

	delete cpShape;
}

void CAdminControl::closeShape() {
	CMath math;

	if ((shape_tail->GetVertexCount() >= 4) && (math.calcDistance(shape_tail->GetVertexHead(), shape_tail->GetVertexTail()) < CLOSE_DISTANCE )) {

		// 閉じる図形の処理
		shape_tail->GetVertexTail()->SetVertex(shape_tail->GetVertexHead()->GetX(), shape_tail->GetVertexHead()->GetY());
		shape_tail->SetIsClosed(true); // 閉じた図形にする
		CVertex* COG = math.calcCOGByShape(shape_tail);
		shape_tail->COGVertex->SetXY(COG->GetX(), COG->GetY());
		delete COG;
		
		// 図形リストに新しい図形を加える
		CShape* newShape = new CShape();
		shape_tail->SetNext(newShape); // 新しい図形を次に設定
		shape_tail = newShape; // テールを新しい図形に更新
	}
}

CShape* CAdminControl::serchShapeByVertex(CVertex* vertex) {
	CMath math;
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		for (CVertex* current = currentShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
			if (math.isXYZ(current, vertex)) return currentShape;
		}
	}
	return NULL;
}

void CAdminControl::freeShape(CShape* shape) {
	CShape* beforShape = NULL;
	// 前の図形を調べる
	for (CShape* currentShape = shape_head; currentShape != NULL; currentShape = currentShape->GetNext()) {
		if (currentShape == shape) break;
		beforShape = currentShape;
	}

	if (shape_head == shape) {
		if (shape_head->GetNext() != NULL)shape_head = shape_head->GetNext();
		else {
			shape_head = NULL;
			shape_tail = NULL;
		}
	}
	if (shape_tail == shape) {
		// tailの前が無い=> shape_headと一緒の場合
		if (shape_head == shape_tail) {
			shape_head = NULL;
			shape_tail = NULL;
		}
		else shape_tail = beforShape;
	}

	if (beforShape != NULL)beforShape->SetNext(shape->GetNext());
	shape->freeShape();
	delete shape;
}

void CAdminControl::freeALLShape() {
	CShape* nowShape = shape_head;

	while (nowShape != NULL) {
		if (nowShape->GetVertexHead() == NULL)break;
		// 図形をすべて破壊する
		freeShape(nowShape);

		nowShape = shape_head;
	}
}

CShape* CAdminControl::copyShape(CShape* baseShape) {

	CShape* newShape = new CShape();

	for (CVertex* current = baseShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		newShape->SetVertexToCopy(current);
	}
	if(baseShape->GetIsClosedFlag())newShape->SetIsClosed(true);
	
	return newShape;
}

void CAdminControl::copyShapeByShape(CShape* baseShape, CShape* copyShape) {
	if (baseShape->GetVertexCount() != copyShape->GetVertexCount())return;

	CVertex* cpCurrent = copyShape->GetVertexHead();
	for (CVertex* current = baseShape->GetVertexHead(); current != NULL; current = current->GetNext()) {
		cpCurrent->SetXY(current->GetX(), current->GetY());
		cpCurrent = cpCurrent->GetNext();
	}
}
