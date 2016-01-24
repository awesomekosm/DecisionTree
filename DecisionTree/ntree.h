#pragma once
#include <vector>
#include <iostream>
#include <string>

class ntree {
public:
    struct point {
        std::string data;
        std::vector<point> *pointChildren = new std::vector<point>;
    };
    
    point *addPoint(point *p, std::string &data) {
        point *newPoint = new point();
        newPoint->data = data;
        (*p).pointChildren->push_back(*newPoint);
        return newPoint;
    }

    void itterateNTree(point *tree, std::vector<std::string> &data, int depth) {
        if (tree != NULL) {
            data.push_back(tree->data);
            for (int d = 0; d < depth; d++) {
                std::cout << " ";
            }
            std::cout << '-' << tree->data << '\n';
            for (auto i : *tree->pointChildren) {
                itterateNTree(&i, data, depth+1);
            }
        }
    }
    void printTree(point *tree, std::vector<std::string> &data) {
        itterateNTree(tree, data, 0);
    }

    std::string &breadthFirstSearch(point *tree, std::string &searchTerm) {

    }
    point *depthFirstSearch(point *tree, std::string &searchTerm) {
        if (tree != NULL) {
            if (tree->data.compare(searchTerm)) {
                return tree;
            }
            else {
                for (auto i : *tree->pointChildren) {
                    depthFirstSearch(&i, searchTerm);
                }        
            }
        }
    }


    inline point *getRoot() {
        return root;
    }
private:
    point *root = new point();
};