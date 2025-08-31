#ifndef ZONE_H
#define ZONE_H
#include <iostream>
#include <vector>

class Zone{
    private:
        char type;
        int population;
        int pollution;
        int cordA, cordB; //Coordinates
        std::vector<Zone*> adjacent; //adjaceny list
   
    public:
        //constructors
        Zone();
        Zone(char type, int population, int pollution, int cordA, int cordB);
        
        //mutators
        void SetType(char type);
        void SetPopulation(int population);
        void SetPollution(int pollution);
        void SetCords(int cordA, int cordB);
        void SetAdjacency(std::vector<std::vector<Zone>> &region);
        
        //accessors
        char GetType();
        int GetPopulation();
        int GetPollution();
        void PrintPopulation();
        void PrintPollution();
        int GetCordA();
        int GetCordB();
        std::vector<Zone*> GetAdjacent();

        //assignment operator
        void operator = (const Zone &Z);

        //print function
        void Print();
};

#endif