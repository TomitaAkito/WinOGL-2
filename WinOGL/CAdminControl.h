#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region メンバ変数
public:
	bool AxisFlag; // 座標軸を描画するか
	bool EditFlag; // 編集モードにするか
	bool LButtonDownFlag; // 左クリックが押下されているか
private:
	CShape* shape_head;  // 形状を管理するオブジェクト
	CShape* shape_tail;  // 形状の末尾ポインタ
	float CLOSE_DISTANCE; // どれくらいで閉じるか
	float POINTSIZE; // 頂点のサイズ
	float LINEWIDTH; // 線のサイズ
	CVertex* MoveMouseVertex; // マウス座標
	CVertex* selectVertexPointer; // 選択された頂点
	CVertex* selectLinePointer; // 選択された稜線の始点
	CShape* selectShapePointer; // 選択された図形
	bool selectVertexFlag; // 頂点を選択しているか
	bool selectLineFlag; // 稜線を選択しているか
	bool selectShapeFlag; // 図形を選択しているか
#pragma endregion

public:
#pragma region コンストラクタ・デストラクタ
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CAdminControl();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CAdminControl();

#pragma endregion

#pragma region 描画系
	/// <summary>
	/// 描画処理を実行
	/// </summary>
	void Draw();

	/// <summary>
	/// 頂点を描画
	/// </summary>
	void DrawVertex();

	/// <summary>
	/// 線を描画
	/// </summary>
	void DrawLine();

	/// <summary>
	/// 点と線のサイズ変更
	/// </summary>
	void DrawSizeChangeUP();

	/// <summary>
	/// 点と線のサイズ変更
	/// </summary>
	void DrawSizeChangeDOWN();

	/// <summary>
	/// 座標軸の描画
	/// </summary>
	void DrawAxis();

	/// <summary>
	/// 予測線の描画
	/// </summary>
	void DrawPredictLine();

	/// <summary>
	/// 選択結果を描画する
	/// </summary>
	void DrawEdit();

	/// <summary>
	/// 引数の頂点の色を変更して描画
	/// </summary>
	/// <param name="vertex">頂点</param>
	void DrawSelectVertex(CVertex* vertex);

	/// <summary>
	/// 引数の稜線の色を変更して描画
	/// </summary>
	/// <param name="lineStart">稜線の始点</param>
	/// <param name="lineEnd">稜線の終点</param>
	void DrawSelectLine(CVertex* lineStart,CVertex* lineEnd);

	/// <summary>
	/// 引数の図形の色を変更して描画
	/// </summary>
	/// <param name="shape">図形</param>
	void DrawSelectShape(CShape* shape);
#pragma endregion

#pragma region Set系/Get系

	/// <summary>
	/// マウス座標を使用して頂点を設定
	/// </summary>
	/// <param name="mouse_x">マウスのX座標</param>
	/// <param name="mouse_y">マウスのY座標</param>
	void SetVertex(float mouse_x, float mouse_y);

	/// <summary>
	/// マウス座標を設定
	/// </summary>
	/// <param name="mouse_x">マウスのX座標</param>
	/// <param name="mouse_y">マウスのY座標</param>
	void SetMouseVertex(float mouse_x, float mouse_y);

#pragma endregion

#pragma region 判定

	/// <summary>
	/// 図形同士が交差(他交差)しているか判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>他交差している場合はtrue、していない場合はfalse</returns>
	bool isShapeCross(CVertex* newVertex);

	/// <summary>
	/// 頂点・図形が内包しているか判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>内包する場合はtrue、しない場合はfalse</returns>
	bool isConnotation(CVertex* newVertex);

	/// <summary>
	/// 頂点が内包しているか判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>内包する場合はtrue、しない場合はfalse</returns>
	bool isConnotationVertex(CVertex* newVertex);

	/// <summary>
	/// 図形が内包しているか判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>内包する場合はtrue、しない場合はfalse</returns>
	bool isConnotationShape(CVertex* newVertex);

	/// <summary>
	/// 頂点を動かした際に内包するか判定
	/// </summary>
	/// <param name="vertex">移動している頂点</param>
	/// <returns>内包する場合はtrue、しない場合はfalse</returns>
	bool isConnotationMoveVertex(CVertex* vertex);

	/// <summary>
	/// 削除した際に内包するか判定
	/// </summary>
	/// <param name="vertex">消す頂点</param>
	/// <param name="shape">削除対象の図形</param>
	/// <returns>内包する場合はtrue、しない場合はfalse</returns>
	bool isConnotationFreeVertex(CVertex* vertex, CShape* shape);
#pragma endregion

#pragma region 編集
	
	/// <summary>
	/// 編集モードを司る関数
	/// </summary>
	/// <param name="mouse_x">マウスのX座標</param>
	/// <param name="mouse_y">マウスのY座標</param>
	void Edit(float mouse_x, float mouse_y);

	/// <summary>
	/// 点の選択
	/// </summary>
	/// <param name="LMouseVertex">マウス座標</param>
	/// <returns>選択できた場合はtrue、できなかった場合はfalse</returns>
	bool selectVertex(CVertex* LMouseVertex);

	/// <summary>
	/// 線の選択
	/// </summary>
	/// <param name="LMouseVertex">マウス座標</param>
	/// <returns>選択できた場合はtrue、できなかった場合はfalse</returns>
	bool selectLine(CVertex* LMouseVertex);

	/// <summary>
	/// 図形の選択
	/// </summary>
	/// <param name="LMouseVertex">マウス座標</param>
	/// <returns>選択できた場合はtrue、できなかった場合はfalse</returns>
	bool selectShape(CVertex* LMouseVertex);

	/// <summary>
	/// 移動系を司る関数
	/// </summary>
	void moveByMouse();

	/// <summary>
	/// 頂点を移動
	/// </summary>
	/// <param name="mouseVertex">マウス座標</param>
	void moveVertex(CVertex* mouseVertex);

	/// <summary>
	/// 点の挿入
	/// </summary>
	/// <param name="mouseVertex">マウス座標</param>
	void insertVertex(CVertex* mouseVertex);

	/// <summary>
	/// 選択された頂点を削除
	/// </summary>
	void deleteVertex();
#pragma endregion

#pragma region その他処理

	/// <summary>
	/// 図形を閉じるかの判定を行い、閉じる必要がある場合は図形を閉じる
	/// </summary>
	void closeShape();

	/// <summary>
	/// 頂点から図形を探索して返す
	/// </summary>
	/// <param name="vertex">頂点</param>
	/// <returns>図形</returns>
	CShape* serchShapeByVertex(CVertex* vertex);

	/// <summary>
	/// 図形の削除
	/// </summary>
	void freeShape(CShape* shape);

	/// <summary>
	/// すべての図形を削除
	/// </summary>
	void freeALLShape();
#pragma endregion
};

