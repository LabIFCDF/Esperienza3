#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>

void Luce()
{
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE
	int n=403;
	double l=250;//cm
	
	double Pmt1_0[n];
	double Pmt2_0[n];
	double Pmt1_1[n];
	double Pmt2_1[n];
	double Pmt1_2[n];
	double Pmt2_2[n];
	double Pmt1_3[n];
	double Pmt2_3[n];
	double Pmt1_4[n];
	double Pmt2_4[n];
	double Pmt1_5[n];
	double Pmt2_5[n];
	
	
	
	
	//array per determinare le differenze temporali al variare della posizione della paletta nelle configurazioni 0-1-2-3-4-5 distanziate di 50 cm
	double dt_10[n];
	double dt_20[n];
	double dt_30[n];
	double dt_40[n];
	double dt_50[n];
	double ttot[n];
	//array di riordinamento
	int ind_0s[n];
	int ind_1s[n];
	int ind_2s[n];
	int ind_3s[n];
	int ind_4s[n];
	int ind_5s[n];
	//mediane
	//array di riordinamento
	double m_0s;
	double m_1s;
	double m_2s;
	double m_3s;
	double m_4s;
	double m_5s;
	//array della velocità della luce nella sbarra
	double v[n];
	//istogrammi dei tempi nelle configurazioni paletta
	TH1D* h0_s =  new TH1D("h0_s", "Pmt 1_0",200 ,0,0);
	TH1D* h0_d =  new TH1D("h0_d", "Pmt 2_0",200 ,0,0);
	TH1D* h1_s =  new TH1D("h1_s", "Pmt 1_1",200 ,0,0);
	TH1D* h1_d =  new TH1D("h1_d", "Pmt 2_1",200 ,0,0);
	TH1D* h2_s =  new TH1D("h2_s", "Pmt 1_2",200 ,0,0);
	TH1D* h2_d =  new TH1D("h2_d", "Pmt 2_2",200 ,0,0);
	TH1D* h3_s =  new TH1D("h3_s", "Pmt 1_3",200 ,0,0);
	TH1D* h3_d =  new TH1D("h3_d", "Pmt 2_3",200 ,0,0);
	TH1D* h4_s =  new TH1D("h4_s", "Pmt 1_4",200 ,0,0);
	TH1D* h4_d =  new TH1D("h4_d", "Pmt 2_4",200 ,0,0);
	TH1D* h5_s =  new TH1D("h5_s", "Pmt 1_5",200 ,0,0);
	TH1D* h5_d =  new TH1D("h5_d", "Pmt 2_5",200 ,0,0);
	TCanvas* c1= new TCanvas("c1", "Singoli tempi nelle configurazioni della paletta 0-1-2", 2000,500);
	TCanvas* c2= new TCanvas("c2", "Singoli tempi nelle configurazioni della paletta 1-2-3", 2000,500);
	//istogrammi per determinare le differenze dei tempi dt1 e dt2, cioè PMT1-centro e PMT2-centro	
	TH1D* ht_10 =  new TH1D("ht_10", "dt_10",200 ,0,0);	
	TH1D* ht_20 =  new TH1D("ht_20", "dt_20",200 ,0,0);
	TH1D* ht_30 =  new TH1D("ht_30", "dt_30",200 ,0,0);	
	TH1D* ht_40 =  new TH1D("ht_40", "dt_40",200 ,0,0);	
	TH1D* ht_50 =  new TH1D("ht_50", "dt_50",200 ,0,0);		
	TCanvas* c3= new TCanvas("c3", "Differenze temporali", 2000,500);
	//istogramma per la velocita' della luce
	TH1D* hv =  new TH1D("hv", "Velocita' luce nella sbarra",200 ,0,0);
	TCanvas* c4= new TCanvas("c4", "Velocità luce nella sbarra", 2000,500);

	//Legge il file e crea 9 vector n dimensionali    	
	std::vector<double> Time_0(n), vPmt1_0(n), vPmt2_0(n);
	std::ifstream f0_read("dati10.dat");
	std::vector<double> Time_1(n), vPmt1_1(n), vPmt2_1(n);
	std::ifstream f1_read("dati60.dat");
	std::vector<double> Time_2(n), vPmt1_2(n), vPmt2_2(n);
	std::ifstream f2_read("dati110.dat");
	std::vector<double> Time_3(n), vPmt1_3(n), vPmt2_3(n);
	std::ifstream f3_read("dati160.dat");
	std::vector<double> Time_4(n), vPmt1_4(n), vPmt2_4(n);
	std::ifstream f4_read("dati210.dat");
	std::vector<double> Time_5(n), vPmt1_5(n), vPmt2_5(n);
	std::ifstream f5_read("dati260.dat");
	//Riempio i vector
    	for(int i = 0; i < n; i++)
    	{
		f0_read >> Time_0[i] >> vPmt1_0[i] >> vPmt2_0[i];
		f1_read >> Time_1[i] >> vPmt1_1[i] >> vPmt2_1[i];
		f2_read >> Time_2[i] >> vPmt1_2[i] >> vPmt2_2[i];
		f3_read >> Time_3[i] >> vPmt1_3[i] >> vPmt2_3[i];
		f4_read >> Time_4[i] >> vPmt1_4[i] >> vPmt2_4[i];
		f5_read >> Time_5[i] >> vPmt1_5[i] >> vPmt2_5[i];
    	}
    	//conversioni in secondi
    	for(int i = 0; i < n; i++)
    	{
    		Pmt1_0[i]=vPmt1_0[i]*40;
    		Pmt2_0[i]=vPmt2_0[i]*40;
    		Pmt1_1[i]=vPmt1_1[i]*40;
    		Pmt2_1[i]=vPmt2_1[i]*40;
    		Pmt1_2[i]=vPmt1_2[i]*40;
    		Pmt2_2[i]=vPmt2_2[i]*40;
    		Pmt1_3[i]=vPmt1_3[i]*40;
    		Pmt2_3[i]=vPmt2_3[i]*40;
    		Pmt1_4[i]=vPmt1_4[i]*40;
    		Pmt2_4[i]=vPmt2_4[i]*40;
		Pmt1_5[i]=vPmt1_5[i]*40;
    		Pmt2_5[i]=vPmt2_5[i]*40;
    	}
    	
    	//riordino gli array per conoscere le mediane
    	TMath::Sort(n,Pmt1_0,ind_0s,0);
    	TMath::Sort(n,Pmt1_1,ind_1s,0);
    	TMath::Sort(n,Pmt1_2,ind_2s,0);
    	TMath::Sort(n,Pmt1_3,ind_3s,0);
    	TMath::Sort(n,Pmt1_4,ind_4s,0);
    	TMath::Sort(n,Pmt1_5,ind_5s,0);
    	//calcolo le mediane
    	m_0s=Pmt1_0[ind_0s[200]];
    	m_1s=Pmt1_1[ind_1s[200]];
    	m_2s=Pmt1_2[ind_2s[200]];
    	m_3s=Pmt1_3[ind_3s[200]];
    	m_4s=Pmt1_4[ind_4s[200]];
    	m_5s=Pmt1_5[ind_5s[200]];
    	
    	
    	
    	//determino gli intervalli temporali 
	for(int i = 0; i < n; i++)
    	{
    		dt_10[i]=m_1s-m_0s;
    		dt_20[i]=m_2s-m_0s;
    		dt_30[i]=m_3s-m_0s;
    		dt_40[i]=m_4s-m_0s;
    		dt_50[i]=m_5s-m_0s;
    	}
    	
    	
    	//calcolo la velocità della luce nella sbarra ATTENZIONE ALLE CONDIZIONI DI ESISTENZA
    	for(int i = 0; i < n; i++)
    	{
    		v[i]=l/dt_50[i];
    	}
    	
    	for(int i = 0; i < n; i++)
    	{
    		hv->Fill(v[i]);
    	}
    	
	//riempio istogrammi per le differenze temporali 
	for(int i=0; i<n; i++)
	{
		ht_10->Fill(dt_10[i]);
		ht_20->Fill(dt_20[i]);
		ht_30->Fill(dt_30[i]);
		ht_40->Fill(dt_40[i]);
		ht_50->Fill(dt_50[i]);
	}
	//riempio gli istogrammi con i singoli tempi dei file dat relativi alle posizioni sx,centro,dx della paletta
	for(int i=0; i<n; i++)
	{
		h0_s->Fill(Pmt1_0[i]);
		h0_d->Fill(Pmt2_0[i]);
	  	h1_s->Fill(Pmt1_1[i]);
	  	h1_d->Fill(Pmt2_1[i]);
		h2_s->Fill(Pmt1_2[i]);
	  	h2_d->Fill(Pmt2_2[i]);
	  	h3_s->Fill(Pmt1_3[i]);
		h3_d->Fill(Pmt2_3[i]);
	  	h4_s->Fill(Pmt1_4[i]);
	  	h4_d->Fill(Pmt2_4[i]);
	  	h5_s->Fill(Pmt1_5[i]);
	  	h5_d->Fill(Pmt2_5[i]);
	}
	
	c1->Divide(2,3);
	c1->cd(1);
	h0_s->Draw();
  	c1->cd(2);
  	h0_d->Draw();
 	c1->cd(3);
  	h1_s->Draw();
  	c1->cd(4);
  	h1_d->Draw();
  	c1->cd(5);
  	h2_s->Draw();
  	c1->cd(6);
  	h2_d->Draw();
  	c2->Divide(2,3);
	c2->cd(1);
	h3_s->Draw();
  	c2->cd(2);
  	h3_d->Draw();
 	c2->cd(3);
  	h4_s->Draw();
  	c2->cd(4);
  	h4_d->Draw();
  	c2->cd(5);
  	h5_s->Draw();
  	c2->cd(6);
  	h5_d->Draw();
  	c3->Divide(2,3);
  	c3->cd(1);
  	ht_10->Draw();
  	c3->cd(2);
  	ht_20->Draw();
  	c3->cd(3);
  	ht_30->Draw();
  	c3->cd(4);
  	ht_40->Draw();
  	c3->cd(5);
  	ht_50->Draw();
	c4->cd();
	hv->Draw();  	
	
	
	
}
