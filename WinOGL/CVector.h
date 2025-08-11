#pragma once
#include "CVertex.h"
class CVector{

#pragma region メンバ変数
private:
	float x; // X成分
	float y; // Y成分
#pragma endregion

#pragma region コンストラクタ・デストラクタ
public:
	// デフォルトコンストラクタ
	CVector();
	// コンストラクタ（引数あり）
	CVector(float x, float y);
	// コンストラクタ（頂点型）
	CVector(CVertex* a, CVertex* b);
	// デストラクタ
	~CVector();
#pragma endregion

#pragma region Set系/Get系
public:

	/// <summary>
	/// X成分を設定
	/// </summary>
	/// <param name="x">X成分</param>
	void SetX(float x);

	/// <summary>
	/// X成分を取得
	/// </summary>
	/// <returns>X成分</returns>
	float GetX();

	/// <summary>
	/// Y成分を設定
	/// </summary>
	/// <param name="y">Y成分</param>
	void SetY(float y);

	/// <summary>
	/// Y成分を取得
	/// </summary>
	/// <returns>Y成分</returns>
	float GetY();

	/// <summary>
	/// 頂点からベクトルを算出して格納
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	void SetByVertex(CVertex* a,CVertex* b);
};

