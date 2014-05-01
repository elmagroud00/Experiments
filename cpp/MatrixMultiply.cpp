#include <cassert>
#include <iomanip>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <valarray>
using namespace std;

template<class T>
void printMatrix(const valarray<T> &a, size_t n) {
    size_t siz = n * n;
    assert(siz <= a.size());
    for(size_t i = 0; i < siz; i++) {
        cout << setw(5) << a[i];
        cout << ((i + 1) % n ? ' ' : '\n');
    }
    cout << endl;
}

template<class T>
valarray<T> matmult(const valarray<T> &a, size_t arows, size_t acols,
                    const valarray<T> &b, size_t brows, size_t bcols) {
    assert(acols == brows);
    valarray<T> result(arows * bcols);
    for(size_t i = 0; i < arows; ++i)
        for(size_t j = 0; j < bcols; ++j) {
            valarray<T> row = a[slice(acols * i, acols, 1)];
            valarray<T> col = b[slice(j, brows, bcols)];
            result[i * bcols + j] = (row * col).sum();
        }
    return result;
}

int main() {
    const int n = 3;
    int adata[n * n] = { 1, 0, -1, 2, 2, 2, -3, 3, 4 };
    int bdata[n * n] = { 3, 4, -1, 1, -3, 0, -1, 1, 1 };
    valarray<int> a(adata, n * n);
    valarray<int> b(bdata, n * n);
    valarray<int> c(matmult(a, n ,n ,b ,n ,n));
    printMatrix(c, n);
}
