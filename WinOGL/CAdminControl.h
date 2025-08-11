#pragma once
#include "CVertex.h"
#include "CShape.h"
#include "CMath.h"
class CAdminControl{
#pragma region メンバ変数
public:
	CShape* shape_head;  // 形状を管理するオブジェクト
	CShape* shape_tail;  // 形状の末尾ポインタ
private:

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
#pragma endregion

#pragma region Set系/Get系

	/// <summary>
	/// マウス座標を使用して頂点を設定
	/// </summary>
	/// <param name="mouse_x">マウスのX座標</param>
	/// <param name="mouse_y">マウスのY座標</param>
	void SetVertex(float mouse_x, float mouse_y);

#pragma endregion

#pragma region 判定

	/// <summary>
	/// 図形同士が交差(他交差)しているか判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>他交差している場合はtrue、していない場合はfalse</returns>
	bool isShapeCross(CVertex* newVertex);
#pragma endregion

#pragma region その他処理

	/// <summary>
	/// 図形を閉じるかの判定を行い、閉じる必要がある場合は図形を閉じる
	/// </summary>
	void closeShape();
#pragma endregion
};

