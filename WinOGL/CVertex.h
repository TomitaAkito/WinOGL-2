#include "pch.h"
#pragma once

class CVertex{
#pragma region メンバ変数
private:
	float x;  // X座標
	float y;  // Y座標
	float z;  // Z座標
	CVertex* next; // 次の頂点へのポインタ
	CVertex* pre; // 前の頂点へのポインタ

#pragma endregion

#pragma region コンストラクタ・デストラクタ
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CVertex();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CVertex();
#pragma endregion

#pragma region Set系/Get系
	/// <summary>
	/// X座標を取得
	/// </summary>
	/// <returns>X座標</returns>
	float GetX();
		
	/// <summary>
	/// Y座標を取得
	/// </summary>
	/// <returns>Y座標</returns>
	float GetY();
		
	/// <summary>
	/// Z座標を取得
	/// </summary>
	/// <returns>Z座標</returns>
	float GetZ();

	/// <summary>
	/// X座標・Y座標を設定
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void SetXY(float x, float y);

	/// <summary>
	///	次の頂点アドレスを取得
	/// </summary>
	/// <returns>アドレス</returns>
	CVertex* GetNext();

	/// <summary>
	/// 直前のポインタを取得
	/// </summary>
	/// <returns>直前のポインタ</returns>
	CVertex* GetPre();

	/// <summary>
	/// X座標を設定
	/// </summary>
	/// <param name="x">X座標</param>
	void SetX(float x);

	/// <summary>
	/// Y座標を設定
	/// </summary>
	/// <param name="x">Y座標</param>
	void SetY(float y);

	/// <summary>
	/// Z座標を設定
	/// </summary>
	/// <param name="x">Z座標</param>
	void SetZ(float z);

	/// <summary>
	/// 次の頂点アドレスを設定
	/// </summary>
	/// <param name="x">次の頂点アドレス</param>
	void SetNext(CVertex* nextPointer);

	/// <summary>
	/// 直前のポインタを設定
	/// </summary>
	/// <param name="x">直前のポインタ</param>
	void SetPre(CVertex* prePointer);

	/// <summary>
	/// Vertexの座標を設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetVertex(float x, float y);
#pragma endregion


};

