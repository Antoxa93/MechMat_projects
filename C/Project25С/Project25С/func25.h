#pragma once
#ifndef FUNC25_H_
#define FUNC25_H_

/* file func25.h
оголошення функцій для виконання обчислень з
задачі 25 - Random-2
Виконав студент групи Компмат-2
А. В. Немирович
08.12.2021 */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//структура з параметрами

typedef struct Random2D {

    unsigned a, c, m, s0, s_n;
    double r_n;

}Random2D;

//функція перевірки на взаємну простоту
int isCoprime(int a, int b);

//функція генерування параметрів структури та перевірка умов
//зазначенних в задачі
void generate_numbers_Random2D(Random2D* self);

//наступний член для натуральних чисел
unsigned next_s_n(Random2D* self);

//наступний член для дійсних чисел
double next_r_n(Random2D* self);

//функція генерування цілого ч-ла
int generate_integer(Random2D* self);

//генерування дійсного ч-ла
double generate_real(Random2D* self);

//генерування -вимірного вектора з дійсних чисел
double* generate_vector(Random2D* self, unsigned n);

//обчислення коеф-ту кореляції між двома масивами дійсних чисел
double corel_coef(double* X, double* Y, unsigned n, FILE* fout);

//обчислення об'єму n-вимірної сфери
double sph_Monte_Carlo(Random2D* self, unsigned N, FILE* fout);

//записати результат в файл та вивести (ціле)
void print_integer(FILE* fout, const char* text, int num);

//записати результат в файл та вивести (дійсне)
void print_double(FILE* fout, const char* text, double num);

#endif

