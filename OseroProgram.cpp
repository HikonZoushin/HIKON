//////////////////////////////////////////////////
//
//作成開始日時 2017/4/19
//オセロプログラム
//MS4年　市原拓馬
//
//////////////////////////////////////////////////

#pragma once
#include "math.h"
#include "DxLib.h"
#include "FPS.h"

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

void Stone(int slot[65]) {//石の描画
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

int* Result(int slot[65], int Win, int Lose ,int flag) {//いろいろ表示
	int MouseX, MouseY, slotP = 0;
	int Sb = 0, Sw = 0;
	int Result[3] = { 0,0,0 };

	for (int i = 0; i < 64; i++) {
		if (slot[i] == 1)Sw++;
		if (slot[i] == 2)Sb++;
	}//色集計

	GetMousePoint(&MouseX, &MouseY);//マウスの座標を取得
	if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
		for (int i = 0; i < 8; i++) {//マウス座標から石のIDを検索
			if ((MouseX >=(i * 8) * 9 + 112) && (MouseX <= ((i + 1) * 8) * 9 + 112)) {
				for (int j = 0; j < 8; j++) {
					if ((MouseY >=(j * 8) * 9 + 12) && (MouseY <= ((j + 1) * 8) * 9 + 12)) {
						slotP = i + j * 8;//IDの特定
						DrawFormatString(18, 94, GetColor(255, 255, 255), "ID %d", slotP);//IDを表示
					}
				}
			}
		}//検索終わり
	}//マウス位置のID表示

	DrawFormatString(10, 54, GetColor(255, 255, 255), " %d勝", Win);
	DrawFormatString(10, 74, GetColor(255, 255, 255), " %d敗", Lose);
	if (Sw + Sb == 64) {
		if (slot[64] == 2) {
			if (Sw > Sb) {
				DrawFormatString(8, 14, GetColor(255, 255, 255), "あなたの負け");
			}
			else {
				DrawFormatString(8, 14, GetColor(255, 255, 255), "あなたの勝ち");
			}
			DrawFormatString(10, 34, GetColor(255, 255, 255), "ESCで再戦");
		}
		else {
			if (Sw > Sb) {
				Result[2]++;
			}
			else {
				Result[1]++;
			}
			DrawFormatString(5, 45, GetColor(255, 255, 255), "ESCで再戦");
		}
		Result[0] = 2;
		return Result;
	}
	else {
		DrawFormatString(20, 14, GetColor(255, 255, 255), "黒の数 %d", Sb);
		DrawFormatString(20, 34, GetColor(255, 255, 255), "白の数 %d", Sw);
		if (flag == 0) {
			DrawFormatString(700, 14, GetColor(255, 255, 255), "あなたの番");
			DrawFormatString(718, 34, GetColor(255, 255, 255), "（黒）");
		}
		else if (flag == 1) {
			DrawFormatString(700, 14, GetColor(255, 255, 255), "相手の番");
			DrawFormatString(718, 34, GetColor(255, 255, 255), "（白）");
		}
		DrawFormatString(695, 54, GetColor(255, 255, 255), "右クリックで");
		DrawFormatString(695, 74, GetColor(255, 255, 255), "パス");
	}
	return Result;
}


int* Decision(int slot[65], int slotP, int Color) {//判定の処理、Colorの値は1：白、2：黒
	int flag = 0;//判定が有効だったかのフラグ

				 //左上の判定
	if ((slotP > 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP != 57)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP - 9] == 2)) || ((Color == 2) && (slot[slotP - 9] == 1)) && (slot[slotP - 9] != 0))) {//左上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (9 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP - 9 * i == 39) || (slotP - 9 * i == 31) || (slotP - 9 * i == 23) || (slotP - 9 * i == 15) || (slotP - 9 * i == 7)))break;//一周した時に処理を終了する
				if (((Color == 1) && (slot[slotP - (9 * i)] == 2)) || ((Color == 2) && (slot[slotP - (9 * i)] == 1))) {}//起点と違う色の場合iを増やす
				else if (((Color == 1) && (slot[slotP - (9 * i)] == 1)) || ((Color == 2) && (slot[slotP - (9 * i)] == 2))) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 9 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 9 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP - (9 * i)] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//左上ここまで

				//上の判定
	if ((slotP >= 16)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP - 8] == 2)) || ((Color == 2) && (slot[slotP - 8] == 1))) && (slot[slotP - 8] != 0)) {//上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (8 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP - (8 * i)] == 2) || (Color == 2) && (slot[slotP - (8 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - (8 * i)] == 1) || (Color == 2) && (slot[slotP - (8 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 8 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 8 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP - (8 * i)] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//上ここまで

				//右上の判定
	if ((slotP > 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP - 7] == 2)) || ((Color == 2) && (slot[slotP - 7] == 1))) && (slot[slotP - 7] != 0)) {//右上に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP - (7 * i) < 0)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP - 7 * i == 48) || (slotP - 7 * i == 40) || (slotP - 7 * i == 32) || (slotP - 7 * i == 24) || (slotP - 7 * i == 16) || (slotP - 7 * i == 8) || (slotP - 7 * i == 0)))break;//一周した時に処理を終了する
				if ((Color == 1) && (slot[slotP - (7 * i)] == 2) || (Color == 2) && (slot[slotP - (7 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP - (7 * i)] == 1) || (Color == 2) && (slot[slotP - (7 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 7 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - 7 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP - (7 * i)] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//右上ここまで

				//左の判定
	if ((slotP != 0) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP !=57)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP - 1] == 2)) || ((Color == 2) && (slot[slotP - 1] == 1))) && (slot[slotP - 1] != 0)) {//左に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if ((slotP - i) < 0)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP - i == 7) || (slotP - i == 15) || (slotP - i == 23) || (slotP - i == 31) || (slotP - i == 39) || (slotP - i == 47) || (slotP - i == 55) || (slotP - i == 63)))break;//一周した時に処理を終了する
				if (((Color == 1) && (slot[slotP - i] == 2)) || ((Color == 2) && (slot[slotP - i] == 1))) {}//起点と違う色の場合iを増やす
				else if (((Color == 1) && (slot[slotP - i] == 1)) || ((Color == 2) && (slot[slotP - i] == 2))) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP - j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP - i] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//左ここまで

				//右の判定
	if ((slotP != 6) && (slotP != 7) && (slotP != 14) && (slotP != 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP + 1] == 2)) || ((Color == 2) && (slot[slotP + 1] == 1))) && (slot[slotP + 1] != 0)) {//右に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if ((slotP + i) > 63)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP + i == 8) || (slotP + i == 16) || (slotP + i == 24) || (slotP + i == 32) || (slotP + i == 40) || (slotP + i == 48) || (slotP + i == 56)))break;//一周した時に処理を終了する
				if ((Color == 1) && (slot[slotP + i] == 2) || (Color == 2) && (slot[slotP + i] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + i] == 1) || (Color == 2) && (slot[slotP + i] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP + i] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//右ここまで

				//右下の判定
	if ((slotP < 46) && (slotP != 38) && (slotP != 39) && (slotP != 30) && (slotP != 31) && (slotP != 22) && (slotP != 23) && (slotP != 14) && (slotP != 15) && (slotP != 6) && (slotP != 7)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP + 9] == 2)) || ((Color == 2) && (slot[slotP + 9] == 1))) && (slot[slotP + 9] != 0)) {//右下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (9 * i) > 63)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP + 9 * i == 24) || (slotP + 9 * i == 32) || (slotP + 9 * i == 40) || (slotP + 9 * i == 48) || (slotP + 9 * i == 56)))break;//一周した時に処理を終了する
				if ((Color == 1) && (slot[slotP + (9 * i)] == 2) || (Color == 2) && (slot[slotP + (9 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (9 * i)] == 1) || (Color == 2) && (slot[slotP + (9 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 9 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 9 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP + 9 * i] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//右下ここまで

				//下の判定
	if ((slotP < 48)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP + 8] == 2)) || ((Color == 2) && (slot[slotP + 8] == 1))) && (slot[slotP + 8] != 0)) {//下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (8 + i) > 63)break;//盤外へ出た際に処理を終了する
				if ((Color == 1) && (slot[slotP + (8 * i)] == 2) || (Color == 2) && (slot[slotP + (8 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (8 * i)] == 1) || (Color == 2) && (slot[slotP + (8 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 8 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 8 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP + 8 * i] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//下ここまで

				//左下の判定
	if ((slotP < 48) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 0)) {//処理を行えないIDを除外
		if ((((Color == 1) && (slot[slotP + 7] == 2)) || ((Color == 2) && (slot[slotP + 7] == 1))) && (slot[slotP + 7] != 0)) {//左下に違う色があった場合
			for (int i = 2; i < 8; i++) {
				if (slotP + (7 * i) > 63)break;//盤外へ出た際に処理を終了する
				if ((i > 2) && ((slotP + 7 * i == 15) || (slotP + 7 * i == 23) || (slotP + 7 * i == 31) || (slotP + 7 * i == 39) || (slotP + 7 * i == 47) || (slotP + 7 * i == 55) || (slotP + 7 * i == 63)))break;//一周した時に処理を終了する
				if ((Color == 1) && (slot[slotP + (7 * i)] == 2) || (Color == 2) && (slot[slotP + (7 * i)] == 1)) {}//起点と違う色の場合iを増やす
				else if ((Color == 1) && (slot[slotP + (7 * i)] == 1) || (Color == 2) && (slot[slotP + (7 * i)] == 2)) {//起点と同じ色の場合
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 7 * j] = 1, flag = 1;//色を白に反転させる
						if (Color == 2)slot[slotP + 7 * j] = 2, flag = 1;//色を黒に反転させる
					}
				}
				else if (slot[slotP + 7 * i] == 0) {//空白だった場合
					break;
				}
			}
		}
	}			//左下ここまで

	if ((flag == 1)) {
		slot[slotP] = Color;
		slot[64] = 1;
	}
	return slot;
}

int* Player(int slot[65],int Color) {//左クリック時の処理
	if (slot[64] == 0) {
		int MouseX, MouseY, slotP = 0;
		GetMousePoint(&MouseX, &MouseY);//マウスの座標を取得
		if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
			for (int i = 0; i < 8; i++) {//マウス座標から石のIDを検索
				if ((MouseX > (i * 8) * 9 + 112) && (MouseX < ((i + 1) * 8) * 9 + 112)) {
					for (int j = 0; j < 8; j++) {
						if ((MouseY > (j * 8) * 9 + 12) && (MouseY < ((j + 1) * 8) * 9 + 12)) {
							slotP = i + j * 8;//IDの特定
							DrawFormatString(18, 94, GetColor(255, 255, 255), "ID %d", slotP);
						}
					}
				}
			}//検索終わり
			if (slot[slotP] == 0) {
				for (int i = 0; i < 64; i++) {
					slot[i] = Decision(slot, slotP, 2)[i];//実判定
				}
			}
		}
	}
	return slot;
}

int* NPC(int slot[65], int difficult) {//NPC
	int slotM[65];
	int Random = GetRand(1);//乱数

	if (slot[64] == 0) {
		for (int i = 0; i < 64; i++) {//マスクデータ作成
			slotM[i] = slot[i];
		}
		if (difficult == 0) {//難易度やさしい
			if (Random == 0) {//左上から
				for (int i = 0; i < 64; i++) {
					if (slot[i] == 0) {
						slot[i] = Decision(slot, i, 1)[i];
						if (slotM[i] != slot[i]) {
							for (int j = 0; j < 64; j++) {
								slot[j] = Decision(slotM, i, 1)[j];
							}
							return slot;
						}
					}
				}//処理終わり
			}
			else if (Random == 1) {//右下から
				for (int i = 63; i > 0; i--) {
					if (slot[i] == 0) {
						slot[i] = Decision(slot, i, 1)[i];
						if (slotM[i] != slot[i]) {
							for (int j = 0; j < 64; j++) {
								slot[j] = Decision(slotM, i, 1)[j];
							}
							return slot;
						}
					}
				}//処理終わり
			}
		}//分岐終わり
	}
	return slot;
}



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(800, 600, 32),ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定と画面モードの設定

	//プログラムの準備
	static int Win = 0, Lose = 0;
	Reset:
	Fps fps; //fps変数
	int slot[65];//盤面認識。0：無、1：白、2：黒
	int slotM[65];//石のマスクデータ
	int flag = 0;//スイッチフラグ
	for (int i = 0; i < 65; i++) {
		if ((i == 27) || (i == 36)) {
			slot[i] = 2;//黒の初期位置
		}
		else if ((i == 28)||(i == 35)) {
			slot[i] = 1;//白の初期位置
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
		fps.Update();	//更新
		if (slot[64] != 2) {
			if (flag == 1) {
				for (int i = 0; i < 65; i++) {
					slot[i] = NPC(slot, 0)[i];
					slotM[i] = slot[i];
				}
				slot[64] = 0;
				flag = 0;
			}//NPC

			if ((flag == 0) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
				for (int i = 0; i < 65; i++) {
					slot[i] = Player(slot, flag)[i];//左クリック時の処理
				}
				slot[64] = 0;
				for (int i = 0; i < 64; i++) {//前回との違いを比較
					if (slotM[i] != slot[i]) {//違いがあった場合NPCを動かす
						flag = 1;
					}
				}
			}//プレイヤー
		}
		if ((flag == 0) && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0))flag = 1;//右クリックでスキップ
		if ((CheckHitKey(KEY_INPUT_ESCAPE) == 1)&&(slot[64] == 2))goto Reset;//ESCキーでリセット

		//描画フェイズ
		Board();//盤の描画
		Stone(slot);//石の描画
		Win += Result(slot, Win, Lose, flag)[1];//勝ち
		Lose += Result(slot, Win, Lose, flag)[2];//負け
		slot[64] = Result(slot,Win,Lose, flag)[0];//結果の描写

		//ScreenFlip();
		fps.Wait();		//待機
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}