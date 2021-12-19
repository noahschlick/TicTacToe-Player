//
//  main.cpp
//  TicTacPlayer
//
//
//  Created by Noah Schlickeisen on 12/14/21.
//  Copyright © 2021 Noah Schlickeisen. All rights reserved.
//

#include <iostream>
#include "TicTac.h"
using namespace std;
    
   

int main() {
    TicTac tic;
    int depth = 0;
    bool isMax = true;
    bool keepGoing = true;
    
    while(keepGoing){
        tic.PLY(isMax);
        keepGoing = tic.makeMove(depth, isMax);
        isMax = !isMax;
    }

    return 0;
}
