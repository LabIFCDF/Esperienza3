#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraph.h>
#include <TGraph2D.h>

void Analisi()
{
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE
	int n=483;
	int i;
	//array per vedere determinare dt1 e dt2 in due modi diversi, a e b
	double dt1a[n];
	double dt1b[n];
	double dt2a[n];
	double dt2b[n];
	//array che rappresentano la differenza tra i 2 metodi a e b di determinazione dei tempi
	double dt1[n];
	double dt2[n];
	//istogrammi dei tempi nelle configurazioni paletta a sx (_s), a dx(_d) e al centro(_c)
	TH1D* h1_s =  new TH1D("h1_s", "Tempo_s",200 ,0,4);
	TH1D* h2_s =  new TH1D("h2_s", "Pmt 1_s",200 ,0,4);
	TH1D* h3_s =  new TH1D("h3_s", "Pmt 2_s",200 ,0,4);	
	TH1D* h1_c =  new TH1D("h1_c", "Tempo_c",200 ,0,4);
	TH1D* h2_c =  new TH1D("h2_c", "Pmt 1_c",200 ,0,4);
	TH1D* h3_c =  new TH1D("h3_c", "Pmt 2_c",200 ,0,4);	
	TH1D* h1_d =  new TH1D("h1_d", "Tempo_d",200 ,0,4);
	TH1D* h2_d =  new TH1D("h2_d", "Pmt 1_d",200 ,0,4);
	TH1D* h3_d =  new TH1D("h3_d", "Pmt 2_d",200 ,0,4);
	//istogrammi per determinare le differenze dei tempi dt1 e dt2, cioè PMT1-centro e PMT2-centro	
	TH1D* ht1 =  new TH1D("ht1", "dt1a-dt1b",200 ,0,4);	
	TH1D* ht2 =  new TH1D("ht2", "dt2a-dt2b",200 ,0,4);	
	TCanvas* c1= new TCanvas("c1", "Singoli tempi nelle 3 configurazioni della paletta", 2000,500);
	TCanvas* c2= new TCanvas("c2", "Differenze temporali", 2000,500);


	//Legge il file e crea 9 vector n dimensionali    	
	std::vector<double> Time_s(n), Pmt1_s(n), Pmt2_s(n);
	std::ifstream fs_read("2602s.dat");
	std::vector<double> Time_c(n), Pmt1_c(n), Pmt2_c(n);
	std::ifstream fc_read("2602c.dat");
	std::vector<double> Time_d(n), Pmt1_d(n), Pmt2_d(n);
	std::ifstream fd_read("2602d.dat");
	//Riempio i vector
    	for(int i = 0; i < n; i++)
    	{
		fs_read >> Time_s[i] >> Pmt1_s[i] >> Pmt2_s[i];
		fc_read >> Time_c[i] >> Pmt1_c[i] >> Pmt2_c[i];
		fd_read >> Time_d[i] >> Pmt1_d[i] >> Pmt2_d[i];
	}
/* Parte dedicata alla determinazione del punto di impatto nella barra di scintillatore, avendo la differenza temporale tra PMT 1-3, e 2-3, posso fare la differenza tra questi
due per avere il tempo che ci ha messo la luce a fare una distanza pari a due volte la distanza tra il centro della barra e il punto di impatto, sapendo la distanza tra il centro
della barra e l'estremo trovo il punto di impatto */
	double csbarra= ; //velocità luce nella barra
	double x[n]; // distanza dei punti di impatto sulla barra rispetto al centro
	double h= ; //distanza verticale tra Pmt3 e barra di scintillatore
	double l[n]; //distanza obliqua percorsa dalla particella
	double c=3*10e9 ; //velocità della luce in cm al ns
	for(int i = 0; i<n; i++)
	  {
	    x[i]=csbarra*(Pmt1[i] - Pmt2[i])/2;
	    l[i]=TMath::Sqrt(TMath::Power(x[i],2) + TMath::Power(h,2));
	  }
		   
		  
	
