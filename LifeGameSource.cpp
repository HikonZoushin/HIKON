//
//100x100マスのライフゲーム ver1.0
//製作者　市原拓馬
//日数　２日
//
//2017/5/17 v1.0完成

#pragma once
#include "math.h"
#include "DxLib.h"

int cell[10000]; //セル格納変数
int StepFPS = 250;//一ステップのタイム

void Screen() { //スクリーン上の描画
	DrawFormatString(610, 40, GetColor(255, 255, 255), " START");
	DrawFormatString(610, 80, GetColor(255, 255, 255), " STOP");
	DrawFormatString(610, 120, GetColor(255, 255, 255)," QUICK");
	DrawFormatString(610, 160, GetColor(255, 255, 255)," SLOW");
	DrawFormatString(610, 200, GetColor(255, 255, 255)," NEUTRAL");
	DrawFormatString(610, 240, GetColor(255, 255, 255)," RANDOM");
	DrawFormatString(610, 280, GetColor(255, 0, 0),    " RESET");
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

void Random() {//ランダム配置関数
	int random[15];//ランダム格納変数
	for (int i = 0; i < 15; i++)random[i] = GetRand(10000);//変数に10000からランダムな数を格納
	for (int i = 0; i < 10000; i++) {//セルの初期化
		cell[i] = 0; //セルを白に
		for (int j = 0; j < 20; j++) {//ランダム格納と同じ場合
			if (i == random[j]) {
				cell[i] = 1;//セルを黒に
				for (int j = 0; j < 20; j++) {//10回周囲八マスをランダムに黒に
					switch (GetRand(16))
					{
					case 0:
						cell[i + 101] = 1;
						break;
					case 1:
						cell[i - 101] = 1;
						break;
					case 2:
						cell[i + 99] = 1;
						break;
					case 3:
						cell[i - 99] = 1;
						break;
					case 4:
						cell[i + 100] = 1;
						break;
					case 5:
						cell[i - 100] = 1;
						break;
					case 6:
						cell[i + 1] = 1;
						break;
					case 7:
						cell[i - 1] = 1;
						break;
					case 8:
						cell[i + 102] = 1;
						break;
					case 9:
						cell[i - 102] = 1;
						break;
					case 10:
						cell[i + 98] = 1;
						break;
					case 11:
						cell[i - 98] = 1;
						break;
					case 12:
						cell[i + 200] = 1;
						break;
					case 13:
						cell[i - 200] = 1;
						break;
					case 14:
						cell[i + 2] = 1;
						break;
					case 15:
						cell[i - 2] = 1;
						break;
					default:
						break;
					}
				}
			}//ここまでランダム配置処理
		}
	}
	return;
}

void CellPush(){
	int MouseX = 0, MouseY = 0, Cell = 0;//マウス座標の初期化

	GetMousePoint(&MouseX, &MouseY);//マウスの座標を取得

	for (int i = 0; i < 100; i++) {//マウス座標からセルのIDを検索
		if ((MouseX >= (i * 6 + 1)) && (MouseX <= (i * 6 + 6))) {
			for (int j = 0; j < 100; j++) {
				if ((MouseY >= (j * 6 + 1)) && (MouseY <= (j * 6 + 6))) {
					Cell = i + j * 100;//IDの特定
					cell[Cell] = 1; //特定したセルを黒くする
				}
			}
		}
	}//検索終わり
	return;
}

int ScreenUpdate(int flag) {//画面操作制御

	int MouseX = 0, MouseY = 0;//マウス座標の初期化
	
	GetMousePoint(&MouseX, &MouseY);//マウスの座標を取得

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {//左クリック時の処理
		if ((MouseX > 610) && (MouseX <665) && (MouseY > 40) && (MouseY <  54) ) {//ライフゲームスタート
			flag = 1;
		}
		else if ((flag == 1)&&(MouseX > 610) && (MouseX <654) && (MouseY > 80) && (MouseY <  94)) {//一時停止

			flag = 2;
		}
		else if ((MouseX > 610) && (MouseX <665) && (MouseY > 120) && (MouseY <  134)) {//ステップ感覚を短く

			StepFPS = 100;
		}
		else if ((MouseX > 610) && (MouseX <654) && (MouseY > 160) && (MouseY <  174)) {//ステップ感覚を長く

			StepFPS = 500;
		}
		else if ((MouseX > 610) && (MouseX <687) && (MouseY > 200) && (MouseY <  214)) {//ステップ感覚を初期値に

			StepFPS = 250;
		}
		else if ((flag == 0)&&((MouseX > 610) && (MouseX <676) && (MouseY > 240) && (MouseY < 254))) {//ランダムで生存セルを配置（スタート前のみ）

			Random();
		}
		else if ((MouseX > 610) && (MouseX <665) && (MouseY > 280) && (MouseY < 294)) {//リセット

			flag = 3;
		}
		else if ((MouseX <= 606)&&(flag == 0)) {//クリック箇所に生存セルを配置（スタート前のみ）

			CellPush();
		}
	}

	return flag;
}

void CellMove() { //セル移動の処理
	int cellbuff[10000];
	int life = 0;//生死判別用
	for (int i = 0; i < 10000; i++) {
		cellbuff[i] = cell[i];
	}//マスクデータを取る

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (cellbuff[i + j * 100] == 0) {//セルが白の場合

				if (i != 0) {//左端ではない
					if ((j != 0) && (cellbuff[i + j * 100 - 101] == 1))life++;//左と上端ではない時、左上判定
					if ((j != 99) && (cellbuff[i + j * 100 + 99] == 1))life++;//左と下端ではない時、左下判定
					if (cellbuff[i + j * 100 - 1] == 1)life++;//左
				}

				if (i != 99) {//右端ではない
					if ((j != 0)&&(cellbuff[i + j * 100 - 99] == 1))life++;//右と上端ではない時、右上判定
					if ((j != 99)&&(cellbuff[i + j * 100 + 101] == 1))life++;//右と下端ではない時、右下判定
					if (cellbuff[i + j * 100 + 1] == 1)life++;//右判定
				}

				if ((j != 0) && (cellbuff[i + j * 100 - 100] == 1))life++;//上端ではない時、上判定
				if((j != 99)&&(cellbuff[i + j * 100 + 100] == 1))life++;//下端ではない時、下判定

				if (life == 3)cell[i + j * 100] = 1;//周囲八マス内３マス黒だった場合、黒にする
				life = 0;
			}
			else if (cellbuff[i + j * 100] == 1) {//セルが黒の場合
				if (i != 0) {//左端ではない
					if ((j != 0) && (cellbuff[i + j * 100 - 101] == 1))life++;//左と上端ではない時、左上判定
					if ((j != 99) && (cellbuff[i + j * 100 + 99] == 1))life++;//左と下端ではない時、左下判定
					if (cellbuff[i + j * 100 - 1] == 1)life++;//左
				}

				if (i != 99) {//右端ではない
					if ((j != 0) && (cellbuff[i + j * 100 - 99] == 1))life++;//右と上端ではない時、右上判定
					if ((j != 99) && (cellbuff[i + j * 100 + 101] == 1))life++;//右と下端ではない時、右下判定
					if (cellbuff[i + j * 100 + 1] == 1)life++;//右判定
				}

				if ((j != 0) && (cellbuff[i + j * 100 - 100] == 1))life++;//上端ではない時、上判定
				if ((j != 99) && (cellbuff[i + j * 100 + 100] == 1))life++;//下端ではない時、下判定

				if ((life == 3) || (life == 2)) {
					cell[i + j * 100] = 1;//周囲八マス内２マスか３マス黒だった場合、生存
				}
				else {
					cell[i + j * 100] = 0;//それ以外の場合白にする
				}
				life = 0;
			}
		}

	}//処理終わり

	return;
}
int Update(int flag) { //計算処理
	
	flag = ScreenUpdate(flag); //画面制御
	if (flag == 1)CellMove(); //セルの移動
	
	return flag;
}

void Draw() { //内部処理

	Screen();
	CellDraw();
	return;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(800, 600, 32), ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定と画面モードの設定
	reset:

	//初期化
	for (int i = 0; i < 10000; i++) {//セルの初期化
		cell[i] = 0; //セルを白に
	}
	int flag = 0;
	
	//初期化終わり

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		// 計算フェイズ
		flag = Update(flag);
		if (flag == 3)goto reset;

		//描画フェイズ
		Draw();

		if ((flag == 0)||(flag == 2)) {
		
		}
		else {
			Sleep(StepFPS); //処理の一時停止
		}
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}