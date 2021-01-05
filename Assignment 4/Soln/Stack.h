#pragma once
#include"SDL.h"
#include"Shape.h"
#include"Node.h"


class Stack
{
private:
    Node* head;     //Points towards the object at the top of the stack
    Node* pos;      //Points towards the most recently drawn object. Useful for plus/minus operations

public:
    Stack();
    ~Stack();
    void Append(Shape*);
    void SetPos(bool);
    Shape* Pop();
    bool IsEmpty();
    void MoveDeep();
    void MoveOut();
    void Delete();
    void DrawAll(SDL_Renderer*);
};
