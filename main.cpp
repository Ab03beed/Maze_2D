//Name: Abdulhadi Daher
//Date: 18/8/2022
//Goal: C

#include "Maze.h"


bool checkNum(const std::string& str);


int main() {
    std::string choice;
    bool exit = false;

    std::cout<< "1-> 11x11 \n"
                "2-> Custom size \n"
                "3-> show the alternative one more time \n"
                "0-> exit" << std::endl;


    while(!exit){
        std::cout<< "Enter choice >";
        std::getline(std::cin, choice);

        while(choice.size() > 1){
            std::cout<< "Too long, please try again!" << std::endl;
            std::cout<< "Enter choice >";
            std::getline(std::cin, choice);
        }

        switch (choice[0]) {

            case '1':{
                std::cout<< "Default maze" << std::endl;

                Maze maze2D;
                maze2D.DFS_Generator();
                maze2D.print();
                maze2D.DFS_Solving();
                maze2D.printSolvedMaze2D();


                break;
            }

            case '2':{
                std::cout<< "Costume maze size" << std::endl;

                std::string widthInput;
                do{
                    std::cout << "Enter the width: ";
                    std::getline(std::cin, widthInput);

                    if(!checkNum(widthInput)){
                        std::cout << "Invalid input, try again!" << std::endl;
                    }

                } while (!checkNum(widthInput));

                size_t width = stoi(widthInput);


                std::string lengthInput;
                do{
                    std::cout << "Enter the length: ";
                    std::getline(std::cin, lengthInput);

                    if(!checkNum(lengthInput)){
                        std::cout << "Invalid input, try again!" << std::endl;
                    }

                } while (!checkNum(lengthInput));

                size_t length = stoi(lengthInput);


                Maze maze2D(width, length);
                maze2D.DFS_Generator();
                maze2D.print();
                maze2D.DFS_Solving();
                maze2D.printSolvedMaze2D();

                break;
            }

            case '3':{
                std::cout<< "1-> 11x11 \n"
                            "2-> Custom size \n"
                            "3-> show the alternative one more time \n"
                            "0-> exit"<< std::endl;
                break;
            }

            case '0':{
                std::cout<< "Shutting down the program!" << std::endl;
                exit = true;
                break;
            }

            default:{
                std::cout<<"\"" << choice << "\"" << " is not valid option!" << std::endl;
            }
        }


    }

    return 0;
}


bool checkNum(const std::string& str){

    for(char c : str){
        if(!std::isdigit(c)){
            return false;
        }
    }

    if(stoi(str) % 2 == 0 ||stoi(str) < 5 ){
        return false;
    }

    return true;
}