#include "Game.h"

// 8 neighbor coordinates
const int Game::coords[] = { -1, -1, 0, -1, 1, -1, -1, 0, 1, 0, -1, 1, 0, 1, 1, 1 };

// returns the world
World* Game::getWorld() {
    return world;
}

// returns the next World state
void Game::next() {
    // create a new world
    World *w = new World();
    
    // iterate over the current world to create the new world
    traverse(w, world->getTree());
    
    // delete the old world and swap in the new one
    delete world;
    world = w;
}

// traverses down the World tree to find living cells
void Game::traverse(World *w, CellTree *cell) {
    // stop if null
    if (cell == 0) {
        return;
    }
    else if (cell->isAlive) {
        // handle alive cells. alive cells never have children in the tree
        handleCell(w, cell);
    } else {
        // recursively iterate down children if they exist.
        if (cell->hasChildren()) {
            for (int i = 0; i < CellTree::TREE_SIZE; ++i) {
                CellTree *child = cell->getChild(i);
            
                if (child != 0) {
                    traverse(w, child);
                }
            }
        }
    }
}

// handle an alive cell
void Game::handleCell(World *w, CellTree *cell) {
    CellTree *c;
    
    // count of alive neighbors
    int alive = 0;
    
    // iterate over the 8 possible neighbors
    for (int i = 0; i < 16; i += 2) {
        // get the coord offsets
        int xOffset = coords[i];
        int yOffset = coords[i + 1];
        
        // add them to the current cell
        int64_t x = cell->x + xOffset;
        int64_t y = cell->y + yOffset;
        
        // check the cell i the current world
        c = world->getCell(x, y);
        
        // if it's alive, increment counter
        if (c != 0 && c->isAlive) {
            ++alive;
        // if it's dead and we haven't checked this cell yet handle it
        } else if (w->getCell(x, y) == 0) {
            handleDeadCell(w, x, y);
        }
    }
    
    // only add alive cells with 2 or 3 neighbors
    if (alive == 2 || alive == 3) {
        w->addCell(cell->x, cell->y, true);
    }
}

// handle checking of a dead cell
void Game::handleDeadCell(World *w, int64_t cellX, int64_t cellY) {
    CellTree *c;
    
    // count of alive neighbors
    int alive = 0;
    
    // iterate over all 8 possible neighbors
    for (int i = 0; i < 16; i += 2) {
        // get offsets
        int xOffset = coords[i];
        int yOffset = coords[i + 1];
        
        // add them to the current cell
        int64_t x = cellX + xOffset;
        int64_t y = cellY + yOffset;
        
        // check the cell in the current world
        c = world->getCell(x, y);
        
        // add if alive
        if (c != 0 && c->isAlive) {
            ++alive;
        }
    }
    
    // add the current cell to the new world and mark if it is alive
    // this will stop dead cells from being checked twice
    w->addCell(cellX, cellY, alive == 3);
}