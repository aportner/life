#include <cstdint>

class CellTree {
public:
    /*
     * Okay, here's the tuning of the tree.
     *
     * TREE_SIZE is how large the tree is. I would use 4 for a quad tree.
     * This means I take 1 bit from the x, 1 bit from the y at a time.
     *
     * This is 64 steps to traverse 64-bit x and y coords.
     */
    static const int TREE_SIZE = 4; // quad-tree, 4 items (2 bits)
    static const int TREE_BITS_PER_COORD = 1; // tree bits / 2
    static const int TREE_STEPS = 64; // 128 / TREE_BITS_PER_COORD / 2
    static const int TREE_MASK = 0x1; // bits per x and y

    CellTree() {
        isAlive = false;
        mChildren = 0;
    }

    CellTree(int64_t xPos, int64_t yPos) : x( xPos ), y( yPos ) {
        isAlive = false;
        mChildren = 0;
    }

    ~CellTree();

    CellTree* addChild(int index);
    CellTree* getChild(int index);

    CellTree** getChildren() { return mChildren; }
    
    bool isAlive;
    int64_t x;
    int64_t y;

private:
    void initChildren();

    CellTree **mChildren;
};
