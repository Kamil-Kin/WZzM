//
//Ortogonalizacja Grama - Schmidta
//
#include <iostream>
#include <cmath>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::memcpy;

int main()
{
	int dim = 5;
	cout << "Podaj ilosc wektorow: ";
	cin >> dim;

	double **input_vectors  = new double *[dim];
	double **output_vectors = new double *[dim];
	double ***elements		= new double **[dim - 1];
	for (int i = 0; i < dim - 1; ++i) 
	{
		elements[i] = new double *[i + 1];
		for (int j = 0; j <= i; ++j) 
			elements[i][j] = new double[dim];
	}
	for (int i = 0; i < dim - 1; ++i)
		for (int c = 0; c <= i; ++c)
			for (int d = 0; d < dim; ++d)
				elements[i][c][d] = 0;

	for (int i = 0; i < dim; ++i)
	{
		input_vectors [i] = new double[dim];
		output_vectors[i] = new double[dim];
	}	
	double *scalar_product;
	double *norm2 = new double[dim];	
	double sum = 0.0;
	int sum2 = 0;

	for (int i = 0; i < dim; ++i) 
	{
		cout << "Podaj wartosci " << dim << " skladowych wektora nr " << i << ": " << endl;
		for (int j = 0; j < dim; ++j)
			cin >> input_vectors[i][j];
	}
	
	for (int i = 0; i < dim; ++i)
		output_vectors[0][i] =  input_vectors[0][i];

	cout << "in/out vector nr " << 0 << ":	";
	for (int i = 0; i < dim; ++i, cout << " ")
		cout << input_vectors[0][i];
	cout << endl;
	for (int j = 0; j < dim; ++j)
		sum += pow(output_vectors[0][j], 2.0);
	norm2[0] = sum;	//cout << "norm  " << 0 << " = " << norm2[0] << endl;

	for (int i = 1; i < dim; ++i) 
	{
		cout << "input vector nr " << i << ":	";
		for (int x = 0; x < dim; ++x, cout << " ")
			cout << input_vectors[i][x];
		cout << endl;

		sum = 0.0;
		for (int j = 0; j < dim; ++j)
			sum += pow(output_vectors[i - 1][j], 2.0);	//norma do kwadratu z wektora wejœciowego v_i
		norm2[i - 1] = sum;	
		//cout << "norm  " << i - 1 << " = " << norm2[i - 1] << endl;

		scalar_product = new double[i]; 
		for (int y = 0; y <= i; ++y) scalar_product[y] = 0;
		
		for (int g = 0; g < i; ++g)
		{
			sum2 = 0;
			for (int h = 0; h < dim; ++h)
				sum2 += (input_vectors[i][h] * output_vectors[g][h]);	//iloczyn skalarny wektora wejœciowego u_i oraz wektora wyjœciowego v_i-1
			scalar_product[g] = sum2;
		}
		//cout << "scalar " << i << " = " << scalar_product[i - 1] << endl;

		for (int j = 0; j < i; ++j)
			for (int k = 0; k < dim; ++k)
				elements[i - 1][j][k] = (scalar_product[j] / norm2[j]) * output_vectors[j][k];	//obliczanie poszczgólnych sk³adników sumy
																								//odejmowanych od wektora wejœciowego v_i
		//cout << "elements nr " << i << ":	";
		//for (int c = 0; c < i; ++c, cout << "	")
		//	for (int d = 0; d < dim; ++d, cout << " ")
		//		cout << elements[i - 1][c][d];
		//cout << endl;

		for (int p = 0; p < i; ++p) 
		{
			for (int r = 0; r < dim; ++r)
				input_vectors[i][r] -= elements[i - 1][p][r];	//odejmowanie poszczególnych sk³adników od wektora wejœciowego
			for (int q = 0; q < dim; ++q)
				output_vectors[i][q] = input_vectors[i][q];
		}
		cout << "output vector nr " << i << ":	";
		for (int f = 0; f < dim; ++f, cout << " ")
			cout << output_vectors[i][f];
		cout << endl;
	}

	delete[] norm2;
	for (int i = 0; i < dim - 1; ++i) 
	{
		for (int j = 0; j <= i; ++j)
			delete[] elements[i][j];
		delete[] elements[i];
	}
	delete[] elements;
	for (int i = 0; i < dim; ++i)
	{
		delete[] output_vectors[i];
		delete[] input_vectors[i];
	}
	delete[] output_vectors;
	delete[] input_vectors;

	system("pause");
	return 0;
}

