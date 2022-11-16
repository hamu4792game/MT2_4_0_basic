#pragma once

struct Vec2 {
	float x;
	float y;
};

struct Matrix3x3
{
	float m[3][3];
};

//	��
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//	��]�s��̍쐬�֐�
Matrix3x3 MakeRotateMatrix(float theta);

//	���s�ړ��s��̍쐬�֐�
Matrix3x3 MakeTranslateMatrix(Vec2 translate);

//	�񎟌��x�N�g���𓯎����W�Ƃ��ĕϊ�����
Vec2 Transform(Vec2 vector, Matrix3x3 matrix);

//	���W�ϊ�
Vec2 Change(Vec2 pos);

//
static const int kRowHeight = 20;
static const int kColumnWidth = 50;

//	�s��̕`��
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

//	�x�N�g���̕`��
void VectorScreenPrintf(int x, int y, Vec2 vector);