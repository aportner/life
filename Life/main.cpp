#include <cstddef>
#include <iostream>
#include <cassert>
#include "World.h"

using namespace std;

void test() {
    World w;

    // test adding
    CellTree *c = w.addCell( 0, 0 );
    c->isAlive = true;

    CellTree *c2 = w.getCell( 0, 0 );
    assert( c == c2 );
}

int main() {
    test();

    return 0;
}
