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

void Beta()
{

cout << "loading eff histo" << endl;
TFile* file = new TFile("utilities.root", "READ");
TH1D* h_eff =  (TH1D*) file->Get("Efficienza impatto");
TH1D* h_eff_theta =  (TH1D*) file->Get("Efficienza angolo");


	int n=9070;
	int n1=8915;
	int j1=0;
	int j2=0;
	//array di riordinamento
	int ind_01[n1];
	int ind_02[n1];
	//mediane
	double m_01=0;
	double m_02=0;
	//posizione sulla sbarra
	Double_t factor = 1.;
	double x[n1];
	double gamma[n1];
	double L[n1];
	double b[n1];
	double t_volo[n1];
	double Pmt1_0[n];
	double Pmt2_0[n];
	double Pmt1_corretto[n1];
	double Pmt2_corretto[n1];
	double angolo[n1];
        double max=-1;
	TH1D* h0_s =  new TH1D("h0_s", "Differenza temporale (T_pmt+T_rit)-T_pmt1",200 ,0,0);
	TH1D* h0_d =  new TH1D("h0_d", "Differenza temporale (T_pmt+T_rit)-T_pmt2",200 ,0,0);
	TH1D* xsbarra =  new TH1D("xsbarra", "Distribuzione punti di impatto pesata con l'efficienza ",29 ,0, 282);
	xsbarra->Sumw2();
	TH1D* beta =  new TH1D("beta", "Distribuzione dei beta dei muoni",100 ,0,1);
	TH1D* theta =  new TH1D("theta", "Distribuzione angolare pesata con l'efficienza",27 ,0,0);
	theta->Sumw2();
	TCanvas* c1= new TCanvas("c1", "Differenze temporali tra pmt inferiore ritardato e pmt1/2 ai lati", 2000,500);
	TCanvas* c2= new TCanvas("c2", "Distribuzione punti di impatto pesata con l'efficienza", 2000,500);
	TCanvas* c3= new TCanvas("c3", "Distribuzione dei beta dei muoni", 2000,500);
	TCanvas* c4= new TCanvas("c4", "Distribuzione angolare pesata con l'efficienza", 2000,500);
	std::vector<double> Time_0(n), vPmt1_0(n), vPmt2_0(n);
	std::ifstream f0_read("15LugDown3.dat");
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
	m_01=Pmt1_0[ind_01[4458]];
	m_02=Pmt2_0[ind_02[4458]];
	cout << m_01 << endl;
	cout << m_02 << endl;
	for(int i=0; i<n1; i++)
	{
		x[i]=6*(Pmt2_corretto[i]-Pmt1_corretto[i]+4.96)+140;	
	}
	//loop over main histo
	int ibin = -1;
	double weight = -1000;
	
	for(int i=0; i<n1; i++)
	{
		ibin = h_eff-> GetXaxis()->FindBin(x[i]);
		//cout << x[i] << endl;
		//cout << h_eff->GetBinContent(ibin) << endl;
		//cout << "-----------------------" << endl;
		weight = h_eff->GetBinContent(ibin);
		if(weight > 0.) //cout << "position = " << x[i] << " || weight = " << weight << endl;
		{
			xsbarra->Fill(x[i], 1./weight);
		}
			
			
	}
	
	Float_t *bins = new Float_t[xsbarra->GetSize()];
	
       // cout << "max è"<< max << endl;
	for(int i=0; i<n1; i++)
	{
		//L[i]=sqrt(pow((x[i]-140),2)+pow(180,2));
		L[i]=TMath::Sqrt(TMath::Power((x[i]-140),2) + TMath::Power(180,2));
	}
	for(int i=0; i<n1; i++)
	{
		t_volo[i]=(x[i]/12)+Pmt1_corretto[i]-111.665;
		b[i]=(L[i]/(30*t_volo[i]));
		gamma[i]=1/TMath::Sqrt(1 - TMath::Power(b[i],2));
		//2 A MANO WAT?
		b[i]=2*b[i]/gamma[i];
		beta->Fill(b[i]);	
	}
	for(int i=0; i<n1; i++)
	{
		angolo[i]=TMath::ATan((x[i]-140)/180);
		ibin = h_eff_theta-> GetXaxis()->FindBin(angolo[i]);
		weight = h_eff_theta->GetBinContent(ibin);
		if(weight > 0.) //cout << "position = " << x[i] << " || weight = " << weight << endl;
		{
			theta->Fill(angolo[i], 1./weight);
		}
	}
	c1->Divide(1,2);
	c1->cd(1);
	h0_s->Draw();
  	c1->cd(2);
  	h0_d->Draw();
  	c2->Divide(1,1);
	c2->cd(1);
	xsbarra->Draw("HIST E");
	c3->Divide(1,1);
	c3->cd(1);
	beta->Draw("HIST E");
	c4->Divide(1,1);
	c4->cd(1);
	theta->Draw("HIST E");
	
	
	
TCanvas* cFile01= new TCanvas("cFile01", "cFile01", 2000,500);
h_eff->Draw("HIST E");
TCanvas* cFile02= new TCanvas("cFile02", "cFile02", 2000,500);
h_eff_theta->Draw("HIST E");


}
