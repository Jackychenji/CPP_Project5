
#include <iostream>
#include <iomanip>
#include "DefineMatrix.hpp"

using namespace std;

typedef short T;
const int M = 3;
const int N = 3;

int main()
{
     Matrix<T> m1(3, 3, 4);
     Matrix<T> m2(4, 5);
     short p[10] = {1, 2, 3, 4, 5, 6, 7, 6, 5, 4};

     Matrix<T> m3(2, 5, p, 10);
     Matrix<T> m4(m2);
     Matrix<T> m5 = m2;
     m1.printMatrix();
     m2.printMatrix();
     m3.printMatrix();
     m4.printMatrix();
     m3.transMatrix();
     m2 *m3;
     m2.printMatrix();
     m2.transMatrix();
     m2.printMatrix();
     cout << "m5 used: " << m5.getRefCount() << endl;

     m2.~Matrix();
     cout << "m5 used: " << m5.getRefCount() << endl;

     m4.printMatrix();
     m5.printMatrix();
     cout << "m5 used: " << m5.getRefCount() << endl;
     m4.~Matrix();
     cout << "m5 used: " << m5.getRefCount() << endl;
     m5.printMatrix();
     cout << "m5 used: " << m5.getRefCount() << endl;
     m5.~Matrix();

     return 0;
}