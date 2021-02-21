#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <utility>
using namespace std;

const unsigned puzzleSize = 3;
//can be adjusted to accomodate 15-puzzle or 25-puzzle

class eightPuzzle {
    private:
        vector<vector<string> > puzzle;
        unsigned gCost; //cost from start point to another point in vector
        unsigned hCost; //cost from some point to final point in vector
        pair<int, int> blank;
    public:
        eightPuzzle() {
            gCost = 0;
            hCost = 0;
            blank = make_pair(0, 0);
        }

        eightPuzzle(vector<vector<string> > puzzle) {
            this->puzzle = puzzle;
            gCost = 0;
            hCost = 0;
            blank = findBlank();
        }

        void printPuzzle() {
            for(unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    cout << puzzle.at(i).at(j) << " ";
                }
                cout << endl;
            }
        }

        vector<vector<string> > getState() const {
            return this->puzzle;
        }
        unsigned getGCost() const {
            return this->gCost;
        }
        unsigned getHCost() const {
            return this->hCost;
        }
        pair<int, int> GetBlank() const {
            return this->blank;
        }

        //Shift function checks if tile is blank, if not move to the next tile 
        void moveUp() {
            if(blank.first != 0) {
                string temp = puzzle.at(blank.first - 1).at(blank.second);
                puzzle.at(blank.first - 1).at(blank.second) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.first = blank.first - 1;
            }
            else {
              return;
            }
        }
        void moveDown() {
            if(blank.first != puzzle.size()-1) {
                string temp = puzzle.at(blank.first + 1).at(blank.second);
                puzzle.at(blank.first + 1).at(blank.second) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.first = blank.first + 1;
            }
            else {
              return;
            }
        }
        void moveRight() {
            if(blank.second != puzzle.size()-1) {
                string temp = puzzle.at(blank.first).at(blank.second + 1);
                puzzle.at(blank.first).at(blank.second + 1) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.second= blank.second + 1;
            }
            else {
              return;
            }
        }
        void moveLeft() {
            if (blank.second != 0) {
                string temp = puzzle.at(blank.first).at(blank.second - 1);
                puzzle.at(blank.first).at(blank.second - 1) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.second= blank.second - 1;
            }
            else {
              return;
            }
        }

        //Creates a map called puzzleMap, and check if index + 1 is equal to current entry
        unsigned misplacedTile() {
            unsigned mtCounter = 0;
            vector<int> puzzleMap;
            for(unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    puzzleMap.push_back(stoi(puzzle.at(i).at(j)));
                }
            }
            for(unsigned i = 0; i < puzzleMap.size() - 1; ++i) {
                if (puzzleMap.at(i) != i + 1) {
                    mtCounter += 1;
                }
            }
            if(puzzleMap.at(puzzleMap.size() - 1) != 0) { //check last tile for a blank
                mtCounter += 1;
            }
            return mtCounter;
        }

        unsigned manhattanDistance() {
            unsigned mdCounter = 0;
            unsigned mdSum = 0;
            int tempCounter = 1;
            //for loop checks distance from first tile to i and j-1, which is the last tile
            for(int i = 0; i < puzzle.size(); ++i) {
                for(int j = 0; j < puzzle.at(i).size() && tempCounter != puzzle.size() * puzzle.size(); ++j) {
                    // If the tiles are not matched up, find the correct position and calculate with mdSum expression
                    if(puzzle.at(i).at(j) != to_string(tempCounter)) {
                        for(int k = 0; k < puzzle.size(); ++k) {
                            for(int l = 0; l < puzzle.at(k).size(); ++l) {
                                if(to_string(tempCounter) == puzzle.at(k).at(l)) {
                                    mdSum += abs(i - k) + abs(j - l);
                                }
                            }
                        }
                    }
                    tempCounter++;
                }
            }
            //checking for blank tile
            if(puzzle.at(puzzle.size()-1).at(puzzle.size()-1) != "0") {
                for(int i = 0; i < puzzle.size(); ++i) {
                    for(int j = 0; j < puzzle.size(); ++j) {
                        if(puzzle.at(i).at(j) == "0") {
                            int tempSize = puzzle.size()-1;
                            mdSum += abs(tempSize - i) + abs(tempSize- j);
                        }
                    }
                }
            }
            return mdSum;
        }

        //Finds blank position in puzzle, in this case the 0
        pair<int, int> findBlank() {
            for(int i = 0; i < puzzle.size(); ++i) {
                for(int j = 0; j < puzzle.at(i).size(); ++j) {
                    if(puzzle.at(i).at(j) == "0") {
                        pair<int, int> blankEntry(i, j);
                        return blankEntry;
                    }
                }
            }
            cerr << "Error finding \"0\"" << endl;
            pair<int, int> blankEntry(-1, -1);
            return blankEntry;
        }

        unsigned calculateFCost() const {
            return getGCost() + getHCost();
        }

        void printCosts() {
            cout << "g Cost: " << gCost << endl;//
            cout << "h Cost: " << hCost << endl;
            cout << "f Cost: " << gCost + hCost << endl;
        }

        //Uses shifting functions to move tiles in tempPuzzle and returns tempPuzzle
        eightPuzzle shiftUp(eightPuzzle tempPuzzle) {
            tempPuzzle.moveUp();
            return tempPuzzle;
        }
        eightPuzzle shiftDown(eightPuzzle tempPuzzle) {
            tempPuzzle.moveDown();
            return tempPuzzle;
        }
        eightPuzzle shiftRight(eightPuzzle tempPuzzle) {
            tempPuzzle.moveRight();
            return tempPuzzle;
        }
        eightPuzzle shiftLeft(eightPuzzle tempPuzzle) {
            tempPuzzle.moveLeft();
            return tempPuzzle;
        }
        //call appropriate algorithm function to calculate cost based on user input
        void setCost(const string &userInput) {
            this->gCost += 1;
            if (userInput == "2") {
                this->hCost = misplacedTile();
            }
            else if(userInput == "3") {
                this->hCost = manhattanDistance();
            }
            else {
                this->hCost = 0;
            }
        }

        //finds the lowest value
        bool operator<(const eightPuzzle &lhs) const {
            return !(this->calculateFCost() < lhs.calculateFCost());
        }
};

//Changes a 2D vector to 1D to check goal state and map
string tempMap(vector<vector<string> > state) {
    string mapState;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state.at(i).size(); ++j) {
            mapState.append(state.at(i).at(j));
        }
    }
    return mapState;
}
//traverses the puzzle and shifts tiles using currState object and getState function
//After each shift setCost function is called to determine the weight of the path
void expandState(eightPuzzle currState, priority_queue<eightPuzzle> &states, map<string, bool> &visitedStates, const string &userInput) {
    eightPuzzle up = currState.shiftUp(currState);
    eightPuzzle down = currState.shiftDown(currState);
    eightPuzzle right = currState.shiftRight(currState);
    eightPuzzle left = currState.shiftLeft(currState);

    visitedStates[tempMap(currState.getState())] = 1;
    if(visitedStates[tempMap(up.getState())] == 0) {
        up.setCost(userInput);
        states.push(up);
    }
    if(visitedStates[tempMap(down.getState())] == 0) {
        down.setCost(userInput);
        states.push(down);
    }
    if(visitedStates[tempMap(left.getState())] == 0) {
        left.setCost(userInput);
        states.push(left);
    }
    if(visitedStates[tempMap(right.getState())] == 0) {
        right.setCost(userInput);
        states.push(right);
    }
}
//bool function to check if destination puzzle has been reached (for default puzzle)
bool findGoalPuzzle(const eightPuzzle &tempPuzzle) {
    string goalPuzzle = "123456780";
    string tempState = tempMap(tempPuzzle.getState());
    if(goalPuzzle == tempState) {
        return true;
    }
    return false;
}
#endif