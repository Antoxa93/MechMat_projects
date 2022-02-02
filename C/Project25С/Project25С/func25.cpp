

#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "func25.h"

#define PI 3.141592653589793

// file func25.с 
//оголошення функцій для виконання обчислень з
//задачі 25 - Random-2
//Виконав студент групи Компмат-2
//А. В. Немирович
//08.12.2021


//перевірка на взаємну простоту
int isCoprime(int a, int b) {
    for (int gcd = a; ; gcd = b, b = a % b, a = gcd)
        if (!b) return gcd == 1;
}

// Генерація 
// генерація параметрів згідно умовам задачі
void generate_numbers_Random2(Random2* self) {

    double k = 16 + rand() % 16;
    if (k == 31) {
        self->m = INT_MAX;
    }
    else { self->m = pow(2, k); }

    while (1) {
        self->c = rand();
        if (isCoprime(self->c, self->m)) {  //виконання умови b)
            break;
        }
    }

    // c) виконується, оск маємо m як степінь двійки

    self->a = 1 + 4*(rand()%(self->m/4)); //виконання умови d)

    self->s0 = rand() % self->m;

    self->s_n = self->s0; // для подальшого рекуррентного співвідношення

    
}

// Обчислення наступного члена послідовності для нат. чисел
unsigned next_s_n(Random2* self) {
    //за співвідношенням з умови
    self->s_n = (self->a * self->s_n + self->c) % self->m; //(mod m)

    return self->s_n;
}

// Обчислення наступного члена послідовності для дійсних чисел
double next_r_n(Random2* self) {
    self->r_n = (double)(self->s_n + 1) / (self->m + 1); //формула з умови задачі

    next_s_n(self); // новий член послідовності нат. чисел

    return self->r_n;
}

// Генерація цілого числа
int generate_integer(Random2* self) {

    int a = INT_MAX * (2 * (0.5 - next_r_n(self))); //ціле, в межах int

    return a;
}

// Генерація дійсного числа 0;1
double generate_real(Random2* self) {

    //дійсне число отримуємо як таку різницю
    double a = (double) generate_integer(self) - next_r_n(self); 

    return a;
}

//запис в файл/консоль для цілого
void print_integer(FILE* fout, const char* string, int num) {
    printf(string, num);
    fprintf(fout, string, num);
}

//запис в файл/консоль для дійсного
void print_double(FILE* fout, const char* string, double num) {
    printf(string, num);
    fprintf(fout, string, num);
}



// функція обчислення n-вимірнгої сфери
double sph_Monte_Carlo(Random2* self, unsigned N, FILE* fout) {
    double V = 0;
    double counter = 0; 
    double V_ozn = pow(PI, N / 2.0) / exp(lgamma(N / 2.0 + 1.0)); //за означенням

    //метод Монте-Карло
    for (int i = 0; i < 1000000; i++) {
        double r = 0;
        for (int j = 0; j < N; j++) {
            double x = 2 * (next_r_n(self) - 0.5);
            r += x * x;
        }
        if (sqrt(r) < 1) // рахуємо к-ть точок, які потрапили до кола, тобто на радіусі менше 1
            counter += 1; 
    }

    V = (pow(2, N) * counter) / 1000000; //об'єм
    printf("V of a %u-sphere : %lf\n", N, V);

    printf("V oznachennya : %lf\n", V_ozn);

    printf("Tochnost : %lf\n", fabs(V_ozn - V));


    if (fout) { //запис в файл (за необхідності)
        fprintf(fout, "V of a %u-sphere : %lf\n", N, V);

        fprintf(fout, "V oznachennya : %lf\n", V_ozn);

        fprintf(fout, "Tochnost : %lf\n", fabs(V_ozn - V));
    }
    return V;
}


// Генерація вектору розмірності n з випадкових дійсних чисел
double* generate_vector(Random2* self, unsigned n) {
    double* v = (double*)malloc(n * sizeof * v);
    for (int i = 0; i < n; i++)
        v[i] = generate_real(self);
    return v;
}

// Обчислення коеф-ту кореляції між двома векторами
double corel_coef(double* X, double* Y, unsigned n, FILE* fout) {
    double s_x = 0, s_y = 0, s_xy = 0;
    double sqs_X = 0, sqs_Y = 0; //squareSum

    for (int i = 0; i < n; i++) {
        s_x += X[i];

        s_y += Y[i];

        s_xy += X[i] * Y[i];

        sqs_X += X[i] * X[i];

        sqs_Y += Y[i] * Y[i];
    }

    double corr = (double)(n * s_xy - s_x * s_y) / sqrt((n * sqs_X - s_x * s_x) * (n * sqs_Y - s_y * s_y));
    printf("\nCorrelation coef of %u-rozm vectors = %.1lf\n", n, corr);
    if (fout)
        fprintf(fout, "Correlation coef of %u-rozm vectors = %.1lf\n", n, corr); //записати за необх. в файл
    return corr;
}
