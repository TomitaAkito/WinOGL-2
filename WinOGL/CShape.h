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
	/// 通常の頂点追加方法
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	void NormalAddVertex(CVertex* newVertex);

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
	/// 頂点数を設定
	/// </summary>
	/// <param name="num">頂点数</param>
	void SetVertexCount(int num);

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

#pragma region 判定系

	/// <summary>
	/// 描画できるかを判定
	/// </summary>
	/// <param name="MoveMouseVertex">マウス座標</param>
	/// <returns>設置できる場合はtrue、できない場合はfalse</returns>
	bool isDrawPredict(CVertex* MoveMouseVertex);

	/// <summary>
	/// 自交差を判定
	/// </summary>
	/// <param name="newVertex">新しい頂点</param>
	/// <returns>自交差している場合はtrue、していない場合はfalse</returns>
	bool isSelfCrossed(CVertex* newVertex);

	/// <summary>
	/// 砂時計のように始点と終点を配置した場合に自交差しないか判定
	/// </summary>
	/// <returns>自交差している場合はtrue、していない場合はfalse</returns>
	bool isSelfCrossedByHourGlassType();

	/// <summary>
	/// 二つの線分が交差しているか判定
	/// </summary>
	/// <param name="As">線分Aの開始地点</param>
	/// <param name="Ae">線分Aの終了地点</param>
	/// <param name="Bs">線分Bの開始地点</param>
	/// <param name="Be">線分Bの終了地点</param>
	/// <returns></returns>
	bool isSelfCrossedBy2Lines(CVertex* As, CVertex* Ae, CVertex* Bs, CVertex* Be);

	/// <summary>
	/// 図形が自交差・他交差していないか判定
	/// </summary>
	/// <param name="selectVertex">選択中の頂点</param>
	/// <param name="nextVertex">選択中の頂点の次の頂点</param>
	/// <param name="shape_head">図形リストの頭</param>
	/// <returns>交差していたらtrue、していなければfalse</returns>
	bool isMoveVertexSelfCross(CVertex* selectVertex, CVertex* nextVertex, CShape* shape_head);


#pragma endregion

#pragma region その他のメソッド

	/// <summary>
	/// 図形を解放
	/// </summary>
	void freeShape();

	/// <summary>
	/// 座標が一致する頂点を削除
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void freeVertex(float x,float y);

	/// <summary>
	/// vertex_tailを削除
	/// </summary>
	void freeVertexTail();

	/// <summary>
	/// 前の頂点の次に頂点を挿入
	/// </summary>
	/// <param name="preVertex">前の頂点</param>
	/// <param name="newVertex">新しく挿入する頂点</param>
	void insertVertex(CVertex* preVertex,CVertex* newVertex);
#pragma endregion
};

