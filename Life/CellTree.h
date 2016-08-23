#ifndef CellTree_h
#define CellTree_h

#include <cstdint>

class CellTree {
public:
    /*
     * Okay, here's the tuning of the tree.
     *
     * TREE_SIZE is how large the tree is. I would use 4 for a quad tree.
     * This means I take 1 bit from the x, 1 bit from the y at a time.
     *
     * There are 64 steps to traverse 64-bit x and y coords 2 bits at a time (128-bit / 2bit).
     *
     * There is a mask of 1 bit per coord
     */
    static const int TREE_SIZE = 4; // quad-tree, 4 items (2 bits)
    static const int TREE_BITS_PER_COORD = 1; // tree bits / 2
    static const int TREE_STEPS = 64; // 128 / TREE_BITS_PER_COORD / 2
    static const int TREE_MASK = 0x1; // bits per x and y

    // default constructor
    CellTree() {
        isAlive = false;
        mChildren = 0;
    }

    // x/y constructor
    CellTree(int64_t xPos, int64_t yPos) : x( xPos ), y( yPos ) {
        isAlive = false;
        mChildren = 0;
    }

    // deconstructor
    ~CellTree();

    // true if this node has children
    bool hasChildren();
    
    // adds a child to the tree
    CellTree* addChild(int index);
    
    // gets a child from the tree
    CellTree* getChild(int index);
    
    bool isAlive;
    int64_t x;
    int64_t y;

private:
    // init children
    void initChildren();

    CellTree **mChildren;
};

#endif