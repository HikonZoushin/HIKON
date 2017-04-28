//////////////////////////////////////////////////
//
//�쐬�J�n���� 2017/4/19
//�I�Z���v���O����
//MS4�N�@�s����n
//
//////////////////////////////////////////////////

#pragma once
#include "math.h"
#include "DxLib.h"
#include "FPS.h"

void Board() {//�Ֆʂ̕`��
	int Cr = GetColor(0, 0, 0);//���F���w��
	DrawBox(112, 12, 688, 588, GetColor(0, 200, 0), TRUE);//�΂̔Ղ�`��
	for (int i = 0; i < 8; i++) {//�c�������������������
		DrawLine((i * 8) * 9 + 112, 12, (i * 8) * 9 + 112, 588, Cr);
		DrawLine(112, (i * 8) * 9 + 12, 688, (i * 8) * 9 + 12, Cr);
	}
	for (int i = 0; i < 2; i++) {//���ۂ��l���ɒu��
		DrawOval(256, (i * 32) * 9 + 156, 5, 5, Cr, TRUE);
		DrawOval(544, (i * 32) * 9 + 156, 5, 5, Cr, TRUE);
	}
	return;
}

void Stone(int slot[65]) {//�΂̕`��
	int Cr1 = GetColor(255, 255, 255);//�����w��
	int Cr2 = GetColor(0, 0, 0);//�����w��
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (slot[(i + j * 8)] == 1) {//���z�u
				DrawOval((i * 8) * 9 + 148, (j * 8) * 9 + 48, 30, 30, Cr1, TRUE);
			}
			else if (slot[i + j * 8] == 2) {//���z�u
				DrawOval((i * 8) * 9 + 148, (j * 8) * 9 + 48, 30, 30, Cr2, TRUE);
			}
		}
	}
}

int* Result(int slot[65], int Win, int Lose ,int flag) {//���낢��\��
	int MouseX, MouseY, slotP = 0;
	int Sb = 0, Sw = 0;
	int Result[3] = { 0,0,0 };

	for (int i = 0; i < 64; i++) {
		if (slot[i] == 1)Sw++;
		if (slot[i] == 2)Sb++;
	}//�F�W�v

	GetMousePoint(&MouseX, &MouseY);//�}�E�X�̍��W���擾
	if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
		for (int i = 0; i < 8; i++) {//�}�E�X���W����΂�ID������
			if ((MouseX >=(i * 8) * 9 + 112) && (MouseX <= ((i + 1) * 8) * 9 + 112)) {
				for (int j = 0; j < 8; j++) {
					if ((MouseY >=(j * 8) * 9 + 12) && (MouseY <= ((j + 1) * 8) * 9 + 12)) {
						slotP = i + j * 8;//ID�̓���
						DrawFormatString(18, 94, GetColor(255, 255, 255), "ID %d", slotP);//ID��\��
					}
				}
			}
		}//�����I���
	}//�}�E�X�ʒu��ID�\��

	DrawFormatString(10, 54, GetColor(255, 255, 255), " %d��", Win);
	DrawFormatString(10, 74, GetColor(255, 255, 255), " %d�s", Lose);
	if (Sw + Sb == 64) {
		if (slot[64] == 2) {
			if (Sw > Sb) {
				DrawFormatString(8, 14, GetColor(255, 255, 255), "���Ȃ��̕���");
			}
			else {
				DrawFormatString(8, 14, GetColor(255, 255, 255), "���Ȃ��̏���");
			}
			DrawFormatString(10, 34, GetColor(255, 255, 255), "ESC�ōĐ�");
		}
		else {
			if (Sw > Sb) {
				Result[2]++;
			}
			else {
				Result[1]++;
			}
			DrawFormatString(5, 45, GetColor(255, 255, 255), "ESC�ōĐ�");
		}
		Result[0] = 2;
		return Result;
	}
	else {
		DrawFormatString(20, 14, GetColor(255, 255, 255), "���̐� %d", Sb);
		DrawFormatString(20, 34, GetColor(255, 255, 255), "���̐� %d", Sw);
		if (flag == 0) {
			DrawFormatString(700, 14, GetColor(255, 255, 255), "���Ȃ��̔�");
			DrawFormatString(718, 34, GetColor(255, 255, 255), "�i���j");
		}
		else if (flag == 1) {
			DrawFormatString(700, 14, GetColor(255, 255, 255), "����̔�");
			DrawFormatString(718, 34, GetColor(255, 255, 255), "�i���j");
		}
		DrawFormatString(695, 54, GetColor(255, 255, 255), "�E�N���b�N��");
		DrawFormatString(695, 74, GetColor(255, 255, 255), "�p�X");
	}
	return Result;
}


int* Decision(int slot[65], int slotP, int Color) {//����̏����AColor�̒l��1�F���A2�F��
	int flag = 0;//���肪�L�����������̃t���O

				 //����̔���
	if ((slotP > 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP != 57)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP - 9] == 2)) || ((Color == 2) && (slot[slotP - 9] == 1)) && (slot[slotP - 9] != 0))) {//����ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (9 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP - 9 * i == 39) || (slotP - 9 * i == 31) || (slotP - 9 * i == 23) || (slotP - 9 * i == 15) || (slotP - 9 * i == 7)))break;//����������ɏ������I������
				if (((Color == 1) && (slot[slotP - (9 * i)] == 2)) || ((Color == 2) && (slot[slotP - (9 * i)] == 1))) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if (((Color == 1) && (slot[slotP - (9 * i)] == 1)) || ((Color == 2) && (slot[slotP - (9 * i)] == 2))) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 9 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 9 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP - (9 * i)] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//���ケ���܂�

				//��̔���
	if ((slotP >= 16)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP - 8] == 2)) || ((Color == 2) && (slot[slotP - 8] == 1))) && (slot[slotP - 8] != 0)) {//��ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (8 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP - (8 * i)] == 2) || (Color == 2) && (slot[slotP - (8 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - (8 * i)] == 1) || (Color == 2) && (slot[slotP - (8 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 8 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 8 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP - (8 * i)] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�ケ���܂�

				//�E��̔���
	if ((slotP > 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP - 7] == 2)) || ((Color == 2) && (slot[slotP - 7] == 1))) && (slot[slotP - 7] != 0)) {//�E��ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (7 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP - 7 * i == 48) || (slotP - 7 * i == 40) || (slotP - 7 * i == 32) || (slotP - 7 * i == 24) || (slotP - 7 * i == 16) || (slotP - 7 * i == 8) || (slotP - 7 * i == 0)))break;//����������ɏ������I������
				if ((Color == 1) && (slot[slotP - (7 * i)] == 2) || (Color == 2) && (slot[slotP - (7 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - (7 * i)] == 1) || (Color == 2) && (slot[slotP - (7 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 7 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 7 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP - (7 * i)] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�E�ケ���܂�

				//���̔���
	if ((slotP != 0) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP !=57)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP - 1] == 2)) || ((Color == 2) && (slot[slotP - 1] == 1))) && (slot[slotP - 1] != 0)) {//���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if ((slotP - i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP - i == 7) || (slotP - i == 15) || (slotP - i == 23) || (slotP - i == 31) || (slotP - i == 39) || (slotP - i == 47) || (slotP - i == 55) || (slotP - i == 63)))break;//����������ɏ������I������
				if (((Color == 1) && (slot[slotP - i] == 2)) || ((Color == 2) && (slot[slotP - i] == 1))) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if (((Color == 1) && (slot[slotP - i] == 1)) || ((Color == 2) && (slot[slotP - i] == 2))) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP - i] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�������܂�

				//�E�̔���
	if ((slotP != 6) && (slotP != 7) && (slotP != 14) && (slotP != 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP + 1] == 2)) || ((Color == 2) && (slot[slotP + 1] == 1))) && (slot[slotP + 1] != 0)) {//�E�ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if ((slotP + i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP + i == 8) || (slotP + i == 16) || (slotP + i == 24) || (slotP + i == 32) || (slotP + i == 40) || (slotP + i == 48) || (slotP + i == 56)))break;//����������ɏ������I������
				if ((Color == 1) && (slot[slotP + i] == 2) || (Color == 2) && (slot[slotP + i] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + i] == 1) || (Color == 2) && (slot[slotP + i] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP + i] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�E�����܂�

				//�E���̔���
	if ((slotP < 46) && (slotP != 38) && (slotP != 39) && (slotP != 30) && (slotP != 31) && (slotP != 22) && (slotP != 23) && (slotP != 14) && (slotP != 15) && (slotP != 6) && (slotP != 7)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP + 9] == 2)) || ((Color == 2) && (slot[slotP + 9] == 1))) && (slot[slotP + 9] != 0)) {//�E���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (9 * i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP + 9 * i == 24) || (slotP + 9 * i == 32) || (slotP + 9 * i == 40) || (slotP + 9 * i == 48) || (slotP + 9 * i == 56)))break;//����������ɏ������I������
				if ((Color == 1) && (slot[slotP + (9 * i)] == 2) || (Color == 2) && (slot[slotP + (9 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (9 * i)] == 1) || (Color == 2) && (slot[slotP + (9 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 9 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 9 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP + 9 * i] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�E�������܂�

				//���̔���
	if ((slotP < 48)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP + 8] == 2)) || ((Color == 2) && (slot[slotP + 8] == 1))) && (slot[slotP + 8] != 0)) {//���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (8 + i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP + (8 * i)] == 2) || (Color == 2) && (slot[slotP + (8 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (8 * i)] == 1) || (Color == 2) && (slot[slotP + (8 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 8 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 8 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP + 8 * i] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//�������܂�

				//�����̔���
	if ((slotP < 48) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 0)) {//�������s���Ȃ�ID�����O
		if ((((Color == 1) && (slot[slotP + 7] == 2)) || ((Color == 2) && (slot[slotP + 7] == 1))) && (slot[slotP + 7] != 0)) {//�����ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (7 * i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((i > 2) && ((slotP + 7 * i == 15) || (slotP + 7 * i == 23) || (slotP + 7 * i == 31) || (slotP + 7 * i == 39) || (slotP + 7 * i == 47) || (slotP + 7 * i == 55) || (slotP + 7 * i == 63)))break;//����������ɏ������I������
				if ((Color == 1) && (slot[slotP + (7 * i)] == 2) || (Color == 2) && (slot[slotP + (7 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (7 * i)] == 1) || (Color == 2) && (slot[slotP + (7 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 7 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 7 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
				else if (slot[slotP + 7 * i] == 0) {//�󔒂������ꍇ
					break;
				}
			}
		}
	}			//���������܂�

	if ((flag == 1)) {
		slot[slotP] = Color;
		slot[64] = 1;
	}
	return slot;
}

int* Player(int slot[65],int Color) {//���N���b�N���̏���
	if (slot[64] == 0) {
		int MouseX, MouseY, slotP = 0;
		GetMousePoint(&MouseX, &MouseY);//�}�E�X�̍��W���擾
		if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
			for (int i = 0; i < 8; i++) {//�}�E�X���W����΂�ID������
				if ((MouseX > (i * 8) * 9 + 112) && (MouseX < ((i + 1) * 8) * 9 + 112)) {
					for (int j = 0; j < 8; j++) {
						if ((MouseY > (j * 8) * 9 + 12) && (MouseY < ((j + 1) * 8) * 9 + 12)) {
							slotP = i + j * 8;//ID�̓���
							DrawFormatString(18, 94, GetColor(255, 255, 255), "ID %d", slotP);
						}
					}
				}
			}//�����I���
			if (slot[slotP] == 0) {
				for (int i = 0; i < 64; i++) {
					slot[i] = Decision(slot, slotP, 2)[i];//������
				}
			}
		}
	}
	return slot;
}

int* NPC(int slot[65], int difficult) {//NPC
	int slotM[65];
	int Random = GetRand(1);//����

	if (slot[64] == 0) {
		for (int i = 0; i < 64; i++) {//�}�X�N�f�[�^�쐬
			slotM[i] = slot[i];
		}
		if (difficult == 0) {//��Փx�₳����
			if (Random == 0) {//���ォ��
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
				}//�����I���
			}
			else if (Random == 1) {//�E������
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
				}//�����I���
			}
		}//����I���
	}
	return slot;
}



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(800, 600, 32),ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�Ɖ�ʃ��[�h�̐ݒ�

	//�v���O�����̏���
	static int Win = 0, Lose = 0;
	Reset:
	Fps fps; //fps�ϐ�
	int slot[65];//�ՖʔF���B0�F���A1�F���A2�F��
	int slotM[65];//�΂̃}�X�N�f�[�^
	int flag = 0;//�X�C�b�`�t���O
	for (int i = 0; i < 65; i++) {
		if ((i == 27) || (i == 36)) {
			slot[i] = 2;//���̏����ʒu
		}
		else if ((i == 28)||(i == 35)) {
			slot[i] = 1;//���̏����ʒu
		}
		else {
			slot[i] = 0;//�Ֆʏ�����
		}
	}
	for (int i = 0; i < 64; i++) {//�}�X�N�f�[�^������
		slotM[i] = slot[i];
	}

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		//�v�Z�t�F�C�Y
		fps.Update();	//�X�V
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
					slot[i] = Player(slot, flag)[i];//���N���b�N���̏���
				}
				slot[64] = 0;
				for (int i = 0; i < 64; i++) {//�O��Ƃ̈Ⴂ���r
					if (slotM[i] != slot[i]) {//�Ⴂ���������ꍇNPC�𓮂���
						flag = 1;
					}
				}
			}//�v���C���[
		}
		if ((flag == 0) && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0))flag = 1;//�E�N���b�N�ŃX�L�b�v
		if ((CheckHitKey(KEY_INPUT_ESCAPE) == 1)&&(slot[64] == 2))goto Reset;//ESC�L�[�Ń��Z�b�g

		//�`��t�F�C�Y
		Board();//�Ղ̕`��
		Stone(slot);//�΂̕`��
		Win += Result(slot, Win, Lose, flag)[1];//����
		Lose += Result(slot, Win, Lose, flag)[2];//����
		slot[64] = Result(slot,Win,Lose, flag)[0];//���ʂ̕`��

		//ScreenFlip();
		fps.Wait();		//�ҋ@
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}