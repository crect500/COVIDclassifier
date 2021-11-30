//compiled with c++11:
//g++ -std=c++11 toMatrix.cpp -o matrix

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "rapidcsv.h"


int main(){
    
    //Rapid CSV to read document
    rapidcsv::Document doc("../data/clean_data.csv");
    std::ofstream outfile("../data/medData.txt");
    
    //Write first line to the outfile (column names)
    outfile << "Age,Sex,Race,Condition,Hospitalized\n";
    
    /*Reading the CSV row by row, int k keeps track of the relevant column being read.
    Values are compared and written in a new format to a string.
     
    i.e. "Male" -> "m"
         "40 - 49 Years" -> "45"
     
     These values are then written into a matrix using a comma as a delimeter
     */
    
    for(int i = 0; i < doc.GetRowCount(); i++){
        int k = -1;
        std::vector<std::string> row = doc.GetRow<std::string>(i);
        
        std::string matrixRow[5] = {"0","0","0","0","0"};
        for(auto j: row){
            k++;
            if(k == 0){
                if(!j.compare("Male")){
                    matrixRow[1] = "m";
                }
                else{
                    matrixRow[1] = "f";
                }
            }
            else if(k == 1){
                if(!j.compare("0 - 9 Years")){
                    matrixRow[0] = "5";
                }
                else if(!j.compare("10 - 19 Years")){
                    matrixRow[0] = "15";
                }
                else if(!j.compare("20 - 29 Years")){
                    matrixRow[0] = "25";
                }
                else if(!j.compare("30 - 39 Years")){
                    matrixRow[0] = "35";
                }
                else if(!j.compare("40 - 49 Years")){
                    matrixRow[0] = "45";
                }
                else if(!j.compare("50 - 59 Years")){
                    matrixRow[0] = "55";
                }
                else if(!j.compare("60 - 69 Years")){
                    matrixRow[0] = "65";
                }
                else if(!j.compare("70 - 79 Years")){
                    matrixRow[0] = "75";
                }
                else{
                    matrixRow[0] = "85";
                }
            }
            else if(k == 2){
                if(!j.compare("Native Hawaiian/Other Pacific Islander")){
                    matrixRow[2] = "I";
                }
                else if(!j.compare("White")){
                    matrixRow[2] = "W";
                }
                else if(!j.compare("Black")){
                    matrixRow[2] = "B";
                }
                else if(!j.compare("Asian")){
                    matrixRow[2] = "A";
                }
                else if(!j.compare("Hispanic/Latino")){
                    matrixRow[2] = "H";
                }
                else{
                    matrixRow[2] = "N";
                }
            }
            else if(k == 3){
                if(!j.compare("Yes")){
                    matrixRow[3] = "1";
                }
            }
            else{
                if(!j.compare("Yes")){
                    matrixRow[4] = "1";
                }
            }
            
            
        }
        
        std::cout << "Working on line " << i << "/2264594" << std::endl;
        
        for(int l = 0; l < 5; l++){
            outfile << matrixRow[l];
            if(l < 4){
                outfile << ",";
            }
        }
        outfile <<'\n';
    }
    return 0;
}

