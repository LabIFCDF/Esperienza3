#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include "TGraphErrors.h"
#include "TF1.h"

void Luce()
{
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE
	int n=14688;
	//creo degli array di supporto per poterli riordinare visto che i vector non si possono riordinare con la Step
	double Pmt1_0[n];
	
	//array di riordinamento
	int ind_0s[n];
	//mediane
	double m_0s=0;
	
	

	//Legge il file e crea 9 vector n dimensionali    	
	std::vector<double> Time_0(n), vPmt1_0(n), vPmt2_0(n);
	std::ifstream f0_read("dati10.dat");
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
	
	
}
