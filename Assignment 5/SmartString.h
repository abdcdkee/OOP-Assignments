class SmartString
{
private:
    char* text;
    int length;
    int CalculateTextLength(const char*);       //Calculates length of text
    void CopyText( char* dest, const char* src);//Copies one char array to another
public:
    SmartString();  //Constructor
    ~SmartString(); //Destructor
    SmartString(const SmartString&);    //Copy constructor
    SmartString(const char*);           //Overloaded constructor
    void Join(const SmartString&);      //Join text in another object
    void Join(const char*);             //Join text in an array
    SmartString operator+(const SmartString&);  //return a SmartString by combining with a SmartString
    SmartString operator+(const char*);         //return a SmartString by combining with an array
    SmartString& operator=(const SmartString&); //putting the value of one SmartString into another
    SmartString& operator=(const char*);        //putting the value of a character array into a SmartString
    SmartString& operator += (const SmartString&);  //Appending the same SmartString with another SmartString
    SmartString& operator += (const char* );        //Appending the same SmartString with a char array
    bool operator==(const SmartString& );   //Equating two SmartString together
    bool operator==(const char* );          //Equating a SmartString and a char array

    int Length();   //Return Length
    void Show();    //Show content of SmartString
};
