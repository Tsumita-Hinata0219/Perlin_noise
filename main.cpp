#include <Novice.h>
#include "Vector2.h"
#include "PerlinNoise.h"
#include "ImGuiManager.h"

const char kWindowTitle[] = "LE2B_20_ツミタ_ヒナタ_";




struct Rect {
	Vector2 pos;
	Vector2 size;
	float angle;
	float alpha;
	unsigned int color;
};
// 色コードの構造体
ColorVector colorV{};


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int ScreenWidth  = 500;
	const int ScreenHeight = 500;
	Novice::Initialize(kWindowTitle, ScreenWidth, ScreenHeight);


	const int maxRectX = 100;
	const int maxRectY = 100;

	// noise()用矩形
	Rect Rect1[maxRectX][maxRectY]{};

	for (int y = 0; y < maxRectY; y++) {
		for (int x = 0; x < maxRectX; x++) {
			Rect1[y][x].pos.x = float(x * 5);
			Rect1[y][x].pos.y = float(y * 5);
			Rect1[y][x].size = { 5.0f, 5.0f };
			Rect1[y][x].angle = 0.0f;
			
			// 透明度をnoise()関数で求める
			Rect1[y][x].alpha = noise(Divide(Rect1[y][x].pos, 180.0f));
			// noise()求めた透明度でcolorを決める
			Rect1[y][x].color = SetColor(colorV, int(Rect1[y][x].alpha * 150));
		}
	}
	


	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(
			0, 0,
			ScreenWidth, ScreenHeight,
			0.0f, BLACK, kFillModeSolid);

	/*	Novice::DrawBox(
			10, 10,
			100, 100,
			0.0f, color, kFillModeSolid);*/


		for (int y = 0; y < maxRectY; y++) {
			for (int x = 0; x < maxRectX; x++)
			{
				Novice::DrawBox(
					int(Rect1[y][x].pos.x), int(Rect1[y][x].pos.y),
					int(Rect1[y][x].size.x), int(Rect1[y][x].size.y),
					0.0f, Rect1[y][x].color, kFillModeSolid);
			}
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

