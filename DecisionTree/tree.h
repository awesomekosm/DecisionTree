#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <queue>

class Tree {
public:
    struct point {
        std::string behavior;
        std::string response;
        std::vector<point> *pointChildren = new std::vector<point>;
    };

    //appends a new point to the old point and sets values
    point *addPoint(point *p, std::string &behavior, std::string &response) {
        point *newPoint = new point();
        newPoint->behavior = behavior;
        newPoint->response = response;
        (*p).pointChildren->push_back(*newPoint);
        return newPoint;
    }

    //recursivly itterate through the tree and print values; visual representation of a tree
    void itterateNTree(point *tree, std::vector<std::string> &pointVector, int depth) {
        if (tree != NULL) {
            pointVector.push_back(std::string(tree->behavior +'_'+ tree->response));
            for (int d = 0; d < depth; d++) {
                std::cout << '\t';
            }
            std::string nameBehavior = (tree->behavior.empty())?"":" Behavior";
            std::string nameResponse = (tree->response.empty())?"":" Response";
            std::cout << "-" << tree->behavior << nameBehavior+tree->response+nameResponse << '\n';
            for (auto &i : *tree->pointChildren) {
                itterateNTree(&i, pointVector, depth + 1);
            }
        }
    }
    void printTree(point *tree) {
        std::vector<std::string> pointVector;
        itterateNTree(tree, pointVector, 0);
    }

    point *breadthFirstSearch(point *tree, std::string &searchTerm) {
        std::queue<point*> queue;
        point *innerTree;
        if (tree->pointChildren->size() != 0) {
            queue.push(tree);
        }
        while (!queue.empty()) {
            innerTree = queue.front();
            if (innerTree->behavior == searchTerm) {
                return innerTree;
            }
            queue.pop();

            for (auto &i : *innerTree->pointChildren) {
                queue.push(&i);
            }
        }
        return NULL;
    }

    point *breadthFirstSearch(std::string &searchTerm) {
        return breadthFirstSearch(getRoot(), searchTerm);
    }

    //get all points with search value are found
    void dfsALL(point *tree, std::string &searchValue,std::vector<point*> *ptr) {
        if (tree != NULL) {
            if (tree->behavior == searchValue) {
                ptr->push_back(tree);
            }
            for (auto &i : *tree->pointChildren) {
                dfsALL(&i, searchValue,ptr);
            }
        }
    }

    //Stop recursion when point searched for is found
    point * dfs(point *tree, std::string &searchValue) {
        if (tree->behavior == searchValue) {
            return tree;
        }
        point *t;
        for (auto &i : *tree->pointChildren) {
            t = dfs(&i, searchValue);
            if (t == NULL) {
                continue;
            }
            if (t->behavior == searchValue) {
                return t;
            }     
        }
        return NULL;
    }


    point *depthFirstSearch(std::string &searchTerm) {
        return dfs(getRoot(), searchTerm);
    }

    std::vector<point*> *depthFirstSearchAll (std::string &searchTerm) {
        std::vector<point*> *ptr = new std::vector<point*>();       
        dfsALL(getRoot(), searchTerm,ptr);
        return ptr;
    }

    inline point *getRoot() {
        return root;
    }
private:
    point *root = new point();
};