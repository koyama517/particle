﻿#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
const char kWindowTitle[] = "LC1A_09_コヤマタクミ";

typedef struct Vector2 {
	float x;
	float y;
};
//
//typedef struct Sword {
//	Vector2 Start;
//	Vector2 End;
//	Vector2 PreEnd;
//	Vector2 speed;
//};
typedef struct Particle {
	Vector2 position;
	int isActive;
	unsigned int carentAlpha;
};

typedef struct player {
	Vector2 pos;
	float speed;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*float thata = 1.0f / 128.0f * M_PI;

	Sword sword
	{
		{400,400},
		{128,128},
		{0,0},
	};*/

	player player{
		{700,400},
		5,
	};

	const int max = 60;

	/*Particle particle[max];
	for (int i = 0; i < max; i++)
	{
		particle[i].isActive = false;
		particle[i].position = sword.End;
		particle[i].carentAlpha = 0x56;
	}*/

	Particle trajectory[max];

	for (int i = 0; i < max; i++)
	{
		trajectory[i].isActive = false;
		trajectory[i].position.x = player.pos.x;
		trajectory[i].position.y = player.pos.y;
		trajectory[i].carentAlpha = 0x56;
	};

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

		/*sword.PreEnd = sword.End;

		sword.End.x = (sword.PreEnd.x * cos(thata) - sword.PreEnd.y * sin(thata));
		sword.End.y = (sword.PreEnd.x * sin(thata) + sword.PreEnd.y * cos(thata));

		for (int i = 0; i < max; i++)
		{
			if (!particle[i].isActive)
			{
				particle[i].position.x = sword.Start.x + sword.End.x;
				particle[i].position.y = sword.Start.y + sword.End.y;
				particle[i].isActive = true;
				particle[i].carentAlpha = 0x56;
				break;
			}
			else
			{
				particle[i].carentAlpha -= 0x02;
				if (particle[i].carentAlpha == 0x00)
				{
					particle[i].isActive = false;
				}
			}
		}*/

		for (int i = 0; i < max; i++)
		{
			if (!trajectory[i].isActive)
			{
				trajectory[i].isActive = true;
				trajectory[i].position.x = player.pos.x;
				trajectory[i].position.y = player.pos.y;
				trajectory[i].carentAlpha = 0x22;
				break;
			}
			else
			{
				trajectory[i].carentAlpha -= 0x02;
				if (trajectory[i].carentAlpha == 0x00)
				{
					trajectory[i].isActive = false;
				}
			}
		}

		if (keys[DIK_UP] || keys[DIK_W]) {
			player.pos.y -= player.speed;
		}

		if (keys[DIK_LEFT] || keys[DIK_A]) {

			player.pos.x -= player.speed;

		}

		if (keys[DIK_DOWN] || keys[DIK_S]) {

			player.pos.y += player.speed;

		}

		if (keys[DIK_LEFT] || keys[DIK_D]) {

			player.pos.x += player.speed;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(player.pos.x, player.pos.y,
			30, 30, 0.0f, WHITE, kFillModeSolid);

		for (int i = 0; i < max; i++)
		{
			if (trajectory[i].isActive)
			{
				Novice::DrawBox(trajectory[i].position.x, trajectory[i].position.y, 30, 30, 0.0f, 0xFFFFFF00 + trajectory[i].carentAlpha, kFillModeSolid);
			}
		}

		/*for (int i = 0; i < max; i++)
		{
			if (particle[i].isActive)
			{
				Novice::DrawTriangle(particle[i].position.x, particle[i].position.y,
					sword.Start.x, sword.Start.x, sword.Start.x + sword.PreEnd.x, sword.Start.y + sword.PreEnd.y,
					0xFFFFFF00 + particle[i].carentAlpha, kFillModeSolid);
			}
		}*/

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
