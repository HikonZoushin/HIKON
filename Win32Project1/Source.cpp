#include "DxLib.h"

void Board() {//盤面の描画
	int Cr = GetColor(0, 0, 0);//黒色を指定
	DrawBox(112, 12, 688, 588, GetColor(0, 200, 0), TRUE);//緑の盤を描画
	for (int i = 0; i < 8; i++) {//縦横八等分する線を引く
		DrawLine((i * 8) * 9 + 112, 12, (i * 8) * 9 + 112, 588, Cr);
		DrawLine(112, (i * 8) * 9 + 12, 688, (i * 8) * 9 + 12, Cr);
	}
	for (int i = 0; i < 2; i++) {//黒丸を四方に置く
		DrawOval(256, (i * 32) * 9 + 156, 5, 5, Cr, TRUE);
		DrawOval(544, (i * 32) * 9 + 156, 5, 5, Cr, TRUE);
	}
	return;
}

void Stone(int slot[64]) {//石の描画
	int Cr1 = GetColor(255, 255, 255);//白を指定
	int Cr2 = GetColor(0, 0, 0);//黒を指定
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (slot[(i + j * 8)] == 1) {//白配置
				DrawOval((i * 8) * 9 + 148, (j * 8) * 9 + 48, 30, 30, Cr1, TRUE);
			}
			else if (slot[i + j * 8] == 2) {//黒配置
				DrawOval((i * 8) * 9 + 148, (j * 8) * 9 + 48, 30, 30, Cr2, TRUE);
			}
		}
	}
}

int* Decision(int slot[64],int slotP, int Color){//判定の処理、Colorの値は1：白、2：黒
	int flag = 0;//判定が有効だったかのフラグ
	
				 //左上の判定
	if ((slotP > 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP != 57)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP - 9] == 2) || (Color == 2) && (slot[slotP - 9] == 1)) {//左上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (9 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP - (9 * i)] == 2) || (Color == 2) && (slot[slotP - (9 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - (9 * i)] == 1) || (Color == 2) && (slot[slotP - (9 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 9 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 9 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//左上ここまで

				//上の判定
	if ((slotP > 16)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP - 8] == 2) || (Color == 2) && (slot[slotP - 8] == 1)) {//上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (8 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP - (8 * i)] == 2) || (Color == 2) && (slot[slotP - (8 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - (8 * i)] == 1) || (Color == 2) && (slot[slotP - (8 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 8 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 8 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//上ここまで

				//右上の判定
	if ((slotP > 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP - 7] == 2) || (Color == 2) && (slot[slotP - 7] == 1)) {//右上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (7 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP - (7 * i)] == 2) || (Color == 2) && (slot[slotP - (7 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - (7 * i)] == 1) || (Color == 2) && (slot[slotP - (7 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 7 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 7 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//右上ここまで

				//左の判定
	if ((slotP != 0) && (slotP != 8) && (slotP != 16) && (slotP != 24) && (slotP != 32) && (slotP != 40) && (slotP != 48) && (slotP != 56)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP - 1] == 2) || (Color == 2) && (slot[slotP - 1] == 1)) {//左に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if ((slotP - i) < 0)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP - i] == 2) || (Color == 2) && (slot[slotP - i] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - i] == 1) || (Color == 2) && (slot[slotP - i] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//左ここまで

				//右の判定
	if ((slotP != 7) && (slotP != 15) && (slotP != 23) && (slotP != 31) && (slotP != 39) && (slotP != 47) && (slotP != 55) && (slotP != 63)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP + 1] == 2) || (Color == 2) && (slot[slotP + 1] == 1)) {//右に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if ((slotP + i) > 63)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP + i] == 2) || (Color == 2) && (slot[slotP + i] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + i] == 1) || (Color == 2) && (slot[slotP + i] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//右ここまで

				//右下の判定
	if ((slotP < 46) && (slotP != 38) && (slotP != 39) && (slotP != 30) && (slotP != 31) && (slotP != 22) && (slotP != 23) && (slotP != 14) && (slotP != 15) && (slotP != 6) && (slotP != 7)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP + 9] == 2) || (Color == 2) && (slot[slotP + 9] == 1)) {//右下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (9 * i) > 63)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP + (9 * i)] == 2) || (Color == 2) && (slot[slotP + (9 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (9 * i)] == 1) || (Color == 2) && (slot[slotP + (9 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 9 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 9 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//右下ここまで

				//下の判定
	if ((slotP < 56)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP + 8] == 2) || (Color == 2) && (slot[slotP + 8] == 1)) {//下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (8 + i) > 63)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP + (8 * i)] == 2) || (Color == 2) && (slot[slotP + (8 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (8 * i)] == 1) || (Color == 2) && (slot[slotP + (8 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 8 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 8 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//下ここまで

				//左下の判定
	if ((slotP < 48) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 0)) {//処理を行えないIDを除外
		if ((Color == 1) && (slot[slotP + 7] == 2) || (Color == 2) && (slot[slotP + 7] == 1)) {//左下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (7 * i) > 63)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP + (7 * i)] == 2) || (Color == 2) && (slot[slotP + (7 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (7 * i)] == 1) || (Color == 2) && (slot[slotP + (7 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 7 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 7 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
			}
		}
	}			//左下ここまで

	if ((flag == 1) && (Color == 1))slot[slotP] = 1;//指定地点に白石
	if ((flag == 1) && (Color == 2))slot[slotP] = 2;//指定地点に黒石
	
	for (int i = 0; i < 64; i++) {//クリア判定
		if (slot[i] == 0)flag = 0;
	}
	if (flag == 1);
	return slot;
	}

int* Player(int slot[64],int Color) {//左クリック時の処理
	Color++;
	int MouseX, MouseY, slotP = 0;
	GetMousePoint(&MouseX,&MouseY);//マウスの座標を取得
	if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
		for (int i = 0; i < 8; i++) {//マウス座標から石のIDを検索
			if ((MouseX > (i * 8) * 9 + 112) && (MouseX < ((i + 1) * 8) * 9 + 112)) {
				for (int j = 0; j < 8; j++) {
					if ((MouseY > (j * 8) * 9 + 12) && (MouseY < ((j + 1) * 8) * 9 + 12)) {
						slotP = i + j * 8;//IDの特定
						DrawFormatString(0, 0, GetColor(255,255,255), "ID %d  ", slotP);
					}
				}
			}
		}//検索終わり
		if (slot[slotP] == 0){
			for (int i = 0; i < 64; i++) {
				slot[i] = Decision(slot,slotP, Color)[i];//実判定
			}
		}
	}
	return slot;
}

int* NPC(int slot[64], int difficult) {
	int slotM[64];
	int i = 0;

	for (int i = 0; i < 64; i++) {//マスクデータ作成
		slotM[i] = slot[i];
	}
	if (difficult == 0) {//難易度やさしい
		while(i < 64) {

				slot[i] = Decision(slot, i, 2)[i];
				if (slotM[i] != slot[i]) {
					for (int j = 0; j < 64; j++) {
						slot[j] = Decision(slotM, i, 2)[j];
					}
					return slot;
				}
			i++;
		}

	}
	return slot;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(800, 600, 32),ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定と画面モードの設定
	//プログラムの準備
	int slot[64];//盤面認識。0：無、1：白、2：黒
	int slotM[64];//石のマスクデータ
	int flag = 0;//スイッチフラグ
	for (int i = 0; i < 64; i++) {
		if ((i == 27) || (i == 36)) {
			slot[i] = 1;//白の初期位置
		}
		else if ((i == 28)||(i == 35)) {
			slot[i] = 2;//黒の初期位置
		}
		else {
			slot[i] = 0;//盤面初期化
		}
	}
	for (int i = 0; i < 64; i++) {//マスクデータ初期化
		slotM[i] = slot[i];
	}
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		//計算フェイズ
		if ((flag == 0) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			for (int i = 0; i < 64; i++) {
				slot[i] = Player(slot,flag)[i];//左クリック時の処理
			}
			for (int i = 0; i < 64; i++) {//前回との違いを比較
				if (slotM[i] != slot[i]) {//違いがあった場合NPCを動かす
					flag = 1;
				}
			}
		}//プレイヤーフェイズ

		if ((flag == 1)&&((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			for (int i = 0; i < 64; i++) {
				slot[i] = Player(slot,flag)[i];//左クリック時の処理
			}
			for (int i = 0; i < 64; i++) {//前回との違いを比較
				if (slotM[i] != slot[i]) {//違いがあった場合NPCを動かす
					flag = 0;
				}
			}
		}//プレイヤーフェイズ2

		/*if (flag == 1) {
			for (int i = 0; i < 64; i++) {
				slot[i] = NPC(slot, 0)[i];
				slotM[i] = slot[i];
			}
			flag = 0;
		}*/
		//描画フェイズ
		Board();//盤の描画
		Stone(slot);//石の描画
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}