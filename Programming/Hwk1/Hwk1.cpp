
/*
	Mark White
	CSCE 1040.001 Homework 1

	Implemetnation Files: 	Hwk1.cpp, bubble.cpp
	Header Files:		student.h, bubble.h
	Data Files:		grades
	Compile and Execute:	g++ *.cpp
	./a.out < grades

	Description: The purpose of this assignment is to determine the statistics (mean, median, highest and lowest grades, etc.) of the students grades.
		     In order to properly complete the assignment we have to include two data structures along with specific variables. Additionally, we will
		     use arrays, pointers, malloc (to dyanmicallly allocate memory), different files and loops to correctly output the data from the "grade" file given to us.
*/


//Libraries
#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "bubble.h"
using namespace std;

//Creating a class stats structure and initializing variables
struct classStats
{

	float mean = 0.0;
	float min = 0.0;
	float max =  0.0;
	float median = 0.0;
	char *name;

};

int main()
{


	//Initializing variables
	int total = 0;
	int totalStudents = 19;
	classStats stats;
	student *studentArr[totalStudents];

	//Reading the name of the course
	stats.name = (char*) malloc (sizeof(char) *15);
	scanf("%s", stats.name);


	//Using malloc to dynamicaly allocate memory to the array for each variable
	for(int i = 0; i < totalStudents; i++)
	{
		studentArr[i] = (student*) malloc (sizeof(student));
		studentArr[i]->first = (char*) malloc (15*sizeof(char*));
		studentArr[i]->last = (char*) malloc (15*sizeof(char*));

		//reading in names and exam values from the grades file
		scanf("%s %s %d %d %d",studentArr[i]->first, studentArr[i]->last, &studentArr[i]->exam1,
		      &studentArr[i]->exam2, &studentArr[i]->exam3);

		//Calculating the man from the three exams
		studentArr[i]->mean = (studentArr[i]->exam1 + studentArr[i]->exam2 + studentArr[i]->exam3)/3.0;

		//Keeping track of the indivisual students mean total in order to find the mean of the entire class
		total = total + studentArr[i]->mean;
	}

	//Using bubble to sort the array

	bubble(studentArr, totalStudents);

	//After soring I know the first and last values in the array will be the min and max
	stats.max = studentArr[18]->mean;
	stats.min = studentArr[0]->mean;
	stats.mean = total/totalStudents;
	stats.median = studentArr[totalStudents/2]->mean;

	//Printing stats
	printf("123456789012345678901234567890123456789012345678901234567890\n");
	printf("%s MEAN: %.2f MIN: %.2f MAX: %.2f MEDIAN: %.2f\n",
		stats.name, stats.mean, stats.min, stats.max, stats.median);

	for(int i = 0; i < totalStudents; i++)
	{
		printf("%15s %15s %.2f\n", studentArr[i]->first, studentArr[i]->last,
			studentArr[i]->mean);
	}

	//Freeing the dyanmically allocated memory
	for(int i = 0; i < totalStudents; i++)
	{
		free(studentArr[i]->first);
		free(studentArr[i]->last);
		free(studentArr[i]);

	}

  return 0;
}

