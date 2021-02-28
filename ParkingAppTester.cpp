/**********************************************************
 * Name: Yonghwan Song
 * Student ID: 135458198
 * Seneca email: ysong115@myseneca.ca
 * Section: NDD
 * Completion Date: 8.8
 ->I have done all the coding by myself and only copied the code that my
 professor provided to complete my workshops and assignments.
 **********************************************************/
/* ------------------------------------------------------
Final Project Milestone 6
Module: ReadWritable
Filename: ParkingAppTester.cpp
Version 1.0
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date      Reason
2020/7/4  Preliminary release
-----------------------------------------------------------*/
#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Parking.h"
using namespace std;
using namespace sdds;
void runParking() {
   Parking P("ParkingData.csv", 11);
   P.run();
}
void ShowDatafile() {
   char ch;
   ifstream file("ParkingData.csv");
   cout << endl << "Content of ParkingData.csv after the program exits" << endl;
   cout << "-----------------------------------------------------------" << endl;
   while (file.get(ch)) {
      cout <<char(tolower(ch));
   }
   cout <<  "-----------------------------------------------------------" << endl;
   cout << "To restore the data back to the original values " << endl;
   cout << "Copy \"ParkingData.csv.bak\" over \"ParkingData.csv\"" << endl;
}
int main() {
   runParking();
   ShowDatafile();
   return 0;
}
