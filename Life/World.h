#include "CellTree.h"

class World {
public:
    World() {}

    CellTree* addCell( int64_t x, int64_t y );
    CellTree* getCell( int64_t x, int64_t y );

private:
    CellTree* mAddCell( CellTree *cell, int64_t x, int64_t y, int steps );
    CellTree* mGetCell( CellTree *cell, int64_t x, int64_t y, int steps );

    int getBits( int64_t x, int64_t y, int steps );

    CellTree mTree;
};
