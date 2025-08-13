#pragma once
#include <math.h>
#include "CVertex.h"
#include "CVector.h"
#include "CShape.h"

class CMath{
public:
	/// <summary>
	/// 2点間の距離を計算
	/// </summary>
	/// <param name="vertex1">頂点1のX座標</param>
	/// <param name="vertex2">頂点2のY座標</param>
	/// <returns>2点間の距離</returns>
	float calcDistance(CVertex* vertex1, CVertex* vertex2);

	/// <summary>
	/// ベクトルの外積を計算
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	/// <returns>外積の結果</returns>
	float calcCrossProduct(CVector* a, CVector* b);

	/// <summary>
	/// ベクトルの内積を計算
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	/// <returns>内積の結果</returns>
	float calcInnerProduct(CVector* a, CVector* b);

	/// <summary>
	/// 座標が一致しているか確認
	/// </summary>
	/// <param name="a">頂点 a</param>
	/// <param name="b">頂点 b</param>
	/// <returns>一致している場合はtrue、していない場合はfalse</returns>
	bool isXYZ(CVertex* a, CVertex* b);

	/// <summary>
	/// 2つの線分の成す角度を計算
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	/// <returns>角度</returns>
	float calcAngle(CVector* a, CVector* b);

	/// <summary>
	/// 該当図形と頂点のなす角を算出
	/// </summary>
	/// <param name="currentShape">図形</param>
	/// <param name="vertex">頂点</param>
	/// <returns>角度</returns>
	float calcAngleByShape(CShape* currentShape, CVertex* vertex);

	/// <summary>
	/// float型の数字の絶対値を返す
	/// </summary>
	/// <param name="value">float型の数字</param>
	/// <returns>絶対値の数字</returns>
	float absFloat(float value);

	/// <summary>
	/// 線と点の距離を算出する
	/// </summary>
	/// <param name="lineStart">線の始点</param>
	/// <param name="lineEnd">線の終点</param>
	/// <param name="vertex">点</param>
	/// <returns>距離</returns>
	float calcPointLineDistance(CVertex* lineStart, CVertex* lineEnd, CVertex* vertex);

	/// <summary>
	/// ベクトルからsinθを算出
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <param name="b">ベクトル b</param>
	/// <returns>sinθ</returns>
	float calcSinTheta(CVector* a, CVector* b);
	
	/// <summary>
	/// ベクトルの大きさを算出
	/// </summary>
	/// <param name="a">ベクトル a</param>
	/// <returns>ベクトルの大きさ</returns>
	float calcVectorDistance(CVector* a);

	/// <summary>
	/// 引数の頂点から移動量を算出して配列に格納
	/// </summary>
	/// <param name="beforVertex">元の頂点</param>
	/// <param name="afterVertex">移動先の頂点</param>
	/// <param name="result">結果を格納(シリアライズ・デシリアライズは呼び出し元で行う)</param>
	void calcMovementByVertex(CVertex* beforVertex, CVertex* afterVertex, float(&result)[2]);
};

