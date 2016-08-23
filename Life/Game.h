#ifndef Game_h
#define Game_h

#include "World.h"

// this is the game logic class that handles cells living/dying
class Game {
public:
    // default constructor
    Game() {
        world = new World();
    }
    
    // default deconstructor
    ~Game() {
        delete world;
    }
    
    // returns the world
    World* getWorld();
    
    // bulk of game logic, advances the game
    void next();
    
private:
    // list of 8 neighbor coordinates for easy iteration
    static const int coords[];
    
    // traverses down the tree to find all living cells
    void traverse(World *w, CellTree *cell);
    
    // handles a living cell to see what happens in the next frame
    void handleCell(World *w, CellTree *cell);
    
    // handles a dead cell to see what happens in the next frame
    // this is only called from living cell neighbors and should
    // only happen once per dead cell
    void handleDeadCell(World *w, int64_t cellX, int64_t cellY);
    
    // world instance
    World* world;
};

#endif