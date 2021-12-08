#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func25.h"

// file test1.с 
//тестування функцій та виконання задач з
//задачі 25 - Random-2
//Виконав студент групи Компмат-2
//А. В. Немирович
//08.12.2021

void testing (){
	Random2D r;
	
	/*Обчислення об'єму n-вимірної сфери */

	generate_numbers_Random2D(&r);
	//printf("result %d \n", r.m);
	int m;
	printf("Input the dimension of sphere : ");
	scanf("%d", &m);
	sph_Monte_Carlo(&r, m, 0);

	int n;
	FILE* fout = fopen("out_vector.txt", "w");
	/*Генерація вектору з дійсних чисел розмірності n*/
	printf("\n\n\nGenerate real vector, input n: ");

	scanf("%d", &n);
	double* vec = generate_vector(&r, 5);
	printf("\n Real number vector: ");
	for (int i = 0; i < n; i++) {
		printf(" %f ,", vec[i]);
		fprintf(fout, " %f ,", vec[i]);
	}
	fprintf(fout, "\n\n");
	

	/*Генерація двох векторів розмірності 1000 та обчислення
	кореляц. коеф-ту*/

	double* v1 = generate_vector(&r, 1000);
	double* v2 = generate_vector(&r, 1000);
	printf("\n Corelation v1 & v2 \n");
	double cor = corel_coef(v1, v2, 1000, 0);
	//приклад для однакових векторів
	printf("\n Corelation v1 & v1 \n");
	double cor1 = corel_coef(v1, v1, 1000, 0);

	/*Генерація цілих та дійсних чисел та запис в файл*/

	//FILE* fout1 = open("rand_num.txt");

	print_integer(fout, "Next s_n: %u\n", next_s_n(&r));
	print_integer(fout, "Next s_n: %u\n", next_s_n(&r));
	print_double(fout, "Next r_n: %lf\n", next_r_n(&r));
	print_double(fout, "Next r_n: %lf\n", next_r_n(&r));


	print_integer(fout, "Random integer: %i\n", generate_integer(&r));
	print_double(fout, "Random real: %lf\n", generate_real(&r));
	fclose(fout);
	
	//звільнення пам'яті
	free(v1);
	free(v2);
	free(vec);
}

int main() {
	testing();
}