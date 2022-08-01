#pragma once
#include "Beatmap.h"

//this is used to have a node to store the non-beatmap
//connector nodes along with the beatmap nodes
struct GraphNode
{
    private:
        std::string name;
        Beatmap* bm = nullptr;
    public:
        GraphNode();
        GraphNode(std::string n);
        GraphNode(std::string n, Beatmap* b);

        std::string getName();
        Beatmap* getBeatmap();
};

GraphNode::GraphNode()
{
    name = "";
    bm = nullptr;
}
GraphNode::GraphNode(std::string n)
{
    name = n;
    bm = nullptr;
}
GraphNode::GraphNode(std::string n, Beatmap* b)
{
    name = n;
    bm = b;
}
std::string GraphNode::getName()
{
    return name;
}
Beatmap* GraphNode::getBeatmap()
{
    return bm;
}

