#include "randomizer.h"



Randomizer::Randomizer()
{
}

std::string Randomizer::response(Tree::point *point) {
    std::string finalResult = point->response;
    if (point->pointChildren->size() != 0) {
        uint32_t temp = getRandom(0, point->pointChildren->size());
        Tree::point *tempPoint = &point->pointChildren->at(temp);
        return response(tempPoint);
    }
    return finalResult;
}

//Method selects which search to use, breadthfirst or depth first and returns a value
//Answer will have lower chance of probability the more generic the behavior(search term in the tree)
std::string Randomizer::getResponse(Tree * tree, std::string & term, std::string &searchType){
    std::string resultString = "";
    Tree::point *resultPoint;
    if (searchType == "depthFirstSearch") {
        resultPoint = tree->depthFirstSearch(term);
        if (resultPoint == NULL) {
            resultPoint = tree->depthFirstSearch(std::string("root"));
        }
        resultString = response(resultPoint);
    }
    else if (searchType == "breadthFirstSearch") {
        resultPoint = tree->breadthFirstSearch(term);
        if (resultPoint == NULL) {
            resultPoint = tree->breadthFirstSearch(std::string("root"));
        }
        resultString = response(resultPoint);
    }
    else {
        resultString = "\nNo such search type exists\n";
    }
    return resultString;
}


Randomizer::~Randomizer()
{
}
