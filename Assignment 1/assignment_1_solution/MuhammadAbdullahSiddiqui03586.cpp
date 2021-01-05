#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

const double PI = 3.14159265; //Pi value is generated for usage in Sin function

void graph_maker();
bool check_for_integer(char value);
void display_output(long long integer_array[], int integer_array_index, char character_array[], int character_array_index);
void separate(char expression[], int expression_length);
/*All the functions that are being called in the program have been defined above*/


int main()
{
    graph_maker();                                   //Function Call for Task1

    char expression[] = "24*356+489*5/45*54";        //Input expression converted to Array named 'expression'
    int expression_length = sizeof(expression) - 1;  //Expression length is stored, Subtracting 1 accounts for the Null terminator at the
                                                     //end of the array
    separate(expression, expression_length);         //Function Call for Task2
    return 0;
}

/////////////////////////////////////START TASK #1///////////////////////////////////////////////////////////

void graph_maker()
    /*Function prints a a Sin graph onto a file using the Sin function*/
{
  ofstream myfile;                      //Introduces Output File Stream (VA)
  myfile.open("requiredGraph.txt");     //Generates File in destination folder.
  double radian;                        //Represents the Radian value which is produced from a given degree value
  float degree;                         //Represents degrees for the Sine curve from 1 to 360
  int initial_count;                    //Stores a magnified value of the Radian
  int space_count=0;                    //Represents the number of spaces before an asterisk for any given line
  for (degree=0; degree<360; degree++)  //Iterates 360 degrees i.e. one complete Sine wave
  {
    radian = sin(degree*(PI/180));      //Formula converts degree to radian
    initial_count = radian*52;          //Initial_count i.e. magnified version of radian value is generated
    space_count = initial_count + 52;   //Initial space count has been generated.
                                        //Note that 52 is added so that the Sine curve begins from the middle of the screen and not the Left.
                                        //This achieves outputting a Sine curve that seems to start and end at an imaginary vertical axis.
    for (int i=0; i<space_count; i++)   //local variable i serves to print number of spaces before an asterisk for any given line.
    {
      myfile<<" ";
    }
    myfile<<"*\n";                      //prints asterisk on each line.
  }
}

//////////////////////////////////////END TASK #1////////////////////////////////////////////////////////////

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////START TASK #2///////////////////////////////////////////////////////////

bool check_for_integer(char value)
    /*Function returns true if the input 'value' is an integer*/
{
    int ASCII_value = int(value);
    if (ASCII_value >=48 && ASCII_value <= 57) //ASCII table range for integers is used to check whether value is an integer
    {
        return true;
    }
    else
    {
        return false;                          //Returns false if the 'value' is an operator
    }
}


void display_output(long long integer_array[], int integer_array_index, char character_array[], int character_array_index)
    /*Function displays output of integer array and character array*/
{
    cout<<"operands: ";
    for (int i=0; i<integer_array_index; i++)                       //Loop to iterate over the elements of the integer array
    {
        cout<<integer_array[i]<<" ";                                //Prints each element stored in the integer array
    }
    cout<<"\n\noperators: ";
    for (int j=0; j<character_array_index; j++)                     //Loop to iterate over the elements of the character array
    {
        cout<<character_array[j]<<" ";                              //Prints each elemeent stored in the character array
    }
}


void separate(char expression[], int expression_length)
    /*Function seperates a given mathematical expression into two arrays containing operators and operands*/
{
    char store_characters[64];                              //Character array that can store 64 elements is generated
    long long store_integers[64];                           //Integer Array generated that can store 64 elements. Max size of each element that
                                                            //can be stored is long long

    int store_integers_index = 0;                           //Index to iterate over Integer array generated
    int store_characters_index = 0;                         //Index to iterate over Character array is generated

    for (int i=0; i<expression_length; i++)                 //Loop iterates over 'expression' array checking each element
    {
        bool condition_satisfied = true;                    //Bool condition for the nested while loop is initiated.1
        if (check_for_integer(expression[i])==true)         //Checks if the element is an integer
        {
            long long store_temporary = 0;
            store_temporary = expression[i] - 48;           //Converts character type value stored in array to integer value.
            while (condition_satisfied)
            /*  Loop checks the elements immediately after the integer and joins
             *  any consecutive suceeding integers into one multi-digit integer*/
            {
                i++;
                if (check_for_integer(expression[i])==true) //Function call checks if the element is an integer
                {
                    store_temporary = store_temporary*10 + (expression[i] - 48); //Command joins two integer values for one multi-digit
                                                                                 //e.g. "2*10 + 4 = 24"
                }
                else
                {
                    i--;                                    //Index decreased so that for loop can check and store the operator in the character
                                                            //integer during the next iteration
                    condition_satisfied = false;            //Nested while loop breaks if the element is an operator
                }
            }
            store_integers[store_integers_index] = store_temporary; //Integer added to the store_integers array
            store_integers_index++;                                 //Index for the integer array is incremented
        }
        else //Program goes into this condition when the element in the 'expression' array is an operator
        {
            store_characters[store_characters_index] = expression[i]; //Operator added to the character array
            store_characters_index++;                                 //Integer for character array is incremented
        }
    }
    store_characters[store_characters_index] = '\0';        //Adds Null terminator as the last term of the store_characters array
    /*Function below is called to print both integer and character arrays and display the output*/
    display_output(store_integers, store_integers_index, store_characters, store_characters_index);
}

//////////////////////////////////////END TASK #2////////////////////////////////////////////////////////////






