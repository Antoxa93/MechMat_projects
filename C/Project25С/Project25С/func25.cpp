
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "func25.h"

#define PI 3.141592653589793

// file func25.ñ 
//îãîëîøåííÿ ôóíêö³é äëÿ âèêîíàííÿ îá÷èñëåíü ç
//çàäà÷³ 25 - Random-2
//Âèêîíàâ ñòóäåíò ãðóïè Êîìïìàò-2
//À. Â. Íåìèðîâè÷
//08.12.2021


//ïåðåâ³ðêà íà âçàºìíó ïðîñòîòó
int isCoprime(int a, int b) {
    for (int gcd = a; ; gcd = b, b = a % b, a = gcd)
        if (!b) return gcd == 1;
}

// Ãåíåðàö³ÿ 
// ãåíåðàö³ÿ ïàðàìåòð³â çã³äíî óìîâàì çàäà÷³
void generate_numbers_Random2(Random2D* self) {

    double k = 16 + rand() % 16;
    if (k == 31) {
        self->m = INT_MAX;
    }
    else { self->m = pow(2, k); }

    while (1) {
        self->c = rand();
        if (isCoprime(self->c, self->m)) {
            break;
        }
    }

    self->a = 4 * (rand() % (self->m / 4)) + 1;

    self->s0 = rand() % self->m;

    self->s_n = self->s0;

    //printf("m = %d, a = %d, c = %d, s0 = %d\n", self->m, self->a, self->c, self->s0);
}

// Îá÷èñëåííÿ íàñòóïíîãî ÷ëåíà ïîñë³äîâíîñò³ äëÿ íàò. ÷èñåë
unsigned next_s_n(Random2* self) {
    self->s_n = (self->a * self->s_n + self->c) % self->m;

    return self->s_n;
}

// Îá÷èñëåííÿ íàñòóïíîãî ÷ëåíà ïîñë³äîâíîñò³ äëÿ ä³éñíèõ ÷èñåë
double next_r_n(Random2* self) {
    self->r_n = (double)(self->s_n + 1) / (self->m + 1);

    next_s_n(self);

    return self->r_n;
}

// Ãåíåðàö³ÿ ö³ëîãî ÷èñëà
int generate_integer(Random2* self) {
    int a = INT_MAX * (2 * (0.5 - next_r_n(self)));
    return a;
}

// Ãåíåðàö³ÿ ä³éñíîãî ÷èñëà
double generate_real(Random2* self) {
    double a = (double) generate_integer(self) - next_r_n(self);
    return a;
}

// ôóíêö³ÿ îá÷èñëåííÿ n-âèì³ðíãî¿ ñôåðè
double sph_Monte_Carlo(Random2* self, unsigned N, FILE* fout) {
    double V = 0;
    double counter = 0; 
    double V_ozn = pow(PI, N / 2.0) / exp(lgamma(N / 2.0 + 1.0)); //çà îçíà÷åííÿì

    //ìåòîä Ìîíòå-Êàðëî
    for (int i = 0; i < 100000; i++) {
        double r = 0;
        for (int j = 0; j < N; j++) {
            double x = 2 * (next_r_n(self) - 0.5);
            r += x * x;
        }
        if (sqrt(r) < 1)
            counter += 1; 
    }

    V = (pow(2, N) * counter) / 100000; //îá'ºì
    printf("V of a %u-sphere : %lf\n", N, V);

    printf("V oznachennya : %lf\n", V_ozn);

    printf("Tochnost : %lf\n", fabs(V_ozn - V));


    if (fout) { //çàïèñ â ôàéë (çà íåîáõ³äíîñò³)
        fprintf(fout, "V of a %u-sphere : %lf\n", N, V);

        fprintf(fout, "V oznachennya : %lf\n", V_ozn);

        fprintf(fout, "Tochnost : %lf\n", fabs(V_ozn - V));
    }
    return V;
}

// Ãåíåðàö³ÿ âåêòîðó ðîçì³ðíîñò³ n ç âèïàäêîâèõ ä³éñíèõ ÷èñåë
double* generate_vector(Random2* self, unsigned n) {
    double* v = (double*)malloc(n * sizeof * v);
    for (int i = 0; i < n; i++)
        v[i] = generate_real(self);
    return v;
}

// Îá÷èñëåííÿ êîåô-òó êîðåëÿö³¿ ì³æ äâîìà âåêòîðàìè
double corel_coef(double* X, double* Y, unsigned n, FILE* fout) {
    double s_x = 0, s_y = 0, s_xy = 0;
    double sqs_X = 0, sqs_Y = 0; //squareSum

    for (int i = 0; i < n; i++) {
        s_x += X[i];
        s_y += Y[i];


        s_xy += X[i] * Y[i];
        sqs_X +=  X[i] * X[i];
        sqs_Y +=  Y[i] * Y[i];
    }

    double corr = (double)(n * s_xy - s_x * s_y) / sqrt((n * sqs_X - s_x * s_x) * (n * sqs_Y - s_y * s_y));
    printf("\nCorrelation coef of %u-rozm vectors = %.1lf\n", n, corr);
    if (fout)
        fprintf(fout, "Correlation coef of %u-rozm vectors = %.1lf\n", n, corr);
    return corr;
}


//çàïèñ â ôàéë/êîíñîëü äëÿ ö³ëîãî
void print_integer(FILE* fout, const char* string, int num) {
    printf(string, num);
    fprintf(fout, string, num);
}

//çàïèñ â ôàéë/êîíñîëü äëÿ ä³éñíîãî
void print_double(FILE* fout, const char* string, double num) {
    printf(string, num);
    fprintf(fout, string, num);
}
