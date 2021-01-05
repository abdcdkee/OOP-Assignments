#include <iostream>
#include "SmartString.h"

using namespace std;

SmartString::SmartString()  //Constructor
{
    text = NULL;
    length = 0;
}

SmartString::~SmartString() //Destructor
{
    if (text!=NULL)
        delete[] text;
    text = NULL;
}

int SmartString::CalculateTextLength(const char* temp)       //Calculates length of text
{
    if (temp==NULL) //Returns -1 if temp is empty
        return -1;
    int index = 0;  //Keeps track of the null terminator in an array
    int len = 0;    //Keeps track of length of character array temp
    while(temp[index]!='\0')
    {
        len++;
        index++;
    }
    return len;
}

void SmartString::CopyText(char* dest, const char* src) //Copies one char array to another
{
    if (src!=NULL)
    {
        int tempLength = CalculateTextLength(src);
        for(int i=0; i<=tempLength; i++)        //<= ensures that the null terminator is also copied onto dest
        {
            *(dest+i) = *(src+i);               //Utilizes pointer arithmetic
        }
    }

}

SmartString::SmartString(const SmartString& src)    //Copy constructor
{
    length = src.length;
    this->text = new char[length+1];   //Char array of length: length+1 intitialized to store null terminator as well
    CopyText(this->text, src.text);
}

SmartString::SmartString(const char* src)          //Overloaded constructor
{
    length = CalculateTextLength(src);
    text = new char[length+1];         //Char array of length: length+1 intitialized to store null terminator as well
    CopyText(this->text, src);
}

void SmartString::Join(const SmartString& src)    //Join text in another object
{
    this->Join(src.text);    //Calls the Join function defined below i.e. the one which takes char array as input
}

void SmartString::Join(const char* src)           //Join text in an array
{
    char* temp = text;
    int srcLength = CalculateTextLength(src);
    int tempLength = length;
    length += srcLength;    //length of original text and src added without adding the positions of the null terminator
    text = new char[length+1];      //Char array of length: length+1 intitialized to store null terminator as well

    if (temp!=NULL)     //Condition ensures that if the original text array is empty, Join function will simply copy
                        //the input character array onto the text char array. This allows Join to be called when
                        //defining the plus operator directly, instead of defining a dynamic array and then calling
                        //CopyText function
        CopyText(text, temp);

    CopyText(&(text[tempLength]), src); //Utilizes pointer arithmetic. Copies the input array onto text from the
                                        //index where values of temp end i.e. &text[tempLength]
}

SmartString SmartString::operator+(const SmartString& src)  //return a SmartString by combining with a SmartString
{
    return (*this + src.text);  //Calls the operator+ function that takes char array as input defined below
                                //Note that function will return a separate SmartString without changing the original
}

SmartString SmartString::operator+(const char* src)         //return a SmartString by combining with an array
{
    SmartString temp(this->text);       //Temporary SmartString created using overloaded constructor
    temp.Join(src);    //Essentially copies the char array src onto the empty text char array in temp
    return temp;       //Returns temp. No change to original SmartString is made
}

SmartString& SmartString::operator=(const SmartString& src) //putting the value of one SmartString into another
{
    *this=src.text; //operator= function defined below taking char array input is called
    return *this;   //Function changes value of the SmartString and returns the new value
}

SmartString& SmartString::operator=(const char* src)  //putting the value of a character array into a SmartString
{
    if (text!=NULL) //Any text stored in the SmartString beforehand is deallocated
    {
        delete[] text;
        text = NULL;
        length = 0;
    }
    this->Join(src);    //char array src is copied onto the now empty text char array
    return *this;       //SmartString is returned after having its attributes changed appropriately
}

SmartString& SmartString::operator += (const SmartString& src)  //Appending the same SmartString with another SmartString
{
    this->Join(src);    //Calls Join function that takes SmartString inputs.
                        //Join function subsequently copies src.text onto this->text
    return *this;       //Returns SmartString after changing its attributes
}

SmartString& SmartString::operator += (const char* src)      //Appending the same SmartString with a char array
{
    this->Join(src);    //Calls Join function that takes char array inputs
                        //Join function subsequently copies src onto text
    return *this;       //Returns SmartString after changing its attributes
}

bool SmartString::operator==(const SmartString& src)  //Equating two SmartString together
{
    return (*this == src.text); //Calls the boolean function defined below
}

bool SmartString::operator==(const char* src)       //Equating a SmartString and a char array
{
    int tempLen = CalculateTextLength(src);

    if (this->length!=tempLen)  //Returns false if arrays not of equal lengths
        return false;
    else
    {
        for(int i=0; i<length; i++) //Checks if all elements of this->text and src are equal
        {
            if (this->text[i]!=src[i])
                return false;
        }
    }
    return true;
}

int SmartString::Length()   //Return Length
{
    return length;
}

void SmartString::Show()   //Show content of SmartString
{
    if (text!=NULL) //Prints value of SmartString if SmartString is not empty
    {
        cout<<"The length of the SmartString is as follows: "<<Length()<<endl;
        cout<<"The SmartString is as follows: ";
        for(int i=0; i<length; i++)
        {
            cout<<text[i];
        }
        cout<<endl;
    }
    else
    {
        cout<<"-1"<<endl;
    }
}
