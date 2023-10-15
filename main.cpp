#include <iostream>
#include "include/csv.h"

int main(){
    io::CSVReader<5> in("../data/iris.csv");
    in.read_header(io::ignore_extra_column, "pet-len", "sep-len","pet-wid", "sep-wid" , "myclass");
    float petlen; float seplen; float petwid; float sepwid; std::string myclass;
    while(in.read_row(petlen, seplen, petwid, sepwid, myclass)){
        std::cout << petlen <<","<<seplen<<","<<petwid<<","<<sepwid<<","<<myclass<<std::endl;
    }
}