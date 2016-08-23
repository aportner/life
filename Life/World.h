#ifndef World_h
#define World_h

#include "CellTree.h"

/*
 * The World class adds logic to traverse the CellTree to add/remove cells.
 * This allows you to navigate 64-bit x/y coordinates by partitioning them
 * via a tree (in this case a quad tree).
 */
class World {
public:
    World() {}

    // add a cell
    CellTree* addCell( int64_t x, int64_t y, bool alive = true );
    
    // remove a cell
    CellTree* getCell( int64_t x, int64_t y );
    
    // get the root of the world tree
    CellTree* getTree();

private:
    // recursive algorithm for adding
    CellTree* mAddCell( CellTree *cell, int64_t x, int64_t y, int steps, bool alive = true );
    
    // recursive algorithm for removing
    CellTree* mGetCell( CellTree *cell, int64_t x, int64_t y, int steps );

    // function to hash a x/y coord into tree space (in quad tree gives you 0-3)
    int getBits( int64_t x, int64_t y, int steps );

    // root tree
    CellTree mTree;
};

#endif