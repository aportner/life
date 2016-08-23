#include <cassert>
#include <cstring>
#include <iostream>
#include "CellTree.h"

using namespace std;

CellTree::~CellTree() {
    if (mChildren != 0) {
        cout << "DELETE" << endl;
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

CellTree* CellTree::addChild(int index) {
    CellTree *cell = getChild( index );

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
    mChildren = new CellTree*[TREE_SIZE];
    memset( mChildren, 0, TREE_SIZE * sizeof(CellTree*) );
}
