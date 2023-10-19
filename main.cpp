#include <iostream>
#include "csv.h"
#include <vector>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

int main(){
    vector<double> inpetlen;
    vector<double> inseplen;
    vector<double> inpetwid;
    vector<double> insepwid;
    vector<std::string> inClass;

    io::CSVReader<5> in("../data/iris.csv");
    in.read_header(io::ignore_extra_column, "pet-len", "sep-len","pet-wid", "sep-wid" , "myclass");
    double petlen; double seplen; double petwid; double sepwid; std::string myclass;
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

    bool success;
    StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();

    series->xs = &inpetlen;
    series->ys = &inseplen;
    series->linearInterpolation = false;
    series->pointType = toVector(L"dots");
    series->color = CreateRGBColor(1, 0, 0);
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();

    settings->width = 600;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(L"Iris Data");
    settings->xLabel = toVector(L"Petala Comp.");
    settings->yLabel = toVector(L"Sepala Comp");
    settings->scatterPlotSeries->push_back(series);
    //settings->scatterPlotSeries->push_back(series2);

    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "example3.png");
        DeleteImage(imageReference->image);
    }else{
        cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            cerr << c;
        }
        cerr << endl;
    }

   // FreeAllocations();

    return success ? 0 : 1;
}