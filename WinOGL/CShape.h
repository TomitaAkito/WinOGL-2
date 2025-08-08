#include "pch.h"
#include "CVertex.h"
#pragma once
class CShape{
#pragma region メンバ変数
private:
	CVertex* vertex_head;  // 頂点の先頭ポインタ
	CVertex* vertex_tail;  // 頂点の末尾ポインタ
	CShape* next;  // 次の形状へのポインタ
	bool isClosedFlag; // 閉じた図形かどうか
	int vertexCount; // 頂点の数
#pragma endregion

#pragma region コンストラクタ・デストラクタ
	public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CShape();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CShape();

#pragma endregion

#pragma region Set系/Get系
	/// <summary>
	/// 頂点の先頭ポインタを取得
	/// </summary>
	/// <returns>頂点の先頭ポインタ</returns>
	CVertex* GetVertexHead();

	/// <summary>
	/// 頂点の末尾ポインタを取得
	/// </summary>
	/// <returns>頂点の末尾ポインタ</returns>
	CVertex* GetVertexTail();

	/// <summary>
	/// Vertexの座標を設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetVertex(float x,float y);

	/// <summary>
	/// Vertexの座標を設定
	/// </summary>
	/// <param name="newVertex">新しいvertex</param>
	void SetVertexByPointer(CVertex* newVertex);

	/// <summary>
	/// 次のポインタを取得
	/// </summary>
	/// <returns>次のポインタ</returns>
	CShape* GetNext();

	/// <summary>
	/// 次の図形を設定
	/// </summary>
	/// <param name="nextShape">設定する次の CShape オブジェクトへのポインタ</param>
	void SetNext(CShape* nextShape);

	/// <summary>
	/// 頂点数を取得
	/// </summary>
	/// <returns>頂点数</returns>
	int GetVertexCount();

	/// <summary>
	/// オブジェクトが閉じているかどうかを設定
	/// </summary>
	/// <param name="isClosedFlag">オブジェクトが閉じている場合は true、開いている場合は false を指定</param>
	void SetIsClosed(bool isClosedFlag);

	/// <summary>
	/// オブジェクトが閉じているかどうかを取得
	/// </summary>
	/// <returns>オブジェクトが閉じている場合は true、開いている場合は false</returns>
	bool GetIsClosedFlag();
#pragma endregion
};

