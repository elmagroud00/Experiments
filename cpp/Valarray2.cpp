#include "PrintValarray.h"
using namespace std;

int main() {
    int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    valarray<int> v(data, 12);
    valarray<int> r1(v[slice(0, 4, 3)]);
    print("slice(0, 4, 3)", r1);
    valarray<int> r2(v[v > 6]);
    print("elements > 6", r2);
    v[slice(0, 4, 3)] *= valarray<int>(v[slice(0, 4, 3)]);
    print("after squaring first column", v);
    int idx[] = { 1, 4, 7, 10 };
    valarray<int> save(idx, 4);
    v[slice(0, 4, 3)] = save;
    print("v restored", v);
    valarray<size_t> siz(2);
    siz[0] = 2;
    siz[1] = 3;
    valarray<size_t> gap(2);
    gap[0] = 6;
    gap[1] = 2;
    valarray<int> r3(v[gslice(0, siz, gap)]);
    print("2-d slice", r3);
    valarray<bool> mask(false, 5);
    mask[1] = mask[2] = mask[4] = true;
    valarray<int> r4(v[mask]);
    print("v[mask]", r4);
    size_t idx2[] = { 2, 2, 3, 6 };
    valarray<size_t> mask2(idx2, 4);
    valarray<int> r5(v[mask2]);
    print("v[mask2]", r5);
    valarray<char> text("now is the time", 15);
    valarray<char> caps("NITT", 4);
    valarray<size_t> idx3(4);
    idx3[0] = 0;
    idx3[1] = 4;
    idx3[2] = 7;
    idx3[3] = 11;
    text[idx3] = caps;
    print("capitalized", text);
}
