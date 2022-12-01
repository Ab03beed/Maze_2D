//
// Created by ab03bed on 2022-05-07.
//

//Name: Abdulhadi Daher
//Date: 18/8/2022
//Goal: C

#include "Maze.h"


Maze::node::node(){
    this->north_Neighbor = nullptr;
    this->south_Neighbor = nullptr;
    this->east_Neighbor = nullptr;
    this->west_Neighbor = nullptr;

    this->connected_N = false;
    this->connected_S = false;
    this->connected_E = false;
    this->connected_W = false;

    this->isVisted = false;

}


Maze::Maze(){

    //length of the default maze.
    Length = 11;
    Width = 11;

    // To create and connect the nodes in the rows and columns.
    createAndConnectNodes();

}



Maze::Maze(size_t width, size_t length) {

    Width = width;
    Length = length;

    // To create and connect the nodes in the rows and columns.
    createAndConnectNodes();

}


void Maze::createAndConnectNodes(){
    size_t width = Width;
    size_t length = Length;


    // To count nodes in row and column.
    size_t nodesInRow = ((width - 1)/ 2 );
    size_t nodesInColumn = ((length - 1)/ 2);

    //To create the nodes in row and column.
    for (size_t y_Axis = 0; y_Axis < nodesInColumn; y_Axis++) {

        std::vector<node *> rowOfNodes;

        for (size_t x_Axis = 0; x_Axis < nodesInRow; x_Axis++) {
            node* newNode = new node();

            rowOfNodes.push_back(newNode);
        }

        maze2D.push_back(rowOfNodes);
    }


    std::vector<int> randomSandE;

    for(size_t i = 0; i < nodesInRow; i++){
        randomSandE.push_back(i);
    }

    srand(time(0));


    int randomIndex = rand() % randomSandE.size();
    endNode = maze2D[0][randomIndex];


    int randomIndex2 = rand() % randomSandE.size();
    startNode = maze2D[nodesInColumn-1][randomIndex2];


    int tempCounterY = 1;
    for (size_t y_Axis = 0; y_Axis < nodesInColumn; y_Axis++) {

        int tempCounterX = 1;

        for (size_t x_Axis = 0; x_Axis < nodesInRow; x_Axis++) {


            //connect nodes, right and left, up and down
            node *currentNode = maze2D[y_Axis][x_Axis];

            if (tempCounterX <= nodesInRow) {
                //If first node in row
                if (tempCounterX == 1) {
                    currentNode->west_Neighbor = nullptr;
                    currentNode->east_Neighbor = maze2D[y_Axis][x_Axis + 1];
                }
                    //If last node in row
                else if (tempCounterX == nodesInRow) {
                    currentNode->east_Neighbor = nullptr;
                    currentNode->west_Neighbor = maze2D[y_Axis][x_Axis - 1];
                    //If the node between 2 other nodes in row.
                } else {
                    currentNode->east_Neighbor = maze2D[y_Axis][x_Axis + 1];
                    currentNode->west_Neighbor = maze2D[y_Axis][x_Axis - 1];

                }
                tempCounterX += 1;
            }

            if (tempCounterY <= nodesInColumn) {
                //If first node in column
                if (tempCounterY == 1) {
                    currentNode->north_Neighbor = nullptr;
                    currentNode->south_Neighbor = maze2D[y_Axis + 1][x_Axis];
                }
                    //If last node in column
                else if (tempCounterY == nodesInColumn) {
                    currentNode->south_Neighbor = nullptr;
                    currentNode->north_Neighbor = maze2D[y_Axis - 1][x_Axis];
                }
                    //If the node between 2 other nodes in column.
                else {
                    currentNode->north_Neighbor = maze2D[y_Axis - 1][x_Axis];
                    currentNode->south_Neighbor = maze2D[y_Axis + 1][x_Axis];
                }
            }

        }
        tempCounterY += 1;
    }

}

void Maze::DFS_Generator(){

    node *currentNode;

    //To switch all nodes to unvisited
    for (int i = 0; i < maze2D.size(); i++) {
        for (int j = 0; j < maze2D[i].size(); j++) {
            maze2D[i][j]->isVisted = false;

            if(maze2D[i][j] == startNode){
                //Choose start node and let it be currentNode
                currentNode = maze2D[i][j];

                //switch currentNode to visited
                currentNode->isVisted = true;
            }
        }
    }

    srand(time(0));



    //Add currentNode to the stack
    std::stack<node *> myStack;
    myStack.push(currentNode);


    //As long as the stack is not empty
    while (!(myStack.empty())) {
        //Get one node from the stack and let it be currentNode.
        currentNode = myStack.top();
        myStack.pop();

        std::vector<int> tempVector;
        //If currentNode has unvisited neighbors
        if ((currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) ||
            (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) ||
            (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) ||
            (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted)) {

            //Add currentNode to the stack.
            myStack.push(currentNode);

            // 1-> North, 2-> East, 3-> South, 4-> West
            if (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) {
                tempVector.push_back(1);
            }
            if (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) {
                tempVector.push_back(2);
            }
            if (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted) {
                tempVector.push_back(3);
            }
            if (currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) {
                tempVector.push_back(4);
            }

            //Choose randomly unvisited neighbor.
            //
            //  source: https://www.codegrepper.com/code-examples/cpp/select+one+random+element+of+a+vector+in+c%2B%2Bint
            //  Date: 03/07/2022
            //  random = rand() % tempVector.size();
            //  int randomNumber = tempVector[random];

            int random = rand() % tempVector.size();
            int randomNumber = tempVector[random];

            if (randomNumber == 1) {
                currentNode->connected_N = true;
                currentNode->north_Neighbor->isVisted = true;
                myStack.push(currentNode->north_Neighbor);
            } else if (randomNumber == 2) {
                currentNode->connected_E = true;
                currentNode->east_Neighbor->isVisted = true;
                myStack.push(currentNode->east_Neighbor);
            } else if (randomNumber == 3) {
                currentNode->connected_S = true;
                currentNode->south_Neighbor->isVisted = true;
                myStack.push(currentNode->south_Neighbor);
            } else if (randomNumber == 4) {
                currentNode->connected_W = true;
                currentNode->west_Neighbor->isVisted = true;
                myStack.push(currentNode->west_Neighbor);
            }

        }

    }

}

void Maze::DFS_Solving(){
    //To switch all nodes to unvisited
    node* currentNode;

    for (int i = 0; i < maze2D.size(); i++) {
        for (int j = 0; j < maze2D[i].size(); j++) {
            maze2D[i][j]->isVisted = false;

            if(maze2D[i][j] == startNode){
                //Choose start node and let it be currentNode
                currentNode = maze2D[i][j];
            }
        }
    }


    srand(time(0));


    //Add currentNode to the stack
    //std::stack<node *> myStack;
    pathToEnd.push(currentNode);


    //As long as the stack is not empty
    while (!(pathToEnd.empty())) {
        //Get one node from the stack and let it be currentNode.
        currentNode = pathToEnd.top();
        pathToEnd.pop();

        //switch currentNode to visited
        currentNode->isVisted = true;

        if(currentNode == endNode){
            pathToEnd.push(currentNode);
            std::cout << "Maze has been solved!" << std::endl;

            break;
        }


        std::vector<int> tempVector;
        //If currentNode has unvisited neighbors
        if ((currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) ||
            (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) ||
            (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) ||
            (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted)) {

            //Add currentNode to the stack.
            pathToEnd.push(currentNode);

            // 1-> North, 2-> East, 3-> South, 4-> West
            if (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) {
                tempVector.push_back(1);
            }
            if (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) {
                tempVector.push_back(2);
            }
            if (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted) {
                tempVector.push_back(3);
            }
            if (currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) {
                tempVector.push_back(4);
            }


            //Choose randomly unvisited neighbor.
            //
            //  source: https://www.codegrepper.com/code-examples/cpp/select+one+random+element+of+a+vector+in+c%2B%2Bint
            //  Date: 03/07/2022
            //  random = rand() % tempVector.size();
            //  int randomNumber = tempVector[random];

            if(!tempVector.empty()){

                int random = rand() % tempVector.size();
                int randomNumber = tempVector[random];

                if (randomNumber == 1) {
                    pathToEnd.push(currentNode->north_Neighbor);

                } else if (randomNumber == 2) {
                    pathToEnd.push(currentNode->east_Neighbor);

                } else if (randomNumber == 3) {
                    pathToEnd.push(currentNode->south_Neighbor);

                } else if (randomNumber == 4) {
                    pathToEnd.push(currentNode->west_Neighbor);

                }
            }


        }

    }

    if(pathToEnd.empty()){
        std::cerr << "There is no way to solve this maze!" << std::endl;
    }

}

void Maze::printSolvedMaze2D(){

    size_t length = Length;
    size_t width = Width;

    std::stack<node*> tempStack;
    tempStack = pathToEnd;

    std::vector<node * > rightNodes;

    for(int i = tempStack.size(); i > 0 ; i--){

        rightNodes.push_back(tempStack.top());

        tempStack.pop();

    }



    for(size_t y_Axis = 1; y_Axis < length +1; y_Axis++){

        for (size_t x_Axis = 1; x_Axis < width +1; x_Axis++){

            if(y_Axis == 1 ){
                if(x_Axis % 2 == 0 && maze2D[y_Axis - 1][(x_Axis/2) -1] == endNode){
                    std::cout << " E ";
                }else {
                    std::cout << wall;
                }
            }
            else if(y_Axis == length){
                if(x_Axis % 2 == 0 && maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]== startNode){
                    std::cout << " S ";
                }else {
                    std::cout << wall;
                }
            }
            else if(x_Axis == 1 || x_Axis == width){
                std::cout << wall;
            }
            else if(y_Axis % 2 == 0 && x_Axis % 2 == 0){

                bool nodeExistInStack = false;

                for(int i = 0; i < rightNodes.size(); i++){

                    if(rightNodes[i] == maze2D[(y_Axis/2)-1][(x_Axis/2)-1]){

                        nodeExistInStack = true;

                    }
                }

                if(nodeExistInStack){
                    std::cout << rightWay;

                }else{
                    std::cout << path;
                }


            }
            else if( y_Axis % 2 == 0 && x_Axis % 2 != 0 && x_Axis != 1){
                if(maze2D[(y_Axis/2)-1][((x_Axis-1)/2)-1]->connected_E || maze2D[(y_Axis/2)-1][((x_Axis+1)/2)-1]->connected_W){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }

            }
            else if(x_Axis % 2 == 0 && y_Axis % 2 != 0 && y_Axis != 1){

                if(maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]->connected_S || maze2D[((y_Axis+1)/2)-1][(x_Axis/2)-1]->connected_N){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }
            }
            else {
                std::cout << wall;
            }


        }

        std::cout << std::endl;
    }

}

/*
void Maze::DFS_Generator(std::vector<std::vector<Maze::node *>> maze2D){

    node *currentNode;

    //To switch all nodes to unvisited
    for (int i = 0; i < maze2D.size(); i++) {
        for (int j = 0; j < maze2D[i].size(); j++) {
            maze2D[i][j]->isVisted = false;

            if(maze2D[i][j] == startNode){
                //Choose start node and let it be currentNode
                currentNode = maze2D[i][j];

                //switch currentNode to visited
                currentNode->isVisted = true;
            }
        }
    }

    srand(time(0));



    //Add currentNode to the stack
    std::stack<node *> myStack;
    myStack.push(currentNode);


    //As long as the stack is not empty
    while (!(myStack.empty())) {
        //Get one node from the stack and let it be currentNode.
        currentNode = myStack.top();
        myStack.pop();

        std::vector<int> tempVector;
        //If currentNode has unvisited neighbors
        if ((currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) ||
            (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) ||
            (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) ||
            (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted)) {

            //Add currentNode to the stack.
            myStack.push(currentNode);

            // 1-> North, 2-> East, 3-> South, 4-> West
            if (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) {
                tempVector.push_back(1);
            }
            if (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) {
                tempVector.push_back(2);
            }
            if (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted) {
                tempVector.push_back(3);
            }
            if (currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) {
                tempVector.push_back(4);
            }

            //Choose randomly unvisited neighbor.
            //
            //  source: https://www.codegrepper.com/code-examples/cpp/select+one+random+element+of+a+vector+in+c%2B%2Bint
            //  Date: 03/07/2022
            //  random = rand() % tempVector.size();
            //  int randomNumber = tempVector[random];

            int random = rand() % tempVector.size();
            int randomNumber = tempVector[random];

            if (randomNumber == 1) {
                currentNode->connected_N = true;
                currentNode->north_Neighbor->isVisted = true;
                myStack.push(currentNode->north_Neighbor);
            } else if (randomNumber == 2) {
                currentNode->connected_E = true;
                currentNode->east_Neighbor->isVisted = true;
                myStack.push(currentNode->east_Neighbor);
            } else if (randomNumber == 3) {
                currentNode->connected_S = true;
                currentNode->south_Neighbor->isVisted = true;
                myStack.push(currentNode->south_Neighbor);
            } else if (randomNumber == 4) {
                currentNode->connected_W = true;
                currentNode->west_Neighbor->isVisted = true;
                myStack.push(currentNode->west_Neighbor);
            }

        }

    }

}


void Maze::print(size_t width, size_t length, std::vector<std::vector<Maze::node*>> maze2D)const{

    for(size_t y_Axis = 1; y_Axis < length +1; y_Axis++){

        for (size_t x_Axis = 1; x_Axis < width +1; x_Axis++){

            if(y_Axis == 1 ){
                if(x_Axis % 2 == 0 && maze2D[y_Axis - 1][(x_Axis/2) -1] == endNode){
                    std::cout << " E ";
                }else {
                    std::cout << wall;
                }
            }
            else if(y_Axis == length){
                if(x_Axis % 2 == 0 && maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1] == startNode){
                    std::cout << " S ";
                }else {
                    std::cout << wall;
                }
            }
            else if(x_Axis == 1 || x_Axis == width){
                std::cout << wall;
            }
            else if(y_Axis % 2 == 0 && x_Axis % 2 == 0){
                std::cout << path;
            }
            else if( y_Axis % 2 == 0 && x_Axis % 2 != 0 && x_Axis != 1){
                if(maze2D[(y_Axis/2)-1][((x_Axis-1)/2)-1]->connected_E || maze2D[(y_Axis/2)-1][((x_Axis+1)/2)-1]->connected_W){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }

            }
            else if(x_Axis % 2 == 0 && y_Axis % 2 != 0 && y_Axis != 1){

                if(maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]->connected_S || maze2D[((y_Axis+1)/2)-1][(x_Axis/2)-1]->connected_N){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }
            }
            else {
                std::cout << wall;
            }

        }

        std::cout << std::endl;
    }



}


std::stack<Maze::node *> Maze::DFS_Solving(std::vector<std::vector<Maze::node *>> maze2D){

    //To switch all nodes to unvisited
    node *currentNode;

    for (int i = 0; i < maze2D.size(); i++) {
        for (int j = 0; j < maze2D[i].size(); j++) {
            maze2D[i][j]->isVisted = false;

            if(maze2D[i][j] == startNode){
                //Choose start node and let it be currentNode
                currentNode = maze2D[i][j];
            }
        }
    }


    srand(time(0));


    //Add currentNode to the stack
    std::stack<node *> myStack;
    myStack.push(currentNode);


    //As long as the stack is not empty
    while (!(myStack.empty())) {
        //Get one node from the stack and let it be currentNode.
        currentNode = myStack.top();
        myStack.pop();

        //switch currentNode to visited
        currentNode->isVisted = true;

        if(currentNode == endNode){
            myStack.push(currentNode);
            std::cout << "Maze has been solved!" << std::endl;

            return myStack;
        }


        std::vector<int> tempVector;
        //If currentNode has unvisited neighbors
        if ((currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) ||
            (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) ||
            (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) ||
            (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted)) {

            //Add currentNode to the stack.
            myStack.push(currentNode);

            // 1-> North, 2-> East, 3-> South, 4-> West
            if (currentNode->north_Neighbor != nullptr && !currentNode->north_Neighbor->isVisted) {
                tempVector.push_back(1);
            }
            if (currentNode->east_Neighbor != nullptr && !currentNode->east_Neighbor->isVisted) {
                tempVector.push_back(2);
            }
            if (currentNode->south_Neighbor != nullptr && !currentNode->south_Neighbor->isVisted) {
                tempVector.push_back(3);
            }
            if (currentNode->west_Neighbor != nullptr && !currentNode->west_Neighbor->isVisted) {
                tempVector.push_back(4);
            }


            //Choose randomly unvisited neighbor.
            //
            //  source: https://www.codegrepper.com/code-examples/cpp/select+one+random+element+of+a+vector+in+c%2B%2Bint
            //  Date: 03/07/2022
            //  random = rand() % tempVector.size();
            //  int randomNumber = tempVector[random];

            if(!tempVector.empty()){

                int random = rand() % tempVector.size();
                int randomNumber = tempVector[random];

                if (randomNumber == 1) {
                    myStack.push(currentNode->north_Neighbor);

                } else if (randomNumber == 2) {
                    myStack.push(currentNode->east_Neighbor);

                } else if (randomNumber == 3) {
                    myStack.push(currentNode->south_Neighbor);

                } else if (randomNumber == 4) {
                    myStack.push(currentNode->west_Neighbor);

                }
            }


        }

    }

    if(myStack.empty()){
        std::cerr << "There is no way to solve this maze!" << std::endl;
    }


}


void Maze::printSolvedMaze2D(size_t width, size_t length, std::vector<std::vector<Maze::node*>> maze2D,std::stack<node *> wayToEnd){


    std::vector<node * > rightNodes;

    for(int i = wayToEnd.size(); i > 0 ; i--){

        rightNodes.push_back(wayToEnd.top());

        wayToEnd.pop();

    }



    for(size_t y_Axis = 1; y_Axis < length +1; y_Axis++){

        for (size_t x_Axis = 1; x_Axis < width +1; x_Axis++){

            if(y_Axis == 1 ){
                if(x_Axis % 2 == 0 && maze2D[y_Axis - 1][(x_Axis/2) -1] == endNode){
                    std::cout << " E ";
                }else {
                    std::cout << wall;
                }
            }
            else if(y_Axis == length){
                if(x_Axis % 2 == 0 && maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]== startNode){
                    std::cout << " S ";
                }else {
                    std::cout << wall;
                }
            }
            else if(x_Axis == 1 || x_Axis == width){
                std::cout << wall;
            }
            else if(y_Axis % 2 == 0 && x_Axis % 2 == 0){

                bool nodeExistInStack = false;

                for(int i = 0; i < rightNodes.size(); i++){

                    if(rightNodes[i] == maze2D[(y_Axis/2)-1][(x_Axis/2)-1]){

                        nodeExistInStack = true;

                    }
                }

                if(nodeExistInStack){
                    std::cout << rightWay;

                }else{
                    std::cout << path;
                }


            }
            else if( y_Axis % 2 == 0 && x_Axis % 2 != 0 && x_Axis != 1){
                if(maze2D[(y_Axis/2)-1][((x_Axis-1)/2)-1]->connected_E || maze2D[(y_Axis/2)-1][((x_Axis+1)/2)-1]->connected_W){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }

            }
            else if(x_Axis % 2 == 0 && y_Axis % 2 != 0 && y_Axis != 1){

                if(maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]->connected_S || maze2D[((y_Axis+1)/2)-1][(x_Axis/2)-1]->connected_N){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }
            }
            else {
                std::cout << wall;
            }


        }

        std::cout << std::endl;
    }

}

*/

void Maze::print(){
    size_t length = Length;
    size_t width = Width;

    for(size_t y_Axis = 1; y_Axis < length +1; y_Axis++){

        for (size_t x_Axis = 1; x_Axis < width +1; x_Axis++){

            if(y_Axis == 1 ){
                if(x_Axis % 2 == 0 && maze2D[y_Axis - 1][(x_Axis/2) -1] == endNode){
                    std::cout << " E ";
                }else {
                    std::cout << wall;
                }
            }
            else if(y_Axis == length){
                if(x_Axis % 2 == 0 && maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1] == startNode){
                    std::cout << " S ";
                }else {
                    std::cout << wall;
                }
            }
            else if(x_Axis == 1 || x_Axis == width){
                std::cout << wall;
            }
            else if(y_Axis % 2 == 0 && x_Axis % 2 == 0){
                std::cout << path;
            }
            else if( y_Axis % 2 == 0 && x_Axis % 2 != 0 && x_Axis != 1){
                if(maze2D[(y_Axis/2)-1][((x_Axis-1)/2)-1]->connected_E || maze2D[(y_Axis/2)-1][((x_Axis+1)/2)-1]->connected_W){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }

            }
            else if(x_Axis % 2 == 0 && y_Axis % 2 != 0 && y_Axis != 1){

                if(maze2D[((y_Axis-1)/2)-1][(x_Axis/2)-1]->connected_S || maze2D[((y_Axis+1)/2)-1][(x_Axis/2)-1]->connected_N){
                    std::cout << path;
                }else{
                    std::cout << wall;
                }
            }
            else {
                std::cout << wall;
            }

        }

        std::cout << std::endl;
    }



}