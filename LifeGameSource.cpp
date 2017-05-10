#pragma once
#include "math.h"
#include "DxLib.h"

int cell[10000]; //セル格納変数

void Screen() { //スクリーン上の描画
	
	return;
}

void CellDraw() {	//セルの描画
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (cell[i + j * 100] == 0) {
				DrawBox(i * 6 + 1, j * 6 + 1, i * 6 + 6, j * 6 + 6, GetColor(255, 255, 255), TRUE); //白色を指定
			}
			else if (cell[i + j * 100] == 1) {
				DrawBox(i * 6 + 1, j * 6 + 1, i * 6 + 6, j * 6 + 6, GetColor(0, 0, 0), TRUE); //黒色を指定
			}
		}
	}
	return;
}

void CellMove() { //セル移動の処理
	int cellbuff[10000];
	int cellbuff2[10000];
	for (int i = 0; i < 10000; i++) {
		cellbuff[i] = cell[i];
		cellbuff2[i] = cell[i];
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (cellbuff[i + j * 100] == 0) {
			}
			else if (cellbuff[i + j * 100] == 1) {

				if (i != 99) {
					if (j != 99) {
						if (cell[i + j * 100 + 101] == 0) {
							cell[i + j * 100 + 101] = 1;
						}
						else {
							cell[i + j * 100 + 101] = 0;
						}
					}
					if (j != 0) {
						if (cell[i + j * 100 - 99] == 0) {
							cell[i + j * 100 - 99] = 1;
						}
						else {
							cell[i + j * 100 - 99] = 0;
						}
					}
					if (cell[i + j * 100 + 1] == 0) {
						cell[i + j * 100 + 1] = 1;
					}
					else {
						cell[i + j * 100 + 1] = 0;
					}
				}

				if (i != 0) {
					if (j != 0) {
						if (cell[i + j * 100 - 101] == 0) {
							cell[i + j * 100 - 101] = 1;
						}
						else {
							cell[i + j * 100 - 101] = 0;
						}
					}
					if (j != 99) {
						if (cell[i + j * 100 + 99] == 0) {
							cell[i + j * 100 + 99] = 1;
						}
						else {
							cell[i + j * 100 + 99] = 0;
						}
					}

					if (cell[i + j * 100 - 1] == 0) {
						cell[i + j * 100 - 1] = 1;
					}
					else {
						cell[i + j * 100 - 1] = 0;
					}
				}

				if (j != 99) {
					if (cell[i + j * 100 + 100] == 0) {
						cell[i + j * 100 + 100] = 1;
					}
					else {
						cell[i + j * 100 + 100] = 0;
					}
				}

				if (j != 0) {
					if (cell[i + j * 100 - 100] == 0) {
						cell[i + j * 100 - 100] = 1;
					}
					else {
						cell[i + j * 100 - 100] = 0;
					}
				}
				cellbuff2[i + j * 100] = 0;
			}
		}
	}//移動の処理

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (cellbuff[i + j * 100] != cellbuff2[i + j * 100]) {
				cell[i + j * 100] = 0;
			}
		}
	}//死の処理

	return;
}

void Update() { //計算処理

	CellMove(); //セルの移動
	
	return;
}

void Draw() { //内部処理

	Screen();
	CellDraw();
	return;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(800, 600, 32), ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定と画面モードの設定

	//初期化
	int random[20];
	for (int i = 0; i < 20; i++)random[i] = GetRand(10000);
	for (int i = 0; i < 10000; i++) {
		cell[i] = 0; //セルの初期化
		for (int j = 0; j < 20; j++) {
			if (i == random[j])cell[i] = 1;
		}
	}

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		// 計算フェイズ
		Update();

		//描画フェイズ
		Draw();

		Sleep(500); //処理の一時停止
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}