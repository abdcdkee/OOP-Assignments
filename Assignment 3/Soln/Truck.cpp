#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

#include "Truck.h"
#include "Box.h"

using namespace std;


Truck::Truck()
{
    num_box = rand()%9 + 12;
    box_array = new Box[num_box];               //Generates box array of random size b/w 12 and 20
}


void Truck::SetPointer(FILE* temp)              //Sets value of pointer pointing to 'Details.txt' as temp
{
    output_pointer = temp;
}


Truck::~Truck()
{
    delete [] box_array;                        //Deallocates box array when truck is destroyed
                                                //(Can also achieve same effect by deleting in Unload function)
    box_array = NULL;
}


void Truck::SetDriver(char input[], int length)
{
    int i=0;
    while (input[i]!='\0')
    {
        driver[i] = input[i];
        i+=1;
    }
}


void Truck::SetPetrol(float input)
{
    petrol = input;
}


void Truck::SetMoney(float input)
{
    money = input;
}


void Truck::SetEmptyMileage(float input)
{
    empty_mileage = input;
}


void Truck::SetFullMileage(float input)
{
    full_mileage = input;
}


string Truck::GetDriver()
{
    return string(driver);
}


float Truck::GetPetrol()
{
    return petrol;
}


float Truck::GetMoney()
{
    return money;
}


float Truck::GetEmptyMileage()
{
    return empty_mileage;
}


float Truck::GetFullMileage()
{
    return full_mileage;
}


int Truck::GetBoxQty()
{
    return num_box;
}


void Truck::Load(int num_box)
    /*Loads boxes onto the truck and displays dimensions of each box*/
{
    stringstream temp1;
    temp1<<num_box;
    string temp_str = "Total " + temp1.str() + " Packages are being Loaded.\n\nLOADING PACKAGES............\n";

    for (int i=0; i<num_box; i++)
    {
        stringstream temp2;
        temp2<<i+1;
        string temp3 = box_array[i].GetDimensions();
        temp_str = temp_str + "Package " + temp2.str() + " has Volume: " + temp3 + " inches.\n";

    }

    temp_str = temp_str + "PACKAGES HAVE BEEN LOADED............\n\n";
    char duff[temp_str.length()+1];
    strcpy(duff, temp_str.c_str());
    fwrite(duff, 1, temp_str.length(), output_pointer);       //Writes to the file 'Details.txt'
}


void Truck::Unload()
    /*Unloads boxes from the truck in reverse of the order of loading and displays dimensions of each box*/
{
    petrol = petrol - litres_needed;
    string temp_str = "Delivery Truck has Reached the Destination.\n\nUNLOADING PACKAGES............\n";

    for (int i=num_box-1; i>=0; i--)
    {
        stringstream temp1;
        temp1<<i+1;
        string temp2 = box_array[i].GetDimensions();
        temp_str = temp_str + "Package " + temp1.str() + " has Dimensions: " + temp2 + " inches.\n";

    }

    temp_str = temp_str + "PACKAGES HAVE BEEN UNLOADED............\n\n";
    char duff[temp_str.length()+1];
    strcpy(duff, temp_str.c_str());
    fwrite(duff, 1, temp_str.length(), output_pointer);     //Writes to file 'Details.txt'
}


void Truck::SetExpenditure()
    /*Determines expenditure i.e. money required to fill the petrol tank*/
{
    int capacity = 50;                               //Max capacity of petrol tank
    float distance = 60;
    litres_needed = distance/(float)full_mileage + distance/(float)empty_mileage;
    float extra_litres = capacity - petrol;          //Stores litres required to fill tank

    if (extra_litres>0)
    {
        expenditure = extra_litres*2.73;             //Stores amount required to fill petrol
        if (expenditure < money)
        {
            petrol = 50;
            money = money - expenditure;             //Decrements money by expenditure amount
            journey_possible = true;
        }
        else
        {
            journey_possible = false;
        }
    }
}


bool Truck::GetJourneyPossible()
{
    return journey_possible;
}


void Truck::SetJourneyCost()
    /*Determines cost of the litres of fuel consumed during the journey*/
{
    journey_cost = litres_needed*2.73;
}


float Truck::GetExpenditure()
    /*Returns amount of money spent to fill the petrol tank*/
{
    return expenditure;
}


float Truck::GetJourneyCost()
    /*Returns cost of the litres of fuel consumed during the journey*/
{
    return journey_cost;
}


float Truck::GetLitresNeeded()
    /*Returns litres of fuel consumed in the journey*/
{
    return litres_needed;
}


