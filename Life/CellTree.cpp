#include <cassert>
#include <cstring>
#include <iostream>
#include "CellTree.h"

using namespace std;

CellTree::~CellTree() {
    // delete all the children recursively
    // this could be easily converted to pooling if I had more time
    if (mChildren != 0) {
        for (int i = 0; i < TREE_SIZE; ++i) {
            if (mChildren[i] != 0) {
                delete mChildren[i];
                mChildren[i] = 0;
            }
        }

        delete mChildren;
        mChildren = 0;
    }
}

bool CellTree::hasChildren() {
    return mChildren != 0;
}

CellTree* CellTree::addChild(int index) {
    // check to see if the child exists already
    CellTree *cell = getChild( index );

    // only add if it doesn't exist
    if ( cell == 0 ) {
        cell = new CellTree();
        assert( cell != 0 );
        
        mChildren[ index ] = cell;
    }

    return cell;
}

CellTree* CellTree::getChild(int index) {
    assert( index < TREE_SIZE );

    // don't initialize children until we get to here
    // since cells with an alive value will not have children
    if (mChildren == 0) {
        initChildren();
    }

    return mChildren[ index ];
}

void CellTree::initChildren() {
    // initialize it to empty children
    mChildren = new CellTree*[TREE_SIZE];
    memset( mChildren, 0, TREE_SIZE * sizeof(CellTree*) );
}
