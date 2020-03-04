#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>


void Riordina()
{
   float a[10]={2, 1, 5, 4, 7, 10 ,2 ,5 , 4, 3};
   long long size = 10;
   long long ind[10];
   TMath::Sort(size,a,ind,0);
   for (int i = 0; i < size; ++i) 
      std::cout << "INDEX   "<< ind[i] << std::endl;
}
