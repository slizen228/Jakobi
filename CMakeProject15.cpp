﻿// CMakeProject13.cpp: определяет точку входа для приложения.
//

#include "CMakeProject15.h"
#include <math.h>

void getMatrixWithoutRowAndCol(double** matrix, int size, int row, int col, double** newMatrix) {
	int offsetRow = 0; //Смещение индекса строки в матрице
	int offsetCol = 0; //Смещение индекса столбца в матрице
	for (int i = 0; i < size - 1; i++) {
		//Пропустить row-ую строку
		if (i == row) {
			offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		}

		offsetCol = 0; //Обнулить смещение столбца
		for (int j = 0; j < size - 1; j++) {
			//Пропустить col-ый столбец
			if (j == col) {
				offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
			}

			newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
		}
	}
}

double matrixDet(double** matrix, int size) {
	double det = 0;
	int degree = 1; // (-1)^(1+j) из формулы определителя

	//Условие выхода из рекурсии
	if (size == 1) {
		return matrix[0][0];
	}
	//Условие выхода из рекурсии
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		//Матрица без строки и столбца
		double** newMatrix = new double* [size - 1];
		for (int i = 0; i < size - 1; i++) {
			newMatrix[i] = new double[size - 1];
		}

		//Раскладываем по 0-ой строке, цикл бежит по столбцам
		for (int j = 0; j < size; j++) {
			//Удалить из матрицы i-ю строку и j-ый столбец
			//Результат в newMatrix
			getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

			//Рекурсивный вызов
			//По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
			//где minor_j - дополнительный минор элемента matrix[0][j]
			// (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
			det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
			//"Накручиваем" степень множителя
			degree = -degree;
		}

		//Чистим память на каждом шаге рекурсии(важно!)
		for (int i = 0; i < size - 1; i++) {
			delete[] newMatrix[i];
		}
		delete[] newMatrix;
	}

	return det;
}

bool simm(double** matrix, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < i; j++) {
			if (matrix[i][j] == matrix[j][i]) {
				continue;
			}
			else {
				return false;
			}

		}
	}
	return true;
}

bool Plus(int N, double** A, double** minor) {
	if (matrixDet(A, N) > 0) {
		for (int i = N - 1; i < 0; i++) {
			getMatrixWithoutRowAndCol(minor, N, i, i, minor);
			if (matrixDet(minor, N) > 0) {
				continue;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

using namespace std;
int Jacobi(int N, double** A, double* b, double* X, double eps) {
	double* temp = new double[N];
	double norm;
	int steps = -1;
	do {
		steps += 1;
		for (int i = 0; i < N; i++) {
			temp[i] = b[i];
			for (int j = 0; j < N; j++) {
				if (i != j)
					temp[i] -= A[i][j] * X[j];
			}
			temp[i] /= A[i][i];
		}
		norm = fabs(X[0] - temp[0]);
		for (int i = 0; i < N; i++) {
			if (fabs(X[i] - temp[i]) > norm)
				norm = fabs(X[i] - temp[i]);
			X[i] = temp[i];
		}
	} while (norm > eps);
	delete[] temp;
	return steps;
}

bool Convergence(int N, double** A, double** minor) {
	if (simm(A, N)) {
		if (Plus(N, A, minor)) {
			if(Plus(N,A,minor2){
				return true;
			}else{
				return false;
			}
			
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

int main()
{


	double eps;
	double* x, * b, ** minor,**minor2;
	double** A;
	int n;
	cin >> n >> eps;
	x = new double[n];
	b = new double[n];
	minor = new double* [n];
	minor2 = new double* [n];
	A = new double* [n];
	for (int i = 0; i < n; i++) {
		cin >> x[i];
		A[i] = new double[n];
		minor[i] = new double[n];
		minor2[i] = new double[n];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
			minor2[i][j] = A[i][j];
			minor[i][j] = A[i][j];
		}
	}
	if (!Convergence(n, A, minor)) {
		cout << "No Convergence";
		return 0;
	}
	cout << "steps:" << Jacobi(n, A, b, x, eps) << endl << "x:" << endl;
	for (int i = 0; i < n; i++) {
		cout << x[i] << endl;
	}
	for (int i = 0; i < n; i++) {
		delete[] A[i];
		delete[] minor[i];
	}
	delete[] x;
	delete[] b;
	return 0;
}
