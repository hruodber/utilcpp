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

    //double xsa[] = {20.1, 7.1, 16.1, 14.9, 16.7, 8.8, 9.7, 10.3, 22, 16.2, 12.1, 10.3, 14.5, 12.4, 9.6, 12.2, 10.8, 14.7, 19.7, 11.2, 10.1, 11, 12.2, 9.2, 23.5, 9.4, 15.3, 9.6, 11.1, 5.3, 7.8, 25.3, 16.5, 12.6, 12, 11.5, 17.1, 11.2, 12.2, 10.6, 19.9, 14.5, 15.5, 17.4, 8.4, 10.3, 10.2, 12.5, 16.7, 8.5, 12.2};
    double xsa[inpetlen.size()];
    std::copy(inpetlen.begin(), inpetlen.end(), xsa);
    vector<double> xs(xsa, xsa+sizeof(xsa)/sizeof(double));

//    double ysa[] = {31.5, 18.9, 35, 31.6, 22.6, 26.2, 14.1, 24.7, 44.8, 23.2, 31.4, 17.7, 18.4, 23.4, 22.6, 16.4, 21.4, 26.5, 31.7, 11.9, 20, 12.5, 18, 14.2, 37.6, 22.2, 17.8, 18.3, 28, 8.1, 14.7, 37.8, 15.7, 28.6, 11.7, 20.1, 30.1, 18.2, 17.2, 19.6, 29.2, 17.3, 28.2, 38.2, 17.8, 10.4, 19, 16.8, 21.5, 15.9, 17.7};
    double ysa[inseplen.size()];
    std::copy(inseplen.begin(), inseplen.end(), ysa);

    vector<double> ys(ysa, ysa+sizeof(ysa)/sizeof(double));

    series->xs = &xs;
    series->ys = &ys;
    series->linearInterpolation = false;
    series->pointType = toVector(L"dots");
    series->color = CreateRGBColor(1, 0, 0);
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();

    settings->width = 600;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = toVector(L"");
    settings->xLabel = toVector(L"");
    settings->yLabel = toVector(L"");
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

    FreeAllocations();

    return success ? 0 : 1;
}