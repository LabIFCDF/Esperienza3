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

void Sopra()
{
	int n=787;
	int n1=781;
	int j1=0;
	int j2=0;
	//array di riordinamento
	int ind_01[n1];
	int ind_02[n1];
	//mediane
	double m_01=0;
	double m_02=0;
	//posizione sulla sbarra
	double x[n1];
	double L[n1];
	double b[n1];
	double gamma[n1];
	double t_volo[n1];
	double Pmt1_0[n];
	double Pmt2_0[n];
	double Pmt1_corretto[n1];
	double Pmt2_corretto[n1];
	TH1D* h0_s =  new TH1D("h0_s", "Differenza temporale (T_pmt+T_rit)-T_pmt1",200 ,0,0);
	TH1D* h0_d =  new TH1D("h0_d", "Differenza temporale (T_pmt+T_rit)-T_pmt2",200 ,0,0);
	TH1D* xsbarra =  new TH1D("xsbarra", "Distribuzione punti di impatto",200 ,0,0);
	TH1D* beta =  new TH1D("beta", "beta",200 ,0,0);
	TCanvas* c1= new TCanvas("c1", "Differenze temporali tra pmt inferiore ritardato e pmt1/2 ai lati", 2000,500);
	TCanvas* c2= new TCanvas("c2", "Distribuzione punti di impatto", 2000,500);
	TCanvas* c3= new TCanvas("c3", "Beta", 2000,500);
	std::vector<double> Time_0(n), vPmt1_0(n), vPmt2_0(n);
	std::ifstream f0_read("15LUG_UP150cm.dat");
	for(int i = 0; i < n; i++)
    	{
		f0_read >> Time_0[i] >> vPmt1_0[i] >> vPmt2_0[i];
    	}
    	for(int i = 0; i < n; i++)
    	{
    		Pmt1_0[i]=vPmt1_0[i]*40;
    		Pmt2_0[i]=vPmt2_0[i]*40;
    	}
    	for(int i = 0; i < n; i++)
    	{
    		if(Pmt1_0[i]>90&&Pmt2_0[i]>85&&Pmt1_0[i]<125&&Pmt2_0[i]<120)
		{
			Pmt1_corretto[j1]=Pmt1_0[i];
			Pmt2_corretto[j2]=Pmt2_0[i];
			j1++;
			j2++;
		}	
    	}
    	cout << j1 << endl;
    	cout << j2 << endl;
    	
    	TMath::Sort(n1,Pmt1_corretto,ind_01,0);
	TMath::Sort(n1,Pmt2_corretto,ind_02,0);
    	for(int i=0; i<n1; i++)
	{
		h0_s->Fill(Pmt1_corretto[i]);	
	}
	for(int i=0; i<n1; i++)
	{
		h0_d->Fill(Pmt2_corretto[i]);	
	}
	m_01=Pmt1_0[ind_01[370]];
	m_02=Pmt2_0[ind_02[370]];
	cout << m_01 << endl;
	cout << m_02 << endl;
	for(int i=0; i<n1; i++)
	{
		x[i]=6*(Pmt2_corretto[i]-Pmt1_corretto[i]+3.2)+140;	
	}
	for(int i=0; i<n1; i++)
	{
		xsbarra->Fill(x[i]);		
	}
	for(int i=0; i<n1; i++)
	{
		//L[i]=sqrt(pow((x[i]-140),2)+pow(180,2));
		L[i]=TMath::Sqrt(TMath::Power((x[i]-140),2)+1);
	}
	for(int i=0; i<n1; i++)
	{
		t_volo[i]=(x[i]/12)+Pmt1_corretto[i]-103.35;
		b[i]=(L[i]/(t_volo[i]*30));
		gamma[i]=1/(TMath::Sqrt(1-TMath::Power(b[i],2)));
		beta->Fill((2*b[i])/gamma[i]);	
	}
	
	c1->Divide(1,2);
	c1->cd(1);
	h0_s->Draw();
  	c1->cd(2);
  	h0_d->Draw();
  	c2->Divide(1,1);
	c2->cd(1);
	xsbarra->Draw();
	c3->Divide(1,1);
	c3->cd(1);
	beta->Draw();
	
	
	


}
