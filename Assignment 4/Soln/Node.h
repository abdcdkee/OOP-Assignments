#pragma once
#include"SDL.h"
#include"Shape.h"


struct Node
{
    Shape* fig = NULL;      //Points towards Shape object (either Line or Rectangle)
    Node* next = NULL;      //Points towards the next node in the stack
};
