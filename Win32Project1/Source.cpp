#include "DxLib.h"

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

void Stone(int slot[64]) {//�΂̕`��
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

int* Decision(int slot[64],int slotP, int Color){//����̏����AColor�̒l��1�F���A2�F��
	int flag = 0;//���肪�L�����������̃t���O
	
				 //����̔���
	if ((slotP > 17) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 48) && (slotP != 49) && (slotP != 56) && (slotP != 57)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP - 9] == 2) || (Color == 2) && (slot[slotP - 9] == 1)) {//����ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (9 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP - (9 * i)] == 2) || (Color == 2) && (slot[slotP - (9 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - (9 * i)] == 1) || (Color == 2) && (slot[slotP - (9 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 9 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 9 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//���ケ���܂�

				//��̔���
	if ((slotP > 16)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP - 8] == 2) || (Color == 2) && (slot[slotP - 8] == 1)) {//��ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (8 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP - (8 * i)] == 2) || (Color == 2) && (slot[slotP - (8 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - (8 * i)] == 1) || (Color == 2) && (slot[slotP - (8 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 8 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 8 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�ケ���܂�

				//�E��̔���
	if ((slotP > 15) && (slotP != 22) && (slotP != 23) && (slotP != 30) && (slotP != 31) && (slotP != 38) && (slotP != 39) && (slotP != 46) && (slotP != 47) && (slotP != 54) && (slotP != 55) && (slotP != 62) && (slotP != 63)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP - 7] == 2) || (Color == 2) && (slot[slotP - 7] == 1)) {//�E��ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP - (7 * i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP - (7 * i)] == 2) || (Color == 2) && (slot[slotP - (7 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - (7 * i)] == 1) || (Color == 2) && (slot[slotP - (7 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - 7 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - 7 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�E�ケ���܂�

				//���̔���
	if ((slotP != 0) && (slotP != 8) && (slotP != 16) && (slotP != 24) && (slotP != 32) && (slotP != 40) && (slotP != 48) && (slotP != 56)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP - 1] == 2) || (Color == 2) && (slot[slotP - 1] == 1)) {//���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if ((slotP - i) < 0)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP - i] == 2) || (Color == 2) && (slot[slotP - i] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP - i] == 1) || (Color == 2) && (slot[slotP - i] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP - j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP - j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�������܂�

				//�E�̔���
	if ((slotP != 7) && (slotP != 15) && (slotP != 23) && (slotP != 31) && (slotP != 39) && (slotP != 47) && (slotP != 55) && (slotP != 63)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP + 1] == 2) || (Color == 2) && (slot[slotP + 1] == 1)) {//�E�ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if ((slotP + i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP + i] == 2) || (Color == 2) && (slot[slotP + i] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + i] == 1) || (Color == 2) && (slot[slotP + i] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�E�����܂�

				//�E���̔���
	if ((slotP < 46) && (slotP != 38) && (slotP != 39) && (slotP != 30) && (slotP != 31) && (slotP != 22) && (slotP != 23) && (slotP != 14) && (slotP != 15) && (slotP != 6) && (slotP != 7)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP + 9] == 2) || (Color == 2) && (slot[slotP + 9] == 1)) {//�E���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (9 * i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP + (9 * i)] == 2) || (Color == 2) && (slot[slotP + (9 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (9 * i)] == 1) || (Color == 2) && (slot[slotP + (9 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 9 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 9 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�E�������܂�

				//���̔���
	if ((slotP < 56)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP + 8] == 2) || (Color == 2) && (slot[slotP + 8] == 1)) {//���ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (8 + i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP + (8 * i)] == 2) || (Color == 2) && (slot[slotP + (8 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (8 * i)] == 1) || (Color == 2) && (slot[slotP + (8 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 8 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 8 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//�������܂�

				//�����̔���
	if ((slotP < 48) && (slotP != 24) && (slotP != 25) && (slotP != 32) && (slotP != 33) && (slotP != 40) && (slotP != 41) && (slotP != 1) && (slotP != 8) && (slotP != 9) && (slotP != 16) && (slotP != 17) && (slotP != 0)) {//�������s���Ȃ�ID�����O
		if ((Color == 1) && (slot[slotP + 7] == 2) || (Color == 2) && (slot[slotP + 7] == 1)) {//�����ɈႤ�F���������ꍇ
			for (int i = 2; i < 8; i++) {
				if (slotP + (7 * i) > 63)break;//�ՊO�֏o���ۂɏ������I������
				if ((Color == 1) && (slot[slotP + (7 * i)] == 2) || (Color == 2) && (slot[slotP + (7 * i)] == 1)) {}//�N�_�ƈႤ�F�̏ꍇi�𑝂₷
				else if ((Color == 1) && (slot[slotP + (7 * i)] == 1) || (Color == 2) && (slot[slotP + (7 * i)] == 2)) {//�N�_�Ɠ����F�̏ꍇ
					for (int j = i - 1; j > 0; j--) {
						if (Color == 1)slot[slotP + 7 * j] = 1, flag = 1;//�F�𔒂ɔ��]������
						if (Color == 2)slot[slotP + 7 * j] = 2, flag = 1;//�F�����ɔ��]������
					}
				}
			}
		}
	}			//���������܂�

	if ((flag == 1) && (Color == 1))slot[slotP] = 1;//�w��n�_�ɔ���
	if ((flag == 1) && (Color == 2))slot[slotP] = 2;//�w��n�_�ɍ���
	
	for (int i = 0; i < 64; i++) {//�N���A����
		if (slot[i] == 0)flag = 0;
	}
	if (flag == 1);
	return slot;
	}

int* Player(int slot[64],int Color) {//���N���b�N���̏���
	Color++;
	int MouseX, MouseY, slotP = 0;
	GetMousePoint(&MouseX,&MouseY);//�}�E�X�̍��W���擾
	if ((MouseX > 112) && (MouseY > 12) && (MouseX < 688) && (MouseY < 588)) {
		for (int i = 0; i < 8; i++) {//�}�E�X���W����΂�ID������
			if ((MouseX > (i * 8) * 9 + 112) && (MouseX < ((i + 1) * 8) * 9 + 112)) {
				for (int j = 0; j < 8; j++) {
					if ((MouseY > (j * 8) * 9 + 12) && (MouseY < ((j + 1) * 8) * 9 + 12)) {
						slotP = i + j * 8;//ID�̓���
						DrawFormatString(0, 0, GetColor(255,255,255), "ID %d  ", slotP);
					}
				}
			}
		}//�����I���
		if (slot[slotP] == 0){
			for (int i = 0; i < 64; i++) {
				slot[i] = Decision(slot,slotP, Color)[i];//������
			}
		}
	}
	return slot;
}

int* NPC(int slot[64], int difficult) {
	int slotM[64];
	int i = 0;

	for (int i = 0; i < 64; i++) {//�}�X�N�f�[�^�쐬
		slotM[i] = slot[i];
	}
	if (difficult == 0) {//��Փx�₳����
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
	SetGraphMode(800, 600, 32),ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�Ɖ�ʃ��[�h�̐ݒ�
	//�v���O�����̏���
	int slot[64];//�ՖʔF���B0�F���A1�F���A2�F��
	int slotM[64];//�΂̃}�X�N�f�[�^
	int flag = 0;//�X�C�b�`�t���O
	for (int i = 0; i < 64; i++) {
		if ((i == 27) || (i == 36)) {
			slot[i] = 1;//���̏����ʒu
		}
		else if ((i == 28)||(i == 35)) {
			slot[i] = 2;//���̏����ʒu
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
		if ((flag == 0) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			for (int i = 0; i < 64; i++) {
				slot[i] = Player(slot,flag)[i];//���N���b�N���̏���
			}
			for (int i = 0; i < 64; i++) {//�O��Ƃ̈Ⴂ���r
				if (slotM[i] != slot[i]) {//�Ⴂ���������ꍇNPC�𓮂���
					flag = 1;
				}
			}
		}//�v���C���[�t�F�C�Y

		if ((flag == 1)&&((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			for (int i = 0; i < 64; i++) {
				slot[i] = Player(slot,flag)[i];//���N���b�N���̏���
			}
			for (int i = 0; i < 64; i++) {//�O��Ƃ̈Ⴂ���r
				if (slotM[i] != slot[i]) {//�Ⴂ���������ꍇNPC�𓮂���
					flag = 0;
				}
			}
		}//�v���C���[�t�F�C�Y2

		/*if (flag == 1) {
			for (int i = 0; i < 64; i++) {
				slot[i] = NPC(slot, 0)[i];
				slotM[i] = slot[i];
			}
			flag = 0;
		}*/
		//�`��t�F�C�Y
		Board();//�Ղ̕`��
		Stone(slot);//�΂̕`��
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}