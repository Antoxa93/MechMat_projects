#pragma once
#ifndef FUNC25_H_
#define FUNC25_H_

/* file func25.h
îãîëîøåííÿ ôóíêö³é äëÿ âèêîíàííÿ îá÷èñëåíü ç
çàäà÷³ 25 - Random-2
Âèêîíàâ ñòóäåíò ãðóïè Êîìïìàò-2
À. Â. Íåìèðîâè÷
08.12.2021 */

#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//ñòðóêòóðà ç ïàðàìåòðàìè

typedef struct Random2D {

    unsigned a, c, m, s0, s_n;
    double r_n;

}Random2D;

//ôóíêö³ÿ ïåðåâ³ðêè íà âçàºìíó ïðîñòîòó
int isCoprime(int a, int b);

//ôóíêö³ÿ ãåíåðóâàííÿ ïàðàìåòð³â ñòðóêòóðè òà ïåðåâ³ðêà óìîâ
//çàçíà÷åííèõ â çàäà÷³
void generate_numbers_Random2D(Random2D* self);

//íàñòóïíèé ÷ëåí äëÿ íàòóðàëüíèõ ÷èñåë
unsigned next_s_n(Random2D* self);

//íàñòóïíèé ÷ëåí äëÿ ä³éñíèõ ÷èñåë
double next_r_n(Random2D* self);

//ôóíêö³ÿ ãåíåðóâàííÿ ö³ëîãî ÷-ëà
int generate_integer(Random2D* self);

//ãåíåðóâàííÿ ä³éñíîãî ÷-ëà
double generate_real(Random2D* self);

//ãåíåðóâàííÿ -âèì³ðíîãî âåêòîðà ç ä³éñíèõ ÷èñåë
double* generate_vector(Random2D* self, unsigned n);

//îá÷èñëåííÿ êîåô-òó êîðåëÿö³¿ ì³æ äâîìà ìàñèâàìè ä³éñíèõ ÷èñåë
double corel_coef(double* X, double* Y, unsigned n, FILE* fout);

//îá÷èñëåííÿ îá'ºìó n-âèì³ðíî¿ ñôåðè
double sph_Monte_Carlo(Random2D* self, unsigned N, FILE* fout);

//çàïèñàòè ðåçóëüòàò â ôàéë òà âèâåñòè (ö³ëå)
void print_integer(FILE* fout, const char* text, int num);

//çàïèñàòè ðåçóëüòàò â ôàéë òà âèâåñòè (ä³éñíå)
void print_double(FILE* fout, const char* text, double num);

#endif

