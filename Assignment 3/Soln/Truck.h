#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "Box.h"
#pragma once

using namespace std;


class Truck
{
    private:
        char driver[32];
        float petrol;
        float money;
        float full_mileage;
        float empty_mileage;
        int num_box;
        Box* box_array = NULL;
        FILE* output_pointer = NULL;
        float litres_needed;
        bool journey_possible;
        float expenditure;
        float journey_cost;

    public:
        Truck();
        void SetPointer(FILE*);         //Set value of output file pointer
        ~Truck();                       //Deletes box array stored in the truck
        void SetDriver(char [], int);
        void SetPetrol(float);
        void SetMoney(float);
        void SetEmptyMileage(float);
        void SetFullMileage(float);
        string GetDriver();
        float GetPetrol();
        float GetMoney();
        float GetEmptyMileage();
        float GetFullMileage();
        void Load(int);                 //Loads boxes into the truck
        void Unload();                  //Unloads boxes off the truck
        int GetBoxQty();                //Generates random number of boxes b/w 12 and 20
        void SetExpenditure();          //Determines cost for filling petrol tank
        void SetJourneyCost();          //Determines cost for petrol consumed during journey
        float GetExpenditure();
        float GetJourneyCost();
        bool GetJourneyPossible();      //Returns true if the journey is possible
        float GetLitresNeeded();        //Returns litres needed to complete the journey

};

