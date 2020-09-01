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
	int n=403;
	//cm
	double l_0=0;
	double l_1=50;
	double l_2=100;
	double l_3=150;
	double l_4=200;
	double l_5=250;
	//creo degli array di supporto per poterli riordinare visto che i vector non si possono riordinare con la Step
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
	double dt_s10[n];
	double dt_s20[n];
	double dt_s30[n];
	double dt_s40[n];
	double dt_s50[n];
	double dt_d10[n];
	double dt_d20[n];
	double dt_d30[n];
	double dt_d40[n];
	double dt_d50[n];
	double ttot[n];
	//array di riordinamento
	int ind_0s[n];
	int ind_1s[n];
	int ind_2s[n];
	int ind_3s[n];
	int ind_4s[n];
	int ind_5s[n];
	int ind_0d[n];
	int ind_1d[n];
	int ind_2d[n];
	int ind_3d[n];
	int ind_4d[n];
	int ind_5d[n];
	//mediane
	double m_0s=0;
	double m_1s=0;
	double m_2s=0;
	double m_3s=0;
	double m_4s=0;
	double m_5s=0;
	double m_0d=0;
	double m_1d=0;
	double m_2d=0;
	double m_3d=0;
	double m_4d=0;
	double m_5d=0;
	//array della velocità della luce nella sbarra
	double v_s10[n];
	double v_s20[n];
	double v_s30[n];
	double v_s40[n];
	double v_s50[n];
	double v_d10[n];
	double v_d20[n];
	double v_d30[n];
	double v_d40[n];
	double v_d50[n];
	//array dei valori medi delle velocità con relativo errore
	double xcoord[5]={l_1, l_2, l_3, l_4};
	//double tl[5]={3.384, 7.154, 11.18, 15.15, 19.4};
	double tl[5]={2.997, 7.38, 11.54, 15.4};
	double dxcoord[5]={1.5, 1.5, 1.5, 1.5};
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
	//TCanvas* c1= new TCanvas("c1", "Singoli tempi nelle configurazioni della paletta 0-1-2", 2000,500);
	//TCanvas* c2= new TCanvas("c2", "Singoli tempi nelle configurazioni della paletta 1-2-3", 2000,500);
	//istogrammi per determinare le differenze dei tempi dt1 e dt2, cioè PMT1-centro e PMT2-centro	
	TH1D* ht_10 =  new TH1D("ht_10", "dt_10",200 ,0,0);	
	TH1D* ht_20 =  new TH1D("ht_20", "dt_20",200 ,0,0);
	TH1D* ht_30 =  new TH1D("ht_30", "dt_30",200 ,0,0);	
	TH1D* ht_40 =  new TH1D("ht_40", "dt_40",200 ,0,0);	
	TH1D* ht_50 =  new TH1D("ht_50", "dt_50",200 ,0,0);		
	//TCanvas* c3= new TCanvas("c3", "Differenze temporali", 2000,500);
	//istogramma per la velocita' della luce
	TH1D* hv_10 =  new TH1D("hv_10", "Velocita' luce nella sbarra, 50cm",2000 ,0,0);
	TH1D* hv_20 =  new TH1D("hv_20", "Velocita' luce nella sbarra, 100cm",2000 ,0,0);
	TH1D* hv_30 =  new TH1D("hv_30", "Velocita' luce nella sbarra, 150cm",2000 ,0,0);
	TH1D* hv_40 =  new TH1D("hv_40", "Velocita' luce nella sbarra, 200cm",2000 ,0,0);
	TH1D* hv_50 =  new TH1D("hv_50", "Velocita' luce nella sbarra, 250cm",2000 ,0,0);
	//TCanvas* c4= new TCanvas("c4", "Velocità luce nella sbarra", 2000,500);
	
	

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
    	TMath::Sort(n,Pmt2_0,ind_0d,0);
    	TMath::Sort(n,Pmt2_1,ind_1d,0);
    	TMath::Sort(n,Pmt2_2,ind_2d,0);
    	TMath::Sort(n,Pmt2_3,ind_3d,0);
    	TMath::Sort(n,Pmt2_4,ind_4d,0);
    	TMath::Sort(n,Pmt2_5,ind_5d,0);
    	//calcolo le mediane
    	m_0s=Pmt1_0[ind_0s[201]];
    	cout <<"Pmt1_0=" << m_0s << endl;
    	m_1s=Pmt1_1[ind_1s[201]];
    	cout <<"Pmt1_1=" << m_1s << endl;
    	m_2s=Pmt1_2[ind_2s[201]];
    	cout <<"Pmt1_2=" << m_2s << endl;
    	m_3s=Pmt1_3[ind_3s[201]];
    	cout <<"Pmt1_3=" << m_3s << endl;
    	m_4s=Pmt1_4[ind_4s[201]];
    	cout <<"Pmt1_4=" << m_4s << endl;
    	m_5s=Pmt1_5[ind_5s[201]];
    	cout <<"Pmt1_5=" << m_5s << endl;
    	m_0d=Pmt2_0[ind_0d[201]];
    	cout <<"Pmt2_0=" << m_0d << endl;
    	m_1d=Pmt2_1[ind_1d[201]];
    	cout <<"Pmt2_1=" << m_1d << endl;
    	m_2d=Pmt2_2[ind_2d[201]];
    	cout <<"Pmt2_2=" << m_2d << endl;
    	m_3d=Pmt2_3[ind_3d[201]];
    	cout <<"Pmt2_2=" << m_3d << endl;
    	m_4d=Pmt2_4[ind_4d[201]];
    	cout <<"Pmt2_4=" << m_4s << endl;
    	m_5d=Pmt2_5[ind_5d[201]];
    	cout <<"Pmt2_5=" << m_5d << endl;
    	
    	
    	
    	//determino gli intervalli temporali 
	for(int i = 0; i < n; i++)
    	{
    		dt_s10[i]=m_1s-m_0s;
    		dt_s20[i]=m_2s-m_0s;
    		dt_s30[i]=m_3s-m_0s;
    		dt_s40[i]=m_4s-m_0s;
    		dt_s50[i]=m_5s-m_0s;
    		dt_d10[i]=m_0d-m_1d;
    		dt_d20[i]=m_0d-m_2d;
    		dt_d30[i]=m_0d-m_3d;
    		dt_d40[i]=m_0d-m_4d;
    		dt_d50[i]=m_0d-m_5d;
    	}
    	
    	
    	//calcolo la velocità della luce nella sbarra ATTENZIONE ALLE CONDIZIONI DI ESISTENZA
    	for(int i = 0; i < n; i++)
    	{
    		 v_s10[i]=l_1/dt_s10[i];
    		 v_s20[i]=l_2/dt_s20[i];
    		 v_s30[i]=l_3/dt_s30[i];
    		 v_s40[i]=l_4/dt_s40[i];
    		 v_s50[i]=l_5/dt_s50[i];
    		 v_d10[i]=l_1/dt_d10[i];
    		 v_d20[i]=l_2/dt_d20[i];
    		 v_d30[i]=l_3/dt_d30[i];
    		 v_d40[i]=l_4/dt_d40[i];
    		 v_d50[i]=l_5/dt_d50[i];
    	}
    	
    	for(int i = 0; i < n; i++)
    	{
    		hv_10->Fill(v_d10[i]);
    		hv_20->Fill(v_d20[i]);
    		hv_30->Fill(v_d30[i]);
    		hv_40->Fill(v_d40[i]);
    		hv_50->Fill(v_d50[i]);
    	}
    	
	//riempio istogrammi per le differenze temporali 
	for(int i=0; i<n; i++)
	{
		ht_10->Fill(dt_d10[i]);
		ht_20->Fill(dt_d20[i]);
		ht_30->Fill(dt_d30[i]);
		ht_40->Fill(dt_d40[i]);
		ht_50->Fill(dt_d50[i]);
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
	
	//TGraph per il fit
	TGraphErrors *grafico= new TGraphErrors(4,tl,xcoord,nullptr,dxcoord);
	grafico->SetTitle("Velocita' della luce in funzione della posizione; t[ns];lunghezza [cm]");
	TCanvas* c5= new TCanvas("c5", "Velocita' luce nella sbarra", 2000,500);

	
	//Funzione lineare
	double chi;
	TF1 *f= new TF1("Legge lineare","[0]+[1]*x",0,300);
	f->SetParameter(0,0);
	f->SetParameter(1,20);
	//Linea carina
	f->SetLineColor(kBlue);
	f->SetLineWidth(1);
	f->SetNpx(10000);
	 //f->SetLineStyle();
	//Fit
	grafico->Fit(f);
	f->Draw();
		//Disegno il grafico
	grafico->Draw("APE SAME");
	chi=f->GetChisquare();
	c5->cd();
	cout << chi << endl;
	
	
	
	
	
	
	
	
	/*c1->Divide(2,3);
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
  	c4->Divide(2,3);
	c4->cd(1);
	hv_10->Draw();
	c4->cd(2);
	hv_20->Draw();
	c4->cd(3);
	hv_30->Draw();
	c4->cd(4);
	hv_40->Draw();
	c4->cd(5);
	hv_50->Draw(); 	*/
	
	
}
