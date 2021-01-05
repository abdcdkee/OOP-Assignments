#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <cstring>

#include <sstream>
#include <fstream>
#include "Box.h"
#include "Truck.h"

using namespace std;


/***Two important points. Firstly, instead of printing the output, the output has been written to a file called
'Details.txt' because the command prompt was simply unable to show all the data for the file in question, and would
certainly not work for bigger files. The conditions of the drivers has been updated and stored in 'Trip.txt'.
Secondly, I have used stringstream throughout the program. It might seem convoluted but the purpose of it is simply
to convert integers to strings; that are then converted to a character array; that is written by a file pointer to
the file 'Details.txt'. atoi() and other methods were not working for this.***/


int TruckCounter(char*);                            //Returns number of trucks that can make the journey
Truck* TruckAllocater(FILE*, FILE*, Truck*, int);   //Assigns attributes to objects in truck array after extracting from
                                                    //'Drivers.txt' file
void LoadDetails(FILE*, Truck&);                    //Displays Truck Details during loading
void UnloadDetails(FILE*, Truck&);                  //Displays Truck Details during unloading
void DisplayInitialDetails(FILE*, Truck&);          //Displays Details about initial conditions of the driver
void DisplayJourneyDetails(FILE*, Truck&);          //Displays Details of the journey like cost for filling tank etc.
void DisplayFinalDetails(FILE*, Truck&);            //Displays Details that were changed after the journey

void WriteToFile(Truck*, int);                      //Writes to the file 'Trip.txt'
bool JourneyPossible(float, float);                 //Returns true if the truck can make the journey


int main()
{
    srand(time(0));
    char file_name[32] = "Drivers.txt";
    int truck_qty = TruckCounter(file_name);    //Returns number of trucks that can successfully make the journey

    FILE* input_pointer = NULL;                   //Declaring a file pointer
    FILE* output_pointer = NULL;
    input_pointer = fopen("Drivers.txt", "r");    //Opening file as read only
    output_pointer = fopen("Details.txt", "w");   //Opening file as write only

    if (input_pointer == NULL)
    {
        perror ("Error opening file");
        return 0;
    }

    Truck* truck_array = NULL;
    truck_array = new Truck[truck_qty];                 //Generating dynamic truck array

    /*Note that the chunk of code below is used multiple times for writing into the file 'Details.txt'. Not commented
    details everywhere since that would be exceedingly redundant*/
    stringstream temp_int;                              //temp variable belonging to stringstream created
    temp_int<<truck_qty;                                //Assigns integer value to stringstream
    string temp_str = "There are " + temp_int.str() + " Delivery Trucks.\n\n\n\n";
    char duff[temp_str.length()+1];                     //duff is temporary char array that copies temp_str
    strcpy(duff, temp_str.c_str());                     //temp_str copied onto duff array
    fwrite(duff, 1, temp_str.length(), output_pointer); //duff is written to file

    truck_array = TruckAllocater(output_pointer, input_pointer, truck_array, truck_qty);

    fclose(input_pointer);                        //Closing file 'Drivers.txt'
    fclose(output_pointer);                       //Closing file 'Details.txt'
    WriteToFile(truck_array, truck_qty);          //Generates 'Trip.txt' file

    delete[] input_pointer;
    delete[] output_pointer;
    delete[] truck_array;
    truck_array = NULL;

    cout<<"'Trip.txt' has been successfully generated.\n\n";
    cout<<"'Details.txt' has also been generated. It has all the relevant details about drivers. Not printed on command prompt because it was unable to print all the data"<<endl;
}


int TruckCounter(char* file_name)
    /*Function returns number of trucks that can make the journey*/
{
    FILE* input_pointer;                        //Declaring a file pointer
    char buff[32];                              //Declaring a character array to store a line
    input_pointer = fopen(file_name, "r");      //Opening file as read only

    if (input_pointer == NULL)                  //If file is not found
    {
        perror ("Error opening file");          //Show Error
        return 0;
    }

    int truck_count = 0;                        //Counts the number of trucks that can make the journey
    int counter = 0;                            //Counts the lines in file
    int redundant_count = 0;                    //Counts the number of redundant trucks
    float temp_money = 0;                       //Stores money for each truck temporarily
    float temp_petrol = 0;                      //Stores petrol for each truck temporarily

    while(fgets(buff, 32, (FILE*)input_pointer) !=NULL)                     //If line read is not NULL
    {
        if ((counter-(truck_count+redundant_count)*5+1) == 2)               //Accesses petrol of a given truck
            temp_petrol = atoi(buff);
        if ((counter-(truck_count+redundant_count)*5) == 2)                 //Accesses money of a given truck driver
            temp_money = atoi(buff);

        counter++;

        if (counter%5==0 && counter!=0)                   //Increments number of trucks
        {
            if (JourneyPossible(temp_money,temp_petrol))
            {
                truck_count = truck_count+1;
                temp_money=0;
                temp_petrol=0;
            }
            else
            {
                redundant_count = redundant_count +1;       //Increments when truck is unable to make the journey
                temp_money=0;
                temp_petrol=0;
            }
        }
    }
    return truck_count;                                     //return line count
}


Truck* TruckAllocater(FILE* output_pointer, FILE* input_pointer, Truck* truck_array, int truck_qty)
    /*Function allocates attributes to truck objects in truck array*/
{
    char temp_driver[32];                             //Declaring a character array to store a line
    char temp_petrol[32];
    char temp_money[32];
    char temp_full[32];
    char temp_empt[32];

    int i=0;                                          //Keeps track of trucks in the array
    while (i<truck_qty)
    {
        truck_array[i].SetPointer(output_pointer);

        fgets(temp_driver, 32, (FILE*)input_pointer);
        fgets(temp_petrol, 32, (FILE*)input_pointer);
        fgets(temp_money, 32, (FILE*)input_pointer);
        fgets(temp_full, 32, (FILE*)input_pointer);
        fgets(temp_empt, 32, (FILE*)input_pointer);

        if (JourneyPossible(atoi(temp_money), atoi(temp_petrol)))       //Conditional creates truck object when truck can
                                                                        //complete journey
        {
            truck_array[i].SetDriver(temp_driver, sizeof(temp_driver));
            truck_array[i].SetPetrol(atoi(temp_petrol));
            truck_array[i].SetMoney(atoi(temp_money));
            truck_array[i].SetFullMileage(atoi(temp_full));
            truck_array[i].SetEmptyMileage(atoi(temp_empt));

            LoadDetails(output_pointer, truck_array[i]);                //Loads boxes onto the trucks and displays
        }
        else
        {
            i = i-1;
        }
        i++;
    }
    for (int k=0; k<truck_qty; k++)
    {
        UnloadDetails(output_pointer, truck_array[k]);                  //Unloads boxes from the truck and displays as such
    }
    return truck_array;
}


void LoadDetails(FILE* output_pointer, Truck& truck)
{
    int box_qty = truck.GetBoxQty();

    string temp_str = "------------------------------------------------------------\nDelivery Truck Driver is: "
    + truck.GetDriver() + "\n";
    char buff[temp_str.length()+1];
    strcpy(buff, temp_str.c_str());
    fwrite(buff, 1, temp_str.length(), output_pointer);

    DisplayInitialDetails(output_pointer, truck);
    truck.SetExpenditure();
    truck.SetJourneyCost();
    DisplayJourneyDetails(output_pointer, truck);

    if (truck.GetJourneyPossible())
    {
        truck.Load (box_qty);
    }
}


void UnloadDetails(FILE* output_pointer, Truck& truck)
{
    string temp_str = "***************************************************************\nDelivery Truck Driver is: "
    + truck.GetDriver() + "\n";
    char buff[temp_str.length()+1];
    strcpy(buff, temp_str.c_str());
    fwrite(buff, 1, temp_str.length(), output_pointer);

    if (truck.GetJourneyPossible())
    {
        truck.Unload();
        DisplayFinalDetails(output_pointer, truck);
    }
}


void DisplayInitialDetails(FILE* output_pointer, Truck& truck)
{
    stringstream temp1, temp2, temp3, temp4;
    temp1<<truck.GetPetrol();
    temp2<<truck.GetMoney();
    temp3<<truck.GetFullMileage();
    temp4<<truck.GetEmptyMileage();
    string temp_str = "Delivery Truck Petrol is: " + temp1.str() + "\nDelivery Truck Driver's Funds are: " + temp2.str() +
    "\nDelivery Truck Coverage (Full Mileage): " + temp3.str() + "\nDelivery Truck Coverage (Empty Mileage): " + temp4.str() + "\n\n";
    char duff[temp_str.length()+1];
    strcpy(duff, temp_str.c_str());
    fwrite(duff, 1, temp_str.length(), output_pointer);
}


void DisplayFinalDetails(FILE* output_pointer, Truck& truck)
{
    stringstream temp1, temp2;
    temp1<<truck.GetLitresNeeded();
    temp2<<truck.GetJourneyCost();
    string temp_str = "\nThe petrol used during the journey is: " + temp1.str() + "\nThe cost for the journey was: "
    + temp2.str() + ".\n\n\n\n";
    char duff[temp_str.length()+1];
    strcpy(duff, temp_str.c_str());
    fwrite(duff, 1, temp_str.length(), output_pointer);
}


void DisplayJourneyDetails(FILE* output_pointer, Truck& truck)
{
    stringstream temp1, temp2;
    temp1<<truck.GetExpenditure();
    string temp_str = "Cost for filling Petrol tank is: " + temp1.str() + "\n";
    char duff[temp_str.length()+1];
    strcpy(duff, temp_str.c_str());
    fwrite(duff, 1, temp_str.length(), output_pointer);

    if (truck.GetJourneyPossible())
    {
        temp2<<truck.GetMoney();
        temp_str = "Driver's Remaining Funds are: " + temp2.str() +"\nDelivery Truck is able to go for its journey. \n\n";
        char duff[temp_str.length()+1];
        strcpy(duff, temp_str.c_str());
        fwrite(duff, 1, temp_str.length(), output_pointer);
    }
}


bool JourneyPossible(float money, float petrol)
    /*Returns true if fuel tank can be filled*/
{
    if(((50-petrol)*2.73)<=money)
        return true;
    else
        return false;
}


void WriteToFile(Truck* truck_array, int truck_qty)
    /*Function writes to file 'Trip.txt'*/
{
    ofstream myfile;
    myfile.open("Trip.txt");
    for (int i=0; i<truck_qty; i++)
    {
        myfile<<"Driver: "<<truck_array[i].GetDriver();
        myfile<<"Fuel: "<<truck_array[i].GetPetrol()<<endl;
        myfile<<"Money: "<<truck_array[i].GetMoney()<<endl;
        myfile<<"Full Mileage: "<<truck_array[i].GetFullMileage()<<endl;
        myfile<<"Empty Mileage: "<<truck_array[i].GetEmptyMileage()<<endl;
    }
    myfile.close();
}
