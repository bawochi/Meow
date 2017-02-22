#include <iostream>



using namespace std;

class matrix{
public:
	int **mat;
	int rows = 0;
	int cols = 0;

	matrix(int r, int c){
		rows = r;
		cols = c;

		mat = new int*[r];
		for (int i = 0; i < r; i++){
			mat[i] = new int[c];
		}
	}

	void populateMatrix(){
		int temp;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				cout << "Input mat[" << i + 1 << "][" << j + 1 << "] : ";
				cin >> temp;
				mat[i][j] = temp;
			}
		}
	}

	void padding(){
		int temp;

		if (rows > cols)
			temp = rows;
		else
			temp = cols;

		int newSize = 1;
		while (newSize < temp){
			newSize *= 2;
		}

		matrix newMat(newSize, newSize);
		cout << "newSize = " << newSize << endl;

		for (int i = 0; i < newSize; i++){
			for (int j = 0; j < newSize; j++){
				if (i >= rows)
					newMat.mat[i][j] = 0;
				else if (j >= cols)
					newMat.mat[i][j] = 0;
				else
					newMat.mat[i][j] = mat[i][j];

			}
		}

		mat = newMat.mat;
		rows = newSize;
		cols = newSize;
	}

	void printMatrix(){
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				cout << mat[i][j] << "  ";
			}
			cout << endl;
		}
	}

	//getMatrix(){};
};

matrix iterativeMutl(matrix mat1, matrix mat2){
	int **A = mat1.mat;
	int **B = mat2.mat;

	int Cr = mat1.rows;
	int Cc = mat2.cols;
	int common = mat2.rows;
	int sum = 0;

	matrix ans(Cr, Cc);

	int** C = new int*[Cr];
	for (int i = 0; i < Cr; ++i)
		C[i] = new int[Cc];


	for (int i = 0; i < Cr; i++){
		for (int j = 0; j < Cc; j++){
			sum = 0;
			for (int k = 0; k < common; k++){
				sum = sum + A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}

	}

	ans.mat = C;

	return ans;
}

matrix strassenMult(matrix &ans, matrix A, matrix B, int n, int m){

	if (m - n > 2){
		cout << "\n\n PEHLA IF" << endl;
		strassenMult(ans, A, B, n, ((m - n) / 2) - 1);
		strassenMult(ans, A, B, ((m - n) / 2), m);
	}
	else{
		int M1 = (A.mat[n + 0][n + 0] + A.mat[n + 1][n + 1]) * (A.mat[n + 0][n + 0] + A.mat[n + 1][n + 1]);
		int M2 = (A.mat[n + 1][n + 0] + A.mat[n + 1][n + 1]) * B.mat[n + 0][n + 0];
		int M3 = A.mat[n + 0][n + 0] * (B.mat[n + 0][n + 1] - B.mat[n + 1][n + 1]);
		int M4 = A.mat[n + 1][n + 1] * (B.mat[n + 1][n + 0] - B.mat[n + 0][n + 0]);
		int M5 = (A.mat[n + 0][n + 0] + A.mat[n + 0][n + 1]) * B.mat[n + 1][n + 1];
		int M6 = (A.mat[n + 1][n + 0] - A.mat[n + 0][n + 0]) * (B.mat[n + 0][n + 0] + B.mat[n + 0][n + 1]);
		int M7 = (A.mat[n + 0][n + 1] - A.mat[n + 1][n + 1]) * (B.mat[n + 1][n + 0] + B.mat[n + 1][n + 1]);

		ans.mat[n + 0][n + 0] = M1 + M4 - M5 + M7;
		ans.mat[n + 0][n + 1] = M3 + M5;
		ans.mat[n + 1][n + 0] = M2 + M4;
		ans.mat[n + 1][n + 1] = M1 - M2 + M3 + M6;



	}
	return ans;
}

matrix strassen(matrix A, matrix B){
	matrix answer(A.rows, B.cols);
	return strassenMult(answer, A, B, 0, A.rows);
}

void padding(matrix &A, matrix &B){
	int temp;

	if (A.rows > A.cols){
		if (A.rows > B.cols){
			temp = A.rows;
		}
	}
	else if (A.cols > A.rows){
		if (A.cols > B.cols){
			temp = A.cols;
		}
	}
	else if (B.cols > A.cols){
		if (B.cols > A.rows){
			temp = B.cols;
		}
	}
	/*if (A.rows >= B.rows && A.cols >= B.cols ){
	if (A.rows > A.cols)
	temp = A.rows;
	else
	temp = A.cols;
	}
	else if (A.rows <= B.rows && A.cols <= B.cols){
	if (B.rows > B.cols)
	temp = B.rows;
	else
	temp = B.cols;
	}*/


	int newSize = 1;
	while (newSize < temp){
		newSize *= 2;
	}
	// ****** Make matrix A  *********
	matrix newMatA(newSize, newSize);
	cout << "newSize = " << newSize << endl;

	for (int i = 0; i < newSize; i++){
		for (int j = 0; j < newSize; j++){
			if (i >= A.rows)
				newMatA.mat[i][j] = 0;
			else if (j >= A.cols)
				newMatA.mat[i][j] = 0;
			else
				newMatA.mat[i][j] = A.mat[i][j];

		}
	}


	A.mat = newMatA.mat;
	A.rows = newSize;
	A.cols = newSize;

	// ****** Make matrix B  *********
	matrix newMatB(newSize, newSize);
	cout << "newSize = " << newSize << endl;

	for (int i = 0; i < newSize; i++){
		for (int j = 0; j < newSize; j++){
			if (i >= B.rows)
				newMatB.mat[i][j] = 0;
			else if (j >= B.cols)
				newMatB.mat[i][j] = 0;
			else
				newMatB.mat[i][j] = B.mat[i][j];

		}
	}

	B.mat = newMatB.mat;
	B.rows = newSize;
	B.cols = newSize;
}

void multiplyMat(int **input1, int **input2, int **resultMat,
	int resultRows, int resultCols, int mat1cols) {

	for (int i = 0; i < resultRows; i++) {
		resultMat[i] = new int[resultCols];
		for (int j = 0; j < resultCols; j++) {
			resultMat[i][j] = 0;
			for (unsigned int k = 0; k < mat1cols; k++) {
				resultMat[i][j] += input1[i][k] * input2[k][j];
			}
		}
	}
}

void addMat(int **input1, int **input2, int **resultMat, int matSize) {
	for (int i = 0; i < matSize; i++) {
		resultMat[i] = new int[matSize];
		for (int j = 0; j < matSize; j++) {
			resultMat[i][j] = input1[i][j] + input2[i][j];
		}
	}
}

void subMat(int **input1, int **input2, int **resultMat, int matSize) {
	for (int i = 0; i < matSize; i++) {
		resultMat[i] = new int[matSize];
		for (int j = 0; j < matSize; j++) {
			resultMat[i][j] = input1[i][j] - input2[i][j];
		}
	}
}

void multiplyMatStras(int **input1, int **input2, int **resultMat, int matSize) {
	if (matSize <= 2) {
		//  cout<<"matsize less than or equal to 2"<<endl;
		multiplyMat(input1, input2, resultMat, matSize, matSize, matSize); //base condition.
	}
	else {
		int matNewSize = matSize / 2;
		/*
		*  Creating A= A00 A01   and B= B00 B01
		*              A10 A11          B10 B11
		*
		*/
		int **A00 = new int *[matSize];
		int **A01 = new int *[matSize];
		int **A10 = new int *[matSize];
		int **A11 = new int *[matSize];
		int **B00 = new int *[matSize];
		int **B01 = new int *[matSize];
		int **B10 = new int *[matSize];
		int **B11 = new int *[matSize];
		//cout<<"init A and B"<<endl;
		/*
		* splitting the input arrays into 4 subarrays
		*/

		for (int i = 0; i < matNewSize; i++) {
			A00[i] = new int[matSize];
			A01[i] = new int[matSize];
			A10[i] = new int[matSize];
			A11[i] = new int[matSize];
			B00[i] = new int[matSize];
			B01[i] = new int[matSize];
			B10[i] = new int[matSize];
			B11[i] = new int[matSize];
			for (int j = 0; j < matNewSize; j++) {

				A00[i][j] = input1[i][j];
				A01[i][j] = input1[i][j + matNewSize];
				A10[i][j] = input1[i + matNewSize][j];
				A11[i][j] = input1[i + matNewSize][j + matNewSize];

				B00[i][j] = input2[i][j];
				B01[i][j] = input2[i][j + matNewSize];
				B10[i][j] = input2[i + matNewSize][j];
				B11[i][j] = input2[i + matNewSize][j + matNewSize];

			}
		}
		/*
		* On to calculating matrices now
		*/

		/*
		* init temp variables(matrices)
		*/
		int **addTemp1 = new int *[matSize];
		int **addTemp2 = new int *[matSize];
		int **addTemp3 = new int *[matSize];
		int **subTemp1 = new int *[matSize];
		int **subTemp2 = new int *[matSize];
		int **m1 = new int *[matSize];
		int **m2 = new int *[matSize];
		int **m3 = new int *[matSize];
		int **m4 = new int *[matSize];
		int **m5 = new int *[matSize];
		int **m6 = new int *[matSize];
		int **m7 = new int *[matSize];

		/*
		* Calculating M1
		*/
		addMat(A00, A11, addTemp1, matNewSize);
		addMat(B00, B11, addTemp2, matNewSize);

		multiplyMatStras(addTemp1, addTemp2, m1, matNewSize);

		//cout<<"m1 done"<<endl;

		/*
		* Calculating M2
		*/
		addMat(A10, A11, addTemp3, matNewSize);
		multiplyMatStras(addTemp3, B00, m2, matNewSize);
		//cout<<"m2 done"<<endl;

		/*
		* Calculating M3
		*/
		subMat(B01, B11, subTemp1, matNewSize);
		multiplyMatStras(A00, subTemp1, m3, matNewSize);
		//cout<<"m3 done"<<endl;

		/*
		* Calculating M4
		*/
		subMat(B10, B00, subTemp2, matNewSize);
		multiplyMatStras(A11, subTemp2, m4, matNewSize);
		//cout<<"m4 done"<<endl;

		/*
		* Calculating M5
		*/

		addMat(A00, A01, addTemp1, matNewSize);
		multiplyMatStras(addTemp1, B11, m5, matNewSize);
		//cout<<"m5 done"<<endl;

		/*
		* Calculating M6
		*/
		subMat(A10, A00, subTemp1, matNewSize);
		addMat(B00, B01, addTemp2, matNewSize);
		multiplyMatStras(subTemp1, addTemp2, m6, matNewSize);
		//cout<<"m6 done"<<endl;

		/*
		* Calculating M7
		*/

		subMat(A01, A11, subTemp2, matNewSize);
		addMat(B10, B11, addTemp1, matNewSize);

		multiplyMatStras(subTemp2, addTemp1, m7, matNewSize);
		//cout<<"m7 done"<<endl;


		/*
		*  Now calculating sub matrices C = C00 C01
		*                                   C10 C11
		*/

		int **C00 = new int *[matSize];
		int **C01 = new int *[matSize];
		int **C10 = new int *[matSize];
		int **C11 = new int *[matSize];

		/*
		* Calculating C00
		*/
		addMat(m1, m4, addTemp1, matNewSize);
		addMat(addTemp1, m7, addTemp2, matNewSize);
		subMat(addTemp2, m5, C00, matNewSize);
		//cout<<"C00 done"<<endl;
		/*
		* Calculating C01
		*/
		addMat(m3, m5, C01, matNewSize);
		//cout<<"C01 done"<<endl;
		/*
		* Calculating C10
		*/
		addMat(m2, m4, C10, matNewSize);
		//cout<<"C10 done"<<endl;
		/*
		* Calculating C11
		*/
		addMat(m1, m3, addTemp1, matNewSize);
		addMat(addTemp1, m6, addTemp2, matNewSize);
		subMat(addTemp2, m2, C11, matNewSize);
		//cout<<"C11 done"<<endl;

		/*
		* Combining the sub matrices now
		*/
		for (int i = 0; i < matNewSize; i++) {
			resultMat[i] = new int[matSize];
			resultMat[i + matNewSize] = new int[matSize];
			for (int j = 0; j < matNewSize; j++) {
				resultMat[i][j] = C00[i][j];
				resultMat[i][j + matNewSize] = C01[i][j];
				resultMat[i + matNewSize][j] = C10[i][j];
				resultMat[i + matNewSize][j + matNewSize] = C11[i][j];
			}
		}
		//cout<<"sub-matrices combined"<<endl;

	}
}

void initMat(int **matrix, int rows, int cols) {
	for (int row_Ite = 0; row_Ite < rows; row_Ite++) {
		matrix[row_Ite] = new int[cols];
		for (int col_Ite = 0; col_Ite < cols; col_Ite++) {
			matrix[row_Ite][col_Ite] = row_Ite + col_Ite;
		}
	}
}

void displayMat(int **matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << "   ";
		}
		cout << endl;
	}
}


void main(){

	matrix m1(2, 3), m2(3, 2);

	cout << "Fill Matrix m1 : \n\n";
	m1.populateMatrix();
	//m1.padding();

	cout << "Fill Matrix m2 : \n\n";
	m2.populateMatrix();


	padding(m1, m2);

	cout << "\n\nMatrix m1 : \n\n";
	m1.printMatrix();

	cout << "\n\nMatrix m2 : \n\n";
	m2.printMatrix();

	cout << "\n\nAnswer by normal mutiplication : \n\n";
	matrix m3(m1.rows, m1.cols);
	multiplyMat(m1.mat, m2.mat, m3.mat, m3.rows, m3.cols, m1.cols);
	m3.printMatrix();

	cout << "\n\nAnswer by strassen mutiplication : \n\n";
	matrix m4(m1.rows, m1.cols);
	multiplyMatStras(m1.mat, m2.mat, m4.mat, m1.rows);
	m4.printMatrix();

	matrix m5(m1.rows, m1.cols);
	subMat(m3.mat, m4.mat, m5.mat, m1.rows);
	cout << "diff between the two results" << endl;
	m5.printMatrix();


	return;
}