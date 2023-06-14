#include "PerlinNoise.h"
#include <corecrt_math.h>



// 色(RGBA)を決める
int SetColor(ColorVector color, int alpha) {

	// 透明度を引数にしそれ以外はff
	color.r = 100; // R
	color.g = 100; // G
	color.b = 100; // B
	color.a = alpha; // A

	// ビット変換
	color.r <<= 24; // R
	color.g <<= 16; // G
	color.b <<= 8; // B

	// それぞれの要素を足し合わせて返す
	return color.r + color.g + color.b + color.a;
}


// ノイズ関数

float noise(Vector2 pos) {

	// (x, y)を囲む４つの格子
	Vector2 topLeft     = { float(floor(pos.x)), float(floor(pos.y)) };
	Vector2 topRight    = { float(floor(pos.x)) + 1.0f, float(floor(pos.y)) };
	Vector2 bottomLeft  = { float(floor(pos.x)), float(floor(pos.y)) + 1.0f };
	Vector2 bottomRight = { float(floor(pos.x)) + 1.0f, float(floor(pos.y)) + 1.0f };


	// 格子点の固有ベクトルを決めるためのインデックス
	// 格子点座標を(x + y) & 3にして下位2bitだけ取り出す
	int v0Index = int(topLeft.x + topLeft.y) & 3;
	int v1Index = int(topRight.x + topRight.y) & 3;
	int v2Index = int(bottomLeft.x + bottomLeft.y) & 3;
	int v3Index = int(bottomRight.x + bottomRight.y) & 3;


	// 4つの格子点と、4つの各格子点から点までのベクトルから、4つの内積を求める
	float v0 = SetVector(v0Index, { pos.x - topLeft.x, pos.y - topLeft.y });
	float v1 = SetVector(v1Index, { pos.x - topRight.x, pos.y - topRight.y });
	float v2 = SetVector(v2Index, { pos.x - bottomLeft.x, pos.y - bottomLeft.y });
	float v3 = SetVector(v3Index, { pos.x - bottomRight.x, pos.y - bottomRight.y });


	// 割合(少数部)を求めた後、さらに滑らかな補間関数を適用する
	float ratioX = smoothStep(pos.x - float(floor(pos.x)));
	float ratioY = smoothStep(pos.y - float(floor(pos.y)));


	// v4 = 左上と右上の（横）補間
	// v5 = 左下と右下の（縦）補間
	//  v = v4とv5の補間
	// 計３回の補完を行う
	float v4 = lerp(v0, v1, ratioX);
	float v5 = lerp(v2, v3, ratioX);
	float  v = lerp(v4, v5, ratioY);


	// v = -1 ~ 1 なので、1を足して0 ~ 2に、2で割って0 ~ 1の範囲に変換する
	//return (v + 1.0f) / 2.0f; // 0 ~ 1
	return v + 1.0f; // 0 ~ 2
	//return v; // -1 ~ 1
}



// index = 格子点座標を(x + y) & 3にして下位2bitだけ取り出したもの
// x, y = 格子点から点までのベクトル
float SetVector(int index, Vector2 v) {

	if (index == 0) {
		return -v.x - v.y;
	}
	else if (index == 1) {
		return -v.x + v.y;
	}
	else if (index == 2) {
		return v.x - v.y;
	}
	else {
		return v.x + v.y;
	}
}



// 0～1の間で滑らかなエルミート補間を返す

float smoothStep(float x) {
	return x * x * x * (x * (x * 6 - 15) + 10);
}



// 線形補間
float lerp(float start, float end, float t) {
	return (1 - t) * start + t * end;
}



// 減算
Vector2 Subtract(Vector2 a, Vector2 b) {
	Vector2 result{};
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return result;
}



// 除算
Vector2 Divide(Vector2 a, float seed) {
	Vector2 result{};
	result.x = a.x / seed;
	result.y = a.y / seed;

	return result;
}

