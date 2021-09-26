/*Знайти розв'язок СЛАР методом оберненої матриці*/
/*To find solution for system of linear equation using matrix inversion method*/

#include <iostream>
#include <fstream>

using namespace std;

//getting a matrix without i-row rows and j-column
void getMatrix(double** mas, double** p, int i, int j, int m) {
    int di = 0, dj = 0;
    for (int ki = 0; ki < m - 1; ki++) { // check row indexes
        if (ki == i) {
            di = 1;
        }
        for (int kj = 0; kj < m - 1; kj++) { //check column indexes
            if (kj == j) {
                dj = 1;
            }
            p[ki][kj] = mas[ki + di][kj + dj];
        }
        dj = 0;
    }
}

//finding the determinant
double findDeterminant(double** a, int n) {
    int d = 0, j = 0, k = 1, m = n - 1;
    double** p;
    p = new double* [n];
    for (int i = 0; i < n; i++) {
        p[i] = new double[n];
    }
    if (n < 1) {
        cout << "Determinant not founded" << endl;  //if matrix dont have element, so determinant does not exist          
        return d;
    }
    if (n == 1) {
        d = a[0][0];    //determinant is one element
        return d;
    }
    if (n == 2) {
        d = a[0][0] * a[1][1] - (a[1][0] * a[0][1]); // determinannt for matrix 2x2
        return d;
    }
    if (n > 2) {
        for (int i = 0; i < n; i++) {
            getMatrix(a, p, i, 0, n);   //get new matrix
            d = d + k * a[i][0] * findDeterminant(p, m); // calculate the discriminant
            k = -k;
        }
    }
    return d;
}

void inversionMethod(double** a, double* b, double* x, int n) {
    cout << "___________________________Inversion method________________________________" << endl;
    double dMain = findDeterminant(a, n);
    if (dMain == 0) {
        cout << "Inversion matrix no founded" << endl;      //if matrix doesnt have element, so we dont have solution    
        return;
    }
    double** aLocal;
    double** inversionMatrix;
    aLocal = new double* [n];
    inversionMatrix = new double* [n];
    for (int i = 0; i < n; i++) {
        aLocal[i] = new double[n];
        inversionMatrix[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double tempDet = 0;
            getMatrix(a, aLocal, i, j, n);                  //geting matrix without the i-th row and the j-th column   
            tempDet = findDeterminant(aLocal, n - 1);       //we are looking for determinant for the matrix
            if ((i + j) % 2 == 0) {
                inversionMatrix[j][i] = tempDet;             //form an inverted matrix
            }
            else {
                inversionMatrix[j][i] = -tempDet;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversionMatrix[i][j] = inversionMatrix[i][j] / dMain;      //form a finite inverted matrix
        }
    }
    for (int i = 0; i < n; i++) {
        x[i] = 0;
        for (int j = 0; j < n; j++) {
            x[i] = x[i] + (inversionMatrix[i][j] * b[j]);               //calculate roots
        }
    }
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << " " << endl << endl;       //output of result
    }
}

int main()
{
    int n = 0;
    ifstream file;
    file.open("inversionMethod.txt");
    file >> n;
    double** a = new double* [n];;
    double* b = new double[n];
    double* x = new double[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }
    cout << "___________________________Input matrix________________________________" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> a[i][j];
            cout << a[i][j] << " ";
        }
        file >> b[i];
        cout << "|" << b[i] << endl;
    }
    file.close();
    inversionMethod(a, b, x, n);
}