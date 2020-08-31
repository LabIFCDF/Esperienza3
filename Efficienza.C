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
#include <TF1.h>
#include <TGraphErrors.h>

void Efficienza()
{
 int n = 14688 ; //Numero di dati nel file
 int i;
 int j;
 TCanvas* c1= new TCanvas("c1", "Distribuzione dei punti di impatto", 2000,500);
 TH1D* hx = new TH1D("hx", "Punto di impatto",200,0,0);
 TCanvas* c2= new TCanvas("c2", "Distribuzione dei tempi", 2000,500);
 TH1D* ht = new TH1D("ht", "Tempo rilevato",200,0,0);
 /*Legge il file e crea 3 vector n dimensionali    	
    std::vector<double> Time(n), Pmt1(n), Pmt2(n);
	std::ifstream f_read("15LugT1T2.dat");
	//Riempio i vector
    	for(int i = 0; i < n; i++)
    	{
		f_read >> Time[i] >> Pmt1[i] >> Pmt2[i];
		}*/
	int csbarra=12;
	double T12[n];
	double x[n];
	double t[n];
	double Rit;
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE	
	double Pmt1_0[n];
	
	//array di riordinamento
	int ind_0s[n];
	//mediane
	double m_0s=0;
	
	

	//Legge il file e crea 9 vector n dimensionali    	
	std::vector<double> Time_0(n), vPmt1_0(n), vPmt2_0(n);
	std::ifstream f0_read("15LugT1T2.dat");
	//Riempio i vector
    	for(int i = 0; i < n; i++)
    	{
		f0_read >> Time_0[i] >> vPmt1_0[i] >> vPmt2_0[i];

    	}
    	//conversioni in secondi
    	for(int i = 0; i < n; i++)
    	{
    		Pmt1_0[i]=vPmt1_0[i]*40;
    	}
    	
    	//riordino gli array per conoscere le mediane
    	TMath::Sort(n,Pmt1_0,ind_0s,0);
    	//calcolo le mediane
    	m_0s=Pmt1_0[ind_0s[7344]];
    	cout <<"Pmt1_0=" << m_0s << endl;
	
	for(int i=0; i<n; i++){
	  T12[i]=Pmt1_0[i];
	}
	Rit=m_0s-0.1;
	for(int i=0; i<n; i++) {
	  ht->Fill(T12[i]);
	  x[i]=((T12[i]-Rit)*csbarra)/2;
	  if (x[i]>-150 && x[i]<150){ hx->Fill(x[i]);}

	}
	c1->cd();
	hx->Draw("HIST E");
	c2->cd();
	ht->Draw("HIST E");
	
	
}
