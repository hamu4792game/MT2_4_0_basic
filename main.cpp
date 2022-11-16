﻿#include <Novice.h>
#include "Matrix.h"

const char* kWindowTitle = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	int kWindowWidth = 1280, kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float theta = 0.0f;

	struct Object
	{
		Vec2 centerPos;
		Vec2 size;
		Vec2 LT;
		Vec2 RT;
		Vec2 LB;
		Vec2 RB;
		Vec2 speed;
	};
	Object object{
		{400.0f,100.0f},
		{200.0f,100.0f},
		{object.size.x / -2.0f,object.size.y / 2.0f},
		{object.size.x / 2.0f,object.size.y / 2.0f},
		{object.size.x / -2.0f,object.size.y / -2.0f},
		{object.size.x / 2.0f,object.size.y / -2.0f},
		{10.0f,10.0f},
	};

	int block = Novice::LoadTexture("white1x1.png");

	//	行列の作成
	Matrix3x3 rotateMatrix;
	Matrix3x3 translateMatrix;

	Matrix3x3 worldMatrix;


	Vec2 worldLeftTop;
	Vec2 worldRightTop;
	Vec2 worldLeftBottom;
	Vec2 worldRightBottom;

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

		//	回転
		theta += 2.0f;
		if (theta > 360.0f)
		{
			theta = 0.0f;
		}


		//	行列の作成
		rotateMatrix = MakeRotateMatrix(theta);
		translateMatrix = MakeTranslateMatrix(object.centerPos);

		worldMatrix = Multiply(translateMatrix, rotateMatrix);

		//
		worldLeftTop = Transform(object.LT, worldMatrix);
		worldRightTop = Transform(object.RT, worldMatrix);
		worldLeftBottom = Transform(object.LB, worldMatrix);
		worldRightBottom = Transform(object.RB, worldMatrix);



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vec2 screenLeftTop = Change(worldLeftTop);
		Vec2 screenRightTop = Change(worldRightTop);
		Vec2 screenLeftBottom = Change(worldLeftBottom);
		Vec2 screenRightBottom = Change(worldRightBottom);


		Novice::DrawQuad((int)screenLeftTop.x, (int)screenLeftTop.y,
			(int)screenRightTop.x, (int)screenRightTop.y,
			(int)screenLeftBottom.x, (int)screenLeftBottom.y,
			(int)screenRightBottom.x, (int)screenRightBottom.y,
			0, 0, 1, 1, block, 0xffffffff);

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