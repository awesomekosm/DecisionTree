#include <iostream>
#include "xmlparser.h"
#include "tree.h"
#include "randomizer.h"

int main() {
    Tree *tree = new Tree();
    XMLParser xmlParse("decisions.xml", tree);  
    Randomizer r;

    std::string input;
    std::string searchType = "depthFirstSearch";
    bool running = true;
    while (running == true) {
        std::cout << "Press 1  to print out XML tree of ""decisions.xml""\n";
        std::cout << "Press 2  to change search type: *depthFirstSearch or breadthFirstSearch\n";
        std::cout << "Press 3  to receive a response based on input\n";
        std::cout << "Press q  to Exit \n";
        std::getline(std::cin, input);
        if (input == "1") {
            tree->printTree(tree->getRoot());
        }
        if (input == "2") {
            std::cout << "Enter type: depthFirstSearch or breadthFirstSearch: ";
            std::getline(std::cin, searchType);
        }
        if (input == "3") {
            std::cout << "Press q  to Escape Sequence \n";
            bool getResponses = true;
            std::string behaviorInput;
            
            while (getResponses) {
                std::cout << "Enter a Behavior: ";
                std::getline(std::cin, behaviorInput);
                std::string response = r.getResponse(tree, behaviorInput, searchType);
                std::cout << "Response: " << response << '\n';
                if (behaviorInput == "q") {
                    getResponses = false;
                }
            }        
        }
        if (input == "q") {
            running = false;
            return 0;
        }
    }
}