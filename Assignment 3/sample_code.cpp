#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///REMEMBER TO CLOSE FILESS!@!t123TDAS\
//REMEMBER TO USE CLASSES/STRUCTURES AS REQUIRED

using namespace std;

int BoxQty();

struct Box
{
    int length;
    int width;
    int height;

    Box()
    {
        int box_qty = rand()%26+5;
        length = width = height = box_qty;
    }


    int Volume()
    {
        return length*width*height;
    }
};

struct Truck
{
    char driver[32];
    float petrol;
    float money;
    int fullMileage;
    int emptyMileage;
    int numBox;
    float litresNeeded;
    float cost;
    bool journeyPossible;

    Box* Load()
    {
        cout<<"\nConcerning the driver: "<<driver<<endl;
        cout<<"The dimensions of the loaded boxes are: ";
        Box* boxArray = new Box[numBox]; //array of boxes initialized
        for (int i=0; i<numBox-1; i++)
        {
            //boxArray[i];                //cout<<boxArray[i].width<<endl;
            cout<<boxArray[i].width<<", ";
        }
        cout<<boxArray[numBox-1].width;
        cout<<endl<<endl;
        return boxArray;
    }


    void Unload(Box* boxArray)
    {
        if (journeyPossible==true)
        {
            cout<<"The volumes of the unloaded boxes are: ";
            petrol = petrol - litresNeeded;
            money = money - cost;
            for (int i=0; i<numBox-1; i++)
            {
                cout<<boxArray[i].Volume()<<", ";
            }
            cout<<boxArray[numBox-1].Volume();
            cout<<endl;
        }
    }

    float Cost()
    {
        int travelDistance = 60;
        litresNeeded = (float)travelDistance/(float)fullMileage + (float)travelDistance/(float)emptyMileage;
        float extraLitres = litresNeeded - petrol;
        journeyPossible = true;
        if (litresNeeded > petrol)
        {
            cost = extraLitres*2.73;
            if (cost < money)
            {
                petrol = petrol + extraLitres;
            }
            else
            {
                journeyPossible = false;
            }
        }
        /*if (litresLeft < 0)
        {
            litresLeft = litresLeft*-1; //Done to change negative valuye to positiove
        }*/
    }
    TruckDetails()
    {
        if (journeyPossible==true)
        {
            cout<<"\nThe cost incurred by the driver was: "<<cost<<endl;
            cout<<"The money left after trip was: "<<money<<endl; ///CHECK IF FLOAT REQD HERE
            cout<<"The litres needed for the journey were: "<<litresNeeded<<endl;
            cout<<"The litres of petrol left in the truck are: "<<petrol<<endl<<endl<<endl<<endl;
        }
        else
        {
            cout<<"Unfortunately, this driver can not make the journey :( \n\n\n\n";
        }
    }

};



void TruckAllocater(FILE*, Truck*, int);


int BoxQty()
{
    while (true)
    {
        int random = rand()%21;
        if (random > 11)
        {
            return random;
        }
    }
}



int LineCounter(char* fileName)
{
    FILE* filePointer;                          //Declaring a file pointer
    char buff[32];                              //Declaring a character array to store a line

    filePointer = fopen(fileName, "r");         //Opening file as read only

    if (filePointer == NULL)                    //If file is not found
    {
        perror ("Error opening file");          //Show Error
        return 0;
    }

    int counter = 0;                            //Counts the lines in file

    while(fgets(buff, 32, (FILE*)filePointer) !=NULL)   //If line read is not NULL
    {
        counter++;                                      //increase line count
    }
    fclose(filePointer);                                //close file when done
    return counter;                                     //return line count
}


int main()
{
    srand(time(0));
    char fileName[32] = "Drivers.txt"; //Changes mode to avoid 'deprecated: ...' error in the original file
    int truckQty = LineCounter(fileName)/5;

    FILE* filePointer;                          //Declaring a file pointer

    filePointer = fopen("Drivers.txt", "r");    //Opening file as read only

    if (filePointer == NULL)
    {
        perror ("Error opening file");
        return 0;
    }
    Truck* truckArray = new Truck[truckQty];
    TruckAllocater(filePointer, truckArray, truckQty);

    fclose(filePointer);                        //Closing file


    delete truckArray;
    return 0;
}


void TruckAllocater(FILE* filePointer, Truck* truckArray, int truckQty)
{
    char buff[32];                              //Declaring a character array to store a line

    for (int i=0; i<truckQty; i++)
    {
        truckArray[i].numBox = BoxQty();

        fgets(truckArray[i].driver, 32, (FILE*)filePointer); //Reading the name of the driver directly

        fgets(buff, 32, (FILE*)filePointer);        //Reading the next line as string
        truckArray[i].petrol = atoi(buff);                   //Converting the string to integer

        fgets(buff, 32, (FILE*)filePointer); ///SET FUNCTION TO INPUT QTY INDIVIDUALLY
        ///Use GET to print out.
        truckArray[i].money = atoi(buff);

        fgets(buff, 32, (FILE*)filePointer);
        truckArray[i].fullMileage = atoi(buff);

        fgets(buff, 32, (FILE*)filePointer);
        truckArray[i].emptyMileage = atoi(buff);

        Box* boxArray;
        boxArray = truckArray[i].Load();
        truckArray[i].Cost();
        truckArray[i].Unload(boxArray);
        truckArray[i].TruckDetails();
        delete boxArray;
    }
    //cout<<truckArray[0].Cost();

}

