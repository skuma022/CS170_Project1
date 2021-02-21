#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include "eightPuzzle.h"
using namespace std;

//Returns userInput as a char once 3 characters have been entered and moves on to the next row
vector<string> getUserInput(string &userInput) {
    getline(cin, userInput);
    userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end());
    vector<string> puzzleRow;
    for(unsigned i = 0; i < puzzleSize; ++i) {
        puzzleRow.push_back(string(1, userInput.at(i)));
    }
    return puzzleRow;
}
//print puzzle along with the costs of the final result
void outputPuzzle(eightPuzzle tempPuzzle) {
    cout << endl;
    tempPuzzle.eightPuzzle::printPuzzle();
    cout << endl;
    tempPuzzle.printCosts();
    cout << endl;
}
//prompt user to input values
int main() {
    vector<vector<string>> puzzle;
    string userInput;
    while(1) {
        cout << "Welcome to Surya Kumaraguru's 8-puzzle solver." << endl;
        cout << "Type '1' for default puzzle, or '2' to enter your own puzzle: " << endl;
        cin >> userInput;
        if(userInput == "1") {
            puzzle = { {"1", "2", "3"}, {"4", "8", "0"}, {"7", "6", "5"} };
            break;
        }
        else if(userInput == "2") {
            cin.ignore();
            cout << "Enter your puzzle, use zero to represent the blank: " << endl;
            cout << "Enter the first row, use spaces in between numbers: " << endl;
            puzzle.push_back(getUserInput(userInput));
            cout << "Enter the second row, use spaces in between numbers: " << endl;
            puzzle.push_back(getUserInput(userInput));
            cout << "Enter the third row, use spaces in between numbers: " << endl;
            puzzle.push_back(getUserInput(userInput));
            break;
        }
        else {
            cout << "Invalid userInput." << endl;
            userInput.clear();
        }
    }
    
    cout << "Pick an algorithm:" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with Misplaced Tile heuristic" << endl;
    cout << "3. A* with Manhattan Distance heuristic" << endl;
    string h_type;
    cin >> h_type;

    eightPuzzle tempPuzzle(puzzle);
    priority_queue<eightPuzzle> state;
    map<string, bool> checkedStates;
    state.push(tempPuzzle);
    unsigned max_queue_size = state.size();
    unsigned nodesExpanded = 0; //keeps track of number of shifts made
    while(!state.empty()) {
        if(max_queue_size < state.size()) {
            max_queue_size = state.size();
        }
        eightPuzzle currentPuzzle = state.top();
        state.pop();
        if(findGoalPuzzle(currentPuzzle)) {
            cout << "Found goal: " << endl;
            outputPuzzle(currentPuzzle);
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Maximum number of nodes in queue: " << max_queue_size << endl;
            cout << "Depth of the goal node: " << currentPuzzle.getGCost() << endl;
            vector<eightPuzzle> path;
            return 0;
        }
        if(max_queue_size > 0) { //while queue isn't empty
            cout << "The best state to expand to is: " << endl;
        }
        else {
            cout << "Expanding state: " << endl;
        }
        outputPuzzle(currentPuzzle);
        expandState(currentPuzzle, state, checkedStates, h_type);
        ++nodesExpanded;
    }
    cout << "No solution found" << endl;
    cout << "Number of nodes expanded: " << nodesExpanded << endl;
    cout << "Max queue size: " << max_queue_size << endl;
    return 0;
}