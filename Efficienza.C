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
 Double_t factor = 1.;
 TCanvas* c1= new TCanvas("c1", "Distribuzione dei punti di impatto", 2000,500);
 TH1D* hx = new TH1D("hx", "Distribuzione dei punti di impatto con la sola sbarra di scintillatore, normalizzata con il numero atteso di muoni per bin",29,0,282);
 TCanvas* c2= new TCanvas("c2", "Distribuzione dei tempi", 2000,500);
 TH1D* ht = new TH1D("ht", "Tempo rilevato",100,0,0);
 TCanvas* c3= new TCanvas("c3", "Distribuzione dei punti di impatto in angolo", 2000,500);
 TH1D* htheta = new TH1D("htheta", "Distribuzione angolare con la sola sbarra di scintillatore, normalizzata al bin piu' popolato",27,0,0);
 

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
	
	double max=-1;
	double theta[n];
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
	  if (x[i]>-150 && x[i]<150)
	  { hx->Fill(x[i]+140);
	    theta[i]=TMath::ATan((x[i])/180);
	    htheta->Fill(theta[i]);
	  
	  }

	}
	Float_t *bins = new Float_t[hx->GetSize()];
	
        for (Int_t i=0;i<hx->GetSize();i++)
        {
       		bins[i] = hx->GetBinContent(i);
       		cout<< bins[i] << endl;
       	}
       	for (Int_t i=0;i<hx->GetSize();i++)
        {
       		if(max<bins[i])
       		{
       			max=bins[i];
       		}
       	
       	}
       	cout << "max è"<< max << endl;
	c1->cd();
	hx->Scale(factor/883);
	hx->Draw("HIST E");
	c2->cd();
	ht->Draw("HIST E");
	c3->cd();
	htheta->Scale(factor/822);
	htheta->Draw("HIST E");
	

TFile* file = new TFile("utilities.root", "RECREATE");

hx -> Write("Efficienza impatto",2,0);
htheta -> Write("Efficienza angolo");
 


	
	
}
