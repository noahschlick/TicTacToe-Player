//
//  TicTac.h
//  TicTacToe_Copy
//
//  Created by Noah Schlickeisen on 12/14/21.
//  Copyright © 2021 Noah Schlickeisen. All rights reserved.
//

#ifndef TicTac_h
#define TicTac_h
#include <vector>
#include <iostream>
using namespace std;

class TicTac {
private:
    // Keeps track of the number of nodes that are generated
    // while the game is being played.
    int nodesGenerated = 0;
    
    // Keeps track of the moves that the program is analyzing
    int nodesAnalyzed = 0;
    
    // Goal depth is the max depth the program can go down the tree
    // before having to return the max and min values.
    int goalDepth = 2;
    
    // 2d array that represents the tic tac toe 
    int array[3][3];
 
    // The nodes (children) are represented as a vector because
    // a vector can hold an arbirtary amount of values. The
    // tic tac toe table is represeented as a 2d array.
    struct position {
        int table[3][3];
        vector<position *>children;
    };
    
    // Genarates the tic tac toe table
    position *newPosition(int table[3][3]) {
        position *temp = new position;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp->table[i][j] = table[i][j];
            }
        }
        return temp;
    }
    
    // keeping track of best position when not in minimax (after goaldepth is reached)
    position continuePos;
    
    position *root;
    
    // max and min functions take 2 int values and return the greater and smaller values between the 2 of them respectively.
    int max(int input1, int input2){
        if(input1 >= input2){
            return input1;
        }
        else{
            return input2;
        }
    }

    int min(int input1, int input2){
        if(input1 <= input2){
            return input1;
        }
        else{
            return input2;
        }
    }
    
    /*\/\/\//\/\/\/\/\/\/\MOVE_GEN/\/\/\/\/\/\/\/\/\/\/
    Generates another generation of possible moves in the
    minmix tree.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    void MOVE_GEN(position *current, bool maxPlayer) {

        int tempTable[3][3];
     
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
               
                tempTable[i][j] = current->table[i][j];
            }
         
        }

        int moveCount = 0;

        for(int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->table[i][j] == -1) {
                    moveCount += 1;

                    if (maxPlayer) {
                        tempTable[i][j] = 1;
                    } else {
                        tempTable[i][j] = 0;
                    }
                    nodesGenerated++;
                    (current->children).push_back(newPosition(tempTable));

                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            tempTable[i][j] = current->table[i][j];
                        }
                    }
                }
            }
        }
        
        

    }
    
    /*\/\/\//\/\/\/\/\/\/\DEEP_ENOUGH/\/\/\/\/\/\/\/\/\/\/
    returns true if the minmax algorithm reached the bottom
    of thhe list.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    bool DEEP_ENOUGH(int inputDepth){
        if(inputDepth >= goalDepth){
            return true;
        }
        else{
            return false;
        }
    }
    
    
    /*\/\/\//\/\/\/\/\/\/\movesAmount/\/\/\/\/\/\/\/\/\/\/
    Returns the amount of moves int the game.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    int movesAmount(position *current) {
        int size = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(current->table[i][j] == -1) {
                    size += 1;
                }
            }
        }
        return size;
    }
    
    
    /*\/\/\//\/\/\/\/\/\/\isGameOver/\/\/\/\/\/\/\/\/\/\/
    returns true if the all of thhe spaces in the tic
    tac toe game has been filled.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    bool isGameOver(position *current) {
        bool isGameOver = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if(current->table[i][j] == -1)
                    isGameOver = false;
            }
        }
        return isGameOver;
    }
    
    
    /*\/\/\//\/\/\/\/\/\/\MINIMAX/\/\/\/\/\/\/\/\/\/\/
    Calculates the static value of each possible out come.
     in the game.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    int STATIC(position position, bool maxPlayer){
        // two large loop blocks, one checks possible wins on columns, the other checks possible wins on rows, diagonal wins are tracked manually.

        int xCounter = 0;
        int oCounter = 0;
        int winningPositions = 0;
        int xInLine = 0;
        int oInLine = 0;
    //------------------------------------------------------------ rows
            for(int k = 0; k < 3; k++){
                xInLine = 0;
                oInLine = 0;
                for (int j = 0; j < 3; j++) {
                    if(position.table[k][j] == 1){
                        xInLine++;
                        xCounter++;
                    }
                    if(position.table[k][j] == 0){
                        oInLine++;
                        oCounter++;
                    }
                }
                
                if(xInLine == 3)
                    return 100000;
                
                if(oInLine == 3)
                    return -100000;
                
                if(xInLine > 0 && oInLine == 0)
                    winningPositions++;
                
                if(oInLine > 0 && xInLine == 0)
                    winningPositions--;
                
            }
    //------------------------------------------------------------ columns
            for(int j = 0; j < 3; j++){
                xInLine = 0;
                oInLine = 0;
                for (int k = 0; k < 3; k++) {
                    if(position.table[k][j] == 1){
                        xInLine++;
                        xCounter++;
                    }
                    if(position.table[k][j] == 0){
                        oInLine++;
                        oCounter++;
                    }
                }
                if(xInLine == 3)
                    return 100000;
        
                if(oInLine == 3)
                    return -100000;
                
                if(xInLine > 1 && oInLine == 0)
                    winningPositions += 2;
                else if(xInLine > 0 && oInLine == 0)
                    winningPositions++;
                
                if(oInLine > 1 && xInLine == 0)
                    winningPositions -= 2;
                else if(oInLine > 0 && xInLine == 0)
                    winningPositions--;

            }

    //----------------------------------------------- diagonals
        xInLine = 0;
        oInLine = 0;
        
        int firstPos = position.table[0][0];
        int secondPos = position.table[1][1];
        int thirdPos = position.table[2][2];

        if(firstPos == 1)
            xInLine++;
        else if(firstPos == 0)
            oInLine++;
        
        if(secondPos == 1)
            xInLine++;
        else if(secondPos == 0)
            oInLine++;

        if(thirdPos == 1)
            xInLine++;
        else if(thirdPos == 0)
            oInLine++;

        if(xInLine == 3)
            return 100000;
        
        if(oInLine == 3)
            return -100000;

        if(xInLine > 1 && oInLine == 0)
            winningPositions += 2;
        else if(xInLine > 0 && oInLine == 0)
            winningPositions++;
        
        if(oInLine > 1 && xInLine == 0)
            winningPositions -= 2;
        else if(oInLine > 0 && xInLine == 0)
            winningPositions--;
        
        //------------------------- second diagonal


        xInLine = 0;
        oInLine = 0;
        
        firstPos = position.table[0][2];
        secondPos = position.table[1][1];
        thirdPos = position.table[2][0];

        if(firstPos == 1)
            xInLine++;
        else if(firstPos == 0)
            oInLine++;
        
        if(secondPos == 1)
            xInLine++;
        else if(secondPos == 0)
            oInLine++;

        if(thirdPos == 1)
            xInLine++;
        else if(thirdPos == 0)
            oInLine++;
        


        if(xInLine == 3)
            return 100000;
        
        if(oInLine == 3)
            return -100000;
        
        
        
        if(xInLine > 1 && oInLine == 0)
            winningPositions += 2;
        else if(xInLine > 0 && oInLine == 0)
            winningPositions++;
        
        if(oInLine > 1 && xInLine == 0)
            winningPositions -= 2;
        if(oInLine > 0 && xInLine == 0)
            winningPositions--;
        
        return winningPositions;
    }
    
    
    
    /*\/\/\//\/\/\/\/\/\/\MINIMAX/\/\/\/\/\/\/\/\/\/\/
    Iterates through the possible outcome of the game and
    returns the best out come for the player. Will return the
    highest outcome for the max and the lowest for min
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    int MINIMAX(position *node, int depth, bool maxPlayer) {
          
        if(DEEP_ENOUGH(depth) ){
            continuePos = *node;
              
            int maxEval = -100000;
            int minEval = 100000;
            int hueristic;
              
            int size = movesAmount(node);
              
            for (int i = 0; i < size; i++) {
                hueristic = STATIC(*node->children[i], maxPlayer);
                if(maxPlayer){
                    nodesAnalyzed++;
                    cout << "Max " << hueristic << endl;
                    maxEval = max(maxEval, hueristic);
                      
                    if (maxEval == hueristic)
                        root = node->children[i];
    
                } else {
                    nodesAnalyzed++;
                    cout << "Min " << hueristic << endl;
                    minEval = min(minEval, hueristic);
                      
                    if (minEval == hueristic)
                        root = node->children[i];
                }
            }
              
            if(maxPlayer)
                return maxEval;
            else
                return minEval;
              
        }
          
        if(maxPlayer){
            return MINIMAX(node, depth+1, false);
        } else {
            return MINIMAX(node, depth+1, true);
        }
          
        return 0;
    }
      
    
public:
    
    TicTac() {
        // A space on the board is -1 if it is empty, 1
        // if it is an 'X', 0 if it is an 'O'
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                array[i][j] = -1;
            }
        }
        root = newPosition(array);
    }
    
    
    
    /*
     Genarates 2 additional levels of the tree
     */
    void PLY(bool maxPlayer) {
        // Generate the possible moves
        
        int size = movesAmount(root);
        
        MOVE_GEN(root, maxPlayer);
        
        for (int i = 0; i < size; i++) {
            MOVE_GEN(root->children[i], !maxPlayer);
        }
    }
    
    /*\/\/\//\/\/\/\/\/\/\Display Moves/\/\/\/\/\/\/\/\/\/\/
     This method displays the possible moves with in the game.
     It displays the possible moves mainly for testing purposes.
     It displays the possible nodes within the first generation
     then displays the possible nodes in the second generation
     from one nodein the first generation.
     /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    void displayMoves() {
        for (int x = 0; x < (root->children).size(); x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    cout<< root->children[x]->table[y][z];
                }
                cout << endl;
            }
            cout << "-----";
            cout << endl;
        }

        cout << "-----";
        cout << endl;
        cout << "-----";
        cout << endl;


        cout << "SECOND GENARATION" << endl;

        for (int x = 0; x < (root->children[0]->children).size(); x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    cout<< " " << root->children[0]->children[x]->table[y][z];
                }
                cout << endl;
            }
            cout << "-----";
            cout << endl;
        }
    }
    
    
    /*\/\/\//\/\/\/\/\/\/\MakeMove/\/\/\/\/\/\/\/\/\/\/
    Calls the mini max method and displays the results.
    If the game is over, then the methhod will return false.
    /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
    bool makeMove(int depth, bool player) {
        int min_max_value = MINIMAX(root, depth, player);
        
        //call again
        cout << "Value Choosen: " << min_max_value << endl;
        
        //expand position
      
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                if (root->table[y][z] == -1)
                    cout << "_ ";
                else if (root->table[y][z] == 0)
                    cout << "O ";
                else if (root->table[y][z] == 1)
                    cout << "X ";
            }
            cout << endl;
        }
        
        if (isGameOver(root)) {
            cout << "Game is a tie" << endl;
            return false;
        }
        
        if (min_max_value >= 10000) {
            cout << "X player won the game." << endl;
            return false;
        } else if (min_max_value <= -10000) {
            cout << "O player won thhe game." << endl;
            return false;
        }
        
        cout << "------------------------" << endl;
        
        return true;
    }
    
    
    
};

#endif /* TicTac_h */

