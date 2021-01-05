#pragma once


class SmartString
{
private:
    char* text;
    int length;  //Note that in the program, length variable gives the length of the character array without including
                 //the null terminator. However, null terminator is automatically always added and accounted for when
                 //calling helper functions like Join, Copytext etc.
    int CalculateTextLength(const char*);      //Calculates length of text
    void CopyText( char*, const char*);        //Copies one char array to another
public:
    SmartString();                                  //Constructor
    ~SmartString();                                 //Destructor
    SmartString(const SmartString&);                //Copy constructor
    SmartString(const char*);                       //Overloaded constructor
    void Join(const SmartString&);                  //Join text in another object
    void Join(const char*);                         //Join text in an array
    SmartString operator+(const SmartString&);      //return a SmartString by combining with a SmartString
    SmartString operator+(const char*);             //return a SmartString by combining with an array
    SmartString& operator=(const SmartString&);     //putting the value of one SmartString into another
    SmartString& operator=(const char*);            //putting the value of a character array into a SmartString
    SmartString& operator += (const SmartString&);  //Appending the same SmartString with another SmartString
    SmartString& operator += (const char* );        //Appending the same SmartString with a char array
    bool operator==(const SmartString& );           //Equating two SmartString together
    bool operator==(const char* );                  //Equating a SmartString and a char array

    int Length();   //Return Length
    void Show();    //Show content of SmartString
};
