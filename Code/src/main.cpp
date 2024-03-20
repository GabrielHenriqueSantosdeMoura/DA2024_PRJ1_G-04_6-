//
// Created by CTW02617-admin on 3/19/2024.
//
#include "iostream"

#include "headers/Menu.h"
#include "headers/DataReader.h"

int main () {
    DataReader dataReader("../Docs/Project1DataSetSmall/Cities_Madeira.csv", "../Docs/Project1DataSetSmall/Pipes_madeira",
                          "../Docs/Project1DataSetSmall/Reservoirs_Madeira","../Docs/Project1DataSetSmall/StationsMadeira");
};