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
};

