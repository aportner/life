#include <cassert>
#include <iostream>
#include "World.h"

using namespace std;

CellTree* World::addCell( int64_t x, int64_t y ) {
    return mAddCell( &mTree, x, y, 0 );
}

CellTree* World::getCell( int64_t x, int64_t y ) {
    return mGetCell( &mTree, x, y, 0 );
}

int World::getBits( int64_t x, int64_t y, int steps ) {
    int shift = (CellTree::TREE_STEPS - steps - 1);
    assert(shift >= 0);
    assert(shift < CellTree::TREE_STEPS);
    
    int yVal = (y >> shift) & CellTree::TREE_MASK;
    int xVal = (x >> shift) & CellTree::TREE_MASK;
    
    return (yVal << CellTree::TREE_BITS_PER_COORD) | xVal;
}

CellTree* World::mAddCell( CellTree *cell, int64_t x, int64_t y, int steps ) {
    assert( cell != 0 );

    int index = getBits( x, y, steps );
    CellTree *child = 0;

    if (steps == CellTree::TREE_STEPS - 1) {
        cout << "D" << index << endl;

        child = cell->addChild( index );
        assert( child != 0 );

        child->x = x;
        child->y = y;
    } else {
        cout << "C" << index << endl;

        child = cell->addChild( index );
        cout << "C.." << endl;
        assert( child != 0 );

        child = mAddCell( child, x, y, steps + 1 );
        assert( child != 0 );
    }

    return child;
}

CellTree* World::mGetCell( CellTree *cell, int64_t x, int64_t y, int steps ) {
    if ( cell == 0 || steps == CellTree::TREE_STEPS )
        return cell;

    int index = getBits( x, y, steps );

    return mGetCell( cell->getChild( index ), x, y, steps + 1 );
}
