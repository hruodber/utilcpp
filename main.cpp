#include <iostream>
#include "include/csv.h"
#include <vector>
using namespace std;

int main(){
    vector<float> inpetlen;
    vector<float> inseplen;
    vector<float> inpetwid;
    vector<float> insepwid;
    vector<std::string> inClass;

    io::CSVReader<5> in("../data/iris.csv");
    in.read_header(io::ignore_extra_column, "pet-len", "sep-len","pet-wid", "sep-wid" , "myclass");
    float petlen; float seplen; float petwid; float sepwid; std::string myclass;
    while(in.read_row(petlen, seplen, petwid, sepwid, myclass)){
        std::cout << petlen <<","<<seplen<<","<<petwid<<","<<sepwid<<","<<myclass<<std::endl;
        inpetlen.push_back(petlen);
        inseplen.push_back(seplen);
        inpetwid.push_back(petwid);
        insepwid.push_back(sepwid);
        inClass.push_back(myclass);
    }

    for(int i=0;i<inpetlen.size();i++)
      std::cout << inpetlen[i] <<","<<inseplen[i]<<","<<inpetwid[i]<<","<<insepwid[i]<<","<<inClass[i]<<std::endl;

}