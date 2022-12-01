//
// Created by ab03bed on 2022-05-07.
//

//Name: Abdulhadi Daher
//Date: 18/8/2022
//Goal: C

#ifndef PROJECT_V2_MAZE_H
#define PROJECT_V2_MAZE_H

#include<iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>    // For time()
#include <cstdlib>  //For srand() and rand()


class Maze {
public:
    Maze();
    Maze(size_t width, size_t length);

    size_t Width;
    size_t Length;

    void DFS_Generator();
    void print();
    void DFS_Solving();
    void printSolvedMaze2D();



private:
    struct node{
        node();
        node* north_Neighbor;
        node* south_Neighbor;
        node* east_Neighbor;
        node* west_Neighbor;

        bool isVisted;

        bool connected_N;
        bool connected_S;
        bool connected_E;
        bool connected_W;

    };

    node* startNode;
    node* endNode;




    const std::string wall = " # ";
    const std::string path = "   ";
    const std::string rightWay = " . ";

    std::vector<std::vector<node *>> maze2D;
    std::stack<node *> pathToEnd;

    void createAndConnectNodes();

};


#endif //PROJECT_V2_MAZE_H
