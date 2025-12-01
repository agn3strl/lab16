#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

double* full_elements(double* A, int size, double x);
double func(double x);
int put_elements(double* A, int n);
double* calc_elements(double* A, int n);
void input_elements(double* A, int n);
int delete_k(double* A, int size, int start, int k);
double* insert_k(double* A, int size, int k);

int main()
{
	system("chcp 1251");

	double* array;
	double* newarray;
	int size;

	printf("ЗАДАНИЕ 1\n");

	printf("Введите количество элементов массива: ");
	scanf("%d", &size);

	array = (double*)malloc(size * sizeof(double));
	if (array == NULL) {
		puts("error");
		return -1;
	}

	double x;
	printf("Введите значения аргумента функции, по которой будут вычисленны элементы массива: ");
	scanf("%lf", &x);
	full_elements(array, size, x);

	printf("Печать элементов массива, вычисленных по функции 1,8x^2 - sin 10x:\n");
	put_elements(array, size);

	newarray = (double*)malloc(size * sizeof(double));
	if (newarray == NULL) {
		puts("error");
		return -1;
	}
	for (int i = 0; i < size; i++) {
		newarray[i] = array[i];
	}
	
	calc_elements(newarray, size);
	printf("Печать элементов массива с обнуленными отрицательными элементами:\n");
	put_elements(newarray, size);

	free(array);
	free(newarray);

	printf("ЗАДАНИЕ 2\n");

	array = (double*)malloc(size * sizeof(double));
	if (array == NULL) {
		puts("error");
		return -1;
	}

	printf("Введите элементы массива (значения от -1 до 1):\n");
	input_elements(array, size);

	int k;
	printf("Введите количество элементов массива, которые необходимо удалить: ");
	scanf("%d", &k);
	int s;
	printf("Введите, после какого элемента начать производить удаление: ");
	scanf("%d", &s);
	
	newarray = (double*)malloc(size * sizeof(double));
	if (newarray == NULL) {
		puts("error");
		return -1;
	}

	delete_k(array, size, s, k);
	put_elements(array, size - k);

	int c;
	printf("Введите количество элементов для вставки после минимального: ");
	scanf("%d", &c);

	put_elements(insert_k(array, size, c), size - k + c);

	return 0;
}


double func(double x)
{
	return 1.8 * x * x - sin(10 * x);
}

double* full_elements(double* A, int n, double x)
{
	for (int i = 0; i < n; i++) {
		A[i] = func(x);
		x += 0.2;
	}
}

int put_elements(double* A, int n)
{
	for (int i = 0; i < n; i++) printf("A[%d] = %.2lf\n", i + 1, A[i]);
	return 0;
}



double* calc_elements(double* A, int n)
{
	for (int i = 0; i < n; i++) {
		if (A[i] < 0) A[i] = 0;
	}
	return A;
}

void input_elements(double* A, int n)
{
	for (int i = 0; i < n; i++) {
		float temp;
		printf("a[%d] = ", i + 1);
		scanf("%f", &temp);
		if (temp > -1 && temp < 1) A[i] = temp;
		else {
			puts("Значение не соответствует интервалу от -1 до 1");
			break;
		}
	}
}

int delete_k(double* A, int size, int start, int k) 
{
	int n = size - k;
	for (int i = start; i < (size - k); i++) A[i] = A[i + k];
	return n;
}

double* insert_k(double* A, int size, int k)
{
	int min_index = 0;
	double min_value = A[0];
	for (int i = 1; i < size; i++) {
		if (A[i] < min_value) {
			min_value = A[i];
			min_index = i;
		}
	}

	int new_size = size + k;
	double* temp = (double*)realloc(A, new_size * sizeof(double));
	if (temp == NULL) {
		printf("error\n");
		return -1;
	}

	for (int i = 0; i <= min_index; i++) {
		temp[i] = A[i];
	}

	printf("Введите %d элементов для вставки после минимального:\n", k);
	for (int i = 0; i < k; i++) {
		printf("A[%d]: ", i + 1);
		scanf("%lf", &temp[min_index + 1 + i]);
	}

	for (int i = min_index + 1; i < size; i++) {
		temp[i + k] = A[i];
	}

	return temp;
}