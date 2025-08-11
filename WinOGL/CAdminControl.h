#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region メンバ変数
public:
	bool AxisFlag; // 座標軸を描画するか
private:
	CShape* shape_head;  // 形状を管理するオブジェクト
	CShape* shape_tail;  // 形状の末尾ポインタ
	float CLOSE_DISTANCE; // どれくらいで閉じるか
	float POINTSIZE; // 頂点のサイズ
	float LINEWIDTH; // 線のサイズ
	CVertex* mouseVertex; // マウス座標
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
#pragma endregion

#pragma region その他処理

	/// <summary>
	/// 図形を閉じるかの判定を行い、閉じる必要がある場合は図形を閉じる
	/// </summary>
	void closeShape();
#pragma endregion
};

