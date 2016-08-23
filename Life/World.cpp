#include <cassert>
#include <iostream>
#include "World.h"

using namespace std;

// returns the tree
CellTree* World::getTree() {
    return &mTree;
}

// adds a cell at the x/y coordinate
CellTree* World::addCell( int64_t x, int64_t y, bool alive ) {
    return mAddCell( &mTree, x, y, 0, alive );
}

// gets the cell at the x/y coordinate (null if cell doesnt exist)
CellTree* World::getCell( int64_t x, int64_t y ) {
    return mGetCell( &mTree, x, y, 0 );
}

// shifts bits over of the x/y coords to traverse the quad tree
int World::getBits( int64_t x, int64_t y, int steps ) {
    int shift = (CellTree::TREE_STEPS - steps - 1);
    
    assert(shift >= 0);
    assert(shift < CellTree::TREE_STEPS);
    
    
    int yVal = (y >> shift) & CellTree::TREE_MASK;
    int xVal = (x >> shift) & CellTree::TREE_MASK;
    
    return (yVal << CellTree::TREE_BITS_PER_COORD) | xVal;
}

/*
 * Recursive algorithm to add a cell to the bottom of the tree.
 */
CellTree* World::mAddCell( CellTree *cell, int64_t x, int64_t y, int steps, bool alive ) {
    assert( cell != 0 );

    // get the bits (0-3 if a quad tree) of the x/y coords
    int index = getBits( x, y, steps );
    CellTree *child = 0;

    // if we're at the bottom, add the cell
    if (steps == CellTree::TREE_STEPS - 1) {
        child = cell->addChild( index );
        assert( child != 0 );

        child->x = x;
        child->y = y;
        child->isAlive = alive;
    } else {
        // keep traversing. addChild is a noop is the cell already exists
        child = cell->addChild( index );
        assert( child != 0 );

        // recursively go down
        child = mAddCell( child, x, y, steps + 1, alive );
        assert( child != 0 );
    }

    return child;
}

// recursive algorithm to get a cell from the tree
CellTree* World::mGetCell( CellTree *cell, int64_t x, int64_t y, int steps ) {
    // stop if the cell is null or we're at our destination
    if ( cell == 0 || steps == CellTree::TREE_STEPS )
        return cell;

    // hash the x/y coords
    int index = getBits( x, y, steps );

    // recursively continue
    return mGetCell( cell->getChild( index ), x, y, steps + 1 );
}
