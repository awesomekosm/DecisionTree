#pragma once
#include <random>
#include "tree.h"

class Randomizer
{
public:
    Randomizer();
    std::string getResponse(Tree *tree, std::string &str, std::string &searchType);
    ~Randomizer();
private:
    std::random_device rd;
    //internal function to drill through the tree until last branch
    std::string response(Tree::point *point);
    inline uint32_t getRandom(uint32_t from, uint32_t to) {
        std::mt19937 generate(rd());
        std::uniform_real_distribution<double> dist(from, to);;
        return dist(generate);
    }
};

