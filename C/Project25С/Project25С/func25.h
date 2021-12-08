#pragma once
#ifndef FUNC25_H_
#define FUNC25_H_

/* file func25.h
���������� ������� ��� ��������� ��������� �
������ 25 - Random-2
������� ������� ����� �������-2
�. �. ���������
08.12.2021 */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//��������� � �����������

typedef struct Random2D {

    unsigned a, c, m, s0, s_n;
    double r_n;

}Random2D;

//������� �������� �� ������ ��������
int isCoprime(int a, int b);

//������� ����������� ��������� ��������� �� �������� ����
//����������� � ������
void generate_numbers_Random2D(Random2D* self);

//��������� ���� ��� ����������� �����
unsigned next_s_n(Random2D* self);

//��������� ���� ��� ������ �����
double next_r_n(Random2D* self);

//������� ����������� ������ �-��
int generate_integer(Random2D* self);

//����������� ������� �-��
double generate_real(Random2D* self);

//����������� -�������� ������� � ������ �����
double* generate_vector(Random2D* self, unsigned n);

//���������� ����-�� ��������� �� ����� �������� ������ �����
double corel_coef(double* X, double* Y, unsigned n, FILE* fout);

//���������� ��'��� n-������ �����
double sph_Monte_Carlo(Random2D* self, unsigned N, FILE* fout);

//�������� ��������� � ���� �� ������� (����)
void print_integer(FILE* fout, const char* text, int num);

//�������� ��������� � ���� �� ������� (�����)
void print_double(FILE* fout, const char* text, double num);

#endif

