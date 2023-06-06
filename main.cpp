#include <iostream>
#include "MST.h"
#include "ShortestPath.h"

int main()
{
    MST mst;
    ShortestPath sp;
    char mainChoice = '9';
    std::string filename;

    while(mainChoice != '0') {
        std::cout << "======Select problem to solve: ======" << "\n";
        std::cout << "1. MST" << "\n";
        std::cout << "2. Shortest Path" << "\n";
        std::cout << "0. Exit" << std::endl;
        std::cin >> mainChoice;
        switch (mainChoice) {
            case '0': {
                break;
            }
            case '1': {
                system("CLS");
                mst.displayMSTMenu();
                break;
            }
            case '2': {
                system("CLS");
                sp.displaySPMenu();
                break;
            }
            default: {
                std::cout << "Wrong input" << std::endl;
                system("PAUSE");
                break;
            }
        }
        system("CLS");
    }
    return 0;
}


