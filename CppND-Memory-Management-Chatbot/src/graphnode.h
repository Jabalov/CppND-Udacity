#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>
#include "chatbot.h"

using namespace std;

class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////
    // data handles (owned)
    // convert to unique ptr
    // vector<GraphEdge *> _childEdges;  // edges to subsequent nodes
    vector<unique_ptr<GraphEdge>> _childEdges;

    // data handles (not owned)
    vector<GraphEdge *> _parentEdges; // edges to preceding nodes
    ChatBot _chatBot;

    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    vector<string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    vector<string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _parentEdges.size(); }

    // proprietary functions
    void AddToken(string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    // void AddEdgeToChildNode(GraphEdge *edge);
    void AddEdgeToChildNode(unique_ptr<GraphEdge> edge);

    //// STUDENT CODE
    ////
    void MoveChatbotHere(ChatBot chatbot);
    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */