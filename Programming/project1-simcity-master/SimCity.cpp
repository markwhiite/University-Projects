/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <utility>
#include<string>
#include <fstream>
using namespace std;
#include "Zone.h"
#include "Residential.h"
#include "Industrial.h"
#include "Commercial.h"
#include "Pollution.h"
//#include "globalFile.h"


//Print function to print out region map
void PrintFile(vector<vector<Zone>> region){
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			if(region[i][j].GetPopulation()==0)
				cout<<region[i][j].GetType()<< " ";
			else
				cout<<region[i][j].GetPopulation()<< " ";
		}
		cout<<endl;
	}
}

void initializeVectorMap(vector<vector<Zone>> &region, ifstream &fin); //initialize 2D vector of Zones
int TotalPollution(vector<vector<Zone>> &region); //Get Sum of all pollution
int TotalPopulation(vector<vector<Zone>> &region); //Get Sum of all population
int ResidentialTotalPopulation(vector<vector<Zone>> &region); //Get Sum of residentail population
int IndustrialTotalPopulation(vector<vector<Zone>> &region); //Get Sum of industrial population
int CommercialTotalPopulation(vector<vector<Zone>> &region); //Get Sum of Commercial population
void AnalyzeCoords(vector<vector<Zone>> &region, pair<int,int> topLeft, pair<int,int> topRight, pair<int,int> bottomLeft, pair<int,int> bottomRight); //analyze area closer
void PrintPollution(vector<vector<Zone>> region); //Print pollution totals

int main()
{
	string file, regionFile;
	string buff;
	int timeLimit, refreshRate;
	int totalPopulation, prevTotalPopulation=-1;
	pair<int,int>tL,tR,bL,bR; //coordinates to be used later in output
	vector<vector<Zone>> region;

	cout << "...:::Welcome to SimCity simulate:::...  " << endl << endl;

	cout << "Enter the name your file (don't forget to include .txt): ";
	cin >> file;
	
	/*
	CT.ReadFile(file);
	CT.PrintCity();
	region = CT.GetVector();
	cout<<"VECTOR\n";
	PrintFile(region);
	*/
	ifstream fin, regionFin;
	fin.open(file);
	
	if(fin.fail()){
		cout<<"File error.\n";
		exit(1);
	}
	
	getline(fin,buff,':');
	getline(fin,regionFile);
	getline(fin,buff,':');
	fin>>timeLimit;
	fin.ignore();
	getline(fin,buff,':');
	fin>>refreshRate;
	

	regionFin.open(regionFile); //open up region file
	if(regionFin.fail()){
		cout<<"Region file error.\n";
		exit(1);
	}

	initializeVectorMap(region, regionFin); //Function that will store data in 2D vector


	cout<<"Row Size: "<<region.size()<<endl;
	cout<<"Column Size "<<region[0].size()<<endl;
	
	
	//Display initialized vector and create adjacency lists for each zone
	cout<<"\nInitialized Vector\n";
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			cout<<region[i][j].GetType()<< " ";
			region[i][j].SetAdjacency(region); //Create adjaceny list for each zone
		}
		cout<<endl;
	}
	
	
	
	cout<<"\nStart Simulation\n\n";
	int availableGoods=0;
	int availableWorkers=0;
	for(int a = 0; a<timeLimit; a++) //time step, this is where region is updated and outputted
	{
		cout<<"State "<<a+1<<endl;
		updateCommercial(region, availableWorkers, availableGoods);
		updateIndustrial(region, availableWorkers, availableGoods);
		updateResidential(region, availableWorkers);
		
		if(a%refreshRate==0){ //check to see if we are on a multiple of the refresh rate
			PrintFile(region);
			cout<<"\nAvailable Workers: "<<availableWorkers<<endl;
			cout<<"Avaliable Goods: " <<availableGoods<<endl;
		}
		totalPopulation = TotalPopulation(region);
		if(totalPopulation==prevTotalPopulation) //If population hasn't changed then region is at a stall, and program should terminate
			break;
		prevTotalPopulation=totalPopulation;
	}
	
	//simulation is over, on to final outputs
	updatePollution(region);
	cout<<"FINISHED SIMULATION\n\n";
	
	
	cout<<"Total population for residential zones: "<<ResidentialTotalPopulation(region)<<endl; //Output residential zone totals
	cout<<"Total population for industrial zones: "<<IndustrialTotalPopulation(region)<<endl; //Output residential zone totals
	cout<<"Total population for commercial zones: "<<CommercialTotalPopulation(region)<<endl; //Output residential zone totals
	cout<<"Pollution map is\n";
	PrintPollution(region); //Print map of pollution totals
	cout<<"Total pollution is "<<TotalPollution(region)<<endl; //print sum of pollution
	
	cout<<"Please enter the coordinates of the area you would like to analyze more closely (enter 8 integers in a row, with no commmas or parantheisis such as 0 0 0 3 3 0 3 3)\n";
	cout<<"Enter the coordinates of the rectangle in the order: top left, top right, bottom left, bottom right: ";
	
	cin>>tL.first>>tL.second>>tR.first>>tR.second>>bL.first>>bL.second>>bR.first>>bR.second; //read in coordinates as pairs
	
	AnalyzeCoords(region,tL,tR,bL,bR);
	return 0;
}





//Store values from region file into 2D vector
void initializeVectorMap(vector<vector<Zone>> &region, ifstream &fin){
	char temp;
	string line;
	vector<Zone> vec;
	int colSize;
	int rowCount = 0;
	int colCount =1;
	while(!fin.eof())
	{
		getline(fin, line);
		
		string::iterator it;
		
		for(it=line.begin();it!=line.end(); it++){ //iterate through line
			if(colCount%2==1){ //skip commas
				Zone z(*it,0,0,rowCount,colCount/2);
				vec.push_back(z); //push zone back to vector
			}
			colCount++;
		}
		region.push_back(vec);
		vec.clear();
		rowCount++;
		colCount =1;
	}
}


//function finds total pollution
int TotalPollution(vector<vector<Zone>> &region){
	int sum =0;
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			sum+=region[i][j].GetPollution();
		}
	}
	
	return sum;
}

//Function returns the total population of the region
int TotalPopulation(vector<vector<Zone>> &region){
	int sum =0;
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			sum+=region[i][j].GetPopulation();
		}
	}
	
	return sum;
}

//function finds total residential population
int ResidentialTotalPopulation(vector<vector<Zone>> &region){
	int sum =0;
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			if(region[i][j].GetType()=='R')//check if it is a residential zone
				sum+=region[i][j].GetPopulation();
		}
	}
	
	return sum;
}


//function finds total industrial population
int IndustrialTotalPopulation(vector<vector<Zone>> &region){ 
	int sum =0;
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			if(region[i][j].GetType()=='I')	//check if it is a industrial zone
				sum+=region[i][j].GetPopulation();
		}
	}
	
	return sum;
}


//function finds total commercial population
int CommercialTotalPopulation(vector<vector<Zone>> &region){
	int sum =0;
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			if(region[i][j].GetType()=='C') //check if it is a commercial zone
				sum+=region[i][j].GetPopulation();
		}
	}
	
	return sum;
}





void AnalyzeCoords(vector<vector<Zone>> &region, pair<int,int> topLeft, pair<int,int> topRight, pair<int,int> bottomLeft, pair<int,int> bottomRight){
	//check to make sure all coords are inbounds, same print function after that
	if(topLeft.first>=0 && topLeft.second>=0 &&topLeft.first<region.size()&&topLeft.second<region[0].size()&& topRight.first>=0 && topRight.second>=0 && topRight.first<region.size()&& topRight.second<region[0].size()&&bottomLeft.first>=0 && bottomLeft.second>=0 &&bottomLeft.first<region.size()&&bottomLeft.second<region[0].size()&&bottomRight.first>=0 && bottomRight.second>=0 &&bottomRight.first<region.size()&&bottomRight.second<region[0].size())		
	{
		//total
		cout<<"This is the area you chose\n";
		for(int i = topLeft.first; i<=bottomLeft.first; i++){
			for(int j = topLeft.second; j<=bottomRight.second; j++){
				if(region[i][j].GetPopulation()==0)
					cout<<region[i][j].GetType()<< " ";
				else
					cout<<region[i][j].GetPopulation()<< " ";
			}
			cout<<endl;
		}
		
		//residential
		int sum =0;
		for(int i = topLeft.first; i<=bottomLeft.first; i++){
			for(int j = topLeft.second; j<=bottomRight.second; j++){
				if(region[i][j].GetType()=='R'){
					sum+=region[i][j].GetPopulation();
				}
			}
		}
		cout<<"Total Residential population within area is "<<sum<<endl;
		sum =0;
		
		//industrial
		for(int i = topLeft.first; i<=bottomLeft.first; i++){
			for(int j = topLeft.second; j<=bottomRight.second; j++){
				if(region[i][j].GetType()=='I'){
					sum+=region[i][j].GetPopulation();
				}
			}
		}
		cout<<"Total Industrial population within area is "<<sum<<endl;
		sum =0;
		
		
		//commercial
		for(int i = topLeft.first; i<=bottomLeft.first; i++){
			for(int j = topLeft.second; j<=bottomRight.second; j++){
				if(region[i][j].GetType()=='C'){
					sum+=region[i][j].GetPopulation();
				}
			}
		}
		cout<<"Total Commercial population within area is "<<sum<<endl;
		sum =0;
		
		//pollution sum
		for(int i = topLeft.first; i<=bottomLeft.first; i++){
			for(int j = topLeft.second; j<=bottomRight.second; j++){
				sum+=region[i][j].GetPollution();
			}
		}
		cout<<"Total pollution within area is "<<sum<<endl;
		sum =0;
	}
	
	else{
		cout<<"Coordinates are out of bounds, try again\n";
		cout<<"Please enter the coordinates of the area you would like to analyze more closely (enter 8 integers in a row, with no commmas or parantheisis such as 0 0 0 3 3 0 3 3)\n";
		cout<<"Enter the coordinates of the rectangle in the order: top left, top right, bottom left, bottom right: ";
	
		cin>>topLeft.first>>topLeft.second>>topRight.first>>topRight.second>>bottomLeft.first>>bottomLeft.second>>bottomRight.first>>bottomRight.second;
		AnalyzeCoords(region,topLeft,topRight,bottomLeft,bottomRight);
	}
}



void PrintPollution(vector<vector<Zone>> region){ //Print pollution totals
	
	for(int i = 0; i<region.size(); i++){
		for(int j = 0; j<region[i].size(); j++){
			if(region[i][j].GetPollution()==0)
				cout<<region[i][j].GetType()<< " ";
			else
				cout<<region[i][j].GetPollution()<< " ";
		}
		cout<<endl;
	}

}
