#include "Stack.h"
#include "Node.h"


Stack::Stack()
{
    head = NULL;
    pos = NULL;
}

Stack::~Stack()
{
    while(head != NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = NULL;
    pos = NULL;
}

//Pushes a value on to the top of the stack
void Stack::Append(Shape* shape)
{
    if (head==NULL)
    {
        head = new Node;
        head -> next = NULL;
        head -> fig = shape;
    }
    else
    {
        Node* temp = head;
        head = new Node;
        head->fig = shape;
        head->next = temp;
    }
}

//Sets value of Pos pointer that points towards last drawn element.
//However, once the last drawn element has been popped from the stack,
//it will point towards the element at the top of the stack as required.
//Is called whenever element appended to buildstack.
void Stack::SetPos(bool temp)
{
    if (temp)
        pos = head;
}

//Removes topmost element of stack and returns its Shape pointer
Shape* Stack::Pop()
{
    Shape* value = NULL;

    if (head!=NULL)
    {
        if (pos==head)
            pos = head->next;
        Node* temp = head;
        value = head->fig;
        head = head->next;

        delete temp;
    }

    return value;
}

//Returns true if stack is empty
bool Stack::IsEmpty()
{
    if (head==NULL)
        return true;
    return false;
}

//Moves most recently drawn object deeper into the stack. Activates with '-' key.
void Stack::MoveDeep()
{
    Shape* tempShape = pos->fig;

    if (pos->next!=NULL)
    {
        pos->fig = pos->next->fig;
        pos->next->fig = tempShape;
        pos = pos->next;
    }
}

//Moves most recently drawn object towards the top of the stack. Activates with '+' key.
void Stack::MoveOut()
{
    Node* temp = head;
    Node* tempOut =NULL;
    Shape* tempShape = pos->fig;

    if (pos!=head)
    {
        while (temp!=pos)
        {
            tempOut = temp;
            temp = temp->next;
        }
        pos->fig = tempOut->fig;
        tempOut->fig = tempShape;
        pos = tempOut;
    }
}

//Deletes the entire stack and deallocates memory
void Stack::Delete()
{
    Node* temp;

    while (head!=NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }

    head=NULL;
    pos = NULL;
}

//Renders all objects in stack on screen such that the element on top of stack is at the very back on the screen
void Stack::DrawAll(SDL_Renderer* gRenderer)
{
    Node* temp  = head;

    while (temp!=NULL)
    {
        temp->fig->Draw(gRenderer);
        temp = temp->next;
    }
}
