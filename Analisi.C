#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>

void Caricamac(){
int n=70500;
int Pmt1[n]; 
int Pmt2[n]; 
int Pmt3[n];
int Pmt4[n]; 
int Pmt5[n];
int Pmt6[n];
int i;
int num=0;
TH1D* h1 =  new TH1D("h1", "Pmt 1",200 ,0,1200);
TH1D* h2 =  new TH1D("h2", "Pmt 2",200 ,0,1200);
TH1D* h3 =  new TH1D("h3", "Pmt 3",200 ,0,1200);
TH1D* h4 =  new TH1D("h4", "Pmt 4",200 ,0,1200);
TH1D* h5 =  new TH1D("h5", "Pmt 5",200,0,1200 );
TH1D* h6 =  new TH1D("h6", "Pmt 6", 200 ,0,1200 );
TCanvas* c1= new TCanvas("c1", "PMT", 2000,500);

//Legge il file e crea 6 array di punti che rappresentano le misure prese dal camac su ogni singolo canale nell'intero rate di acquisizione    
  ifstream infile;    
  infile.open("DatiFinali.txt");// file containing numbers in 6 columns 
     if(infile.fail()) // checks to see if file opended 
    { 
      cout << "error" << endl;
    } 

 while(!infile.eof()) // reads file to end of *file*, not line
      { 
         infile >> Pmt1[num];
         infile >> Pmt2[num]; 
         infile >> Pmt3[num]; 
	 infile >> Pmt4[num]; 
         infile >> Pmt5[num]; 
         infile >> Pmt6[num]; 


         ++num; // go to the next number
      } 
  infile.close();



 for(int ieve=0; ieve<n; ieve++){
   if(Pmt1[ieve]>9) h1->Fill(Pmt1[ieve]);
   if(Pmt2[ieve]>9) h2->Fill(Pmt2[ieve]);
   if(Pmt3[ieve]>9) h3->Fill(Pmt3[ieve]);
   if(Pmt4[ieve]>9) h4->Fill(Pmt4[ieve]);
   if(Pmt5[ieve]>9) h5->Fill(Pmt5[ieve]);
   if(Pmt6[ieve]>9) h6->Fill(Pmt6[ieve]);}
  c1->cd(1);
  h1->Draw();
  gPad->SetLogy();
