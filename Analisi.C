#include <iostream>
#include <fstream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
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
  	//determino i due intervalli temporali (sx-centro, dx-centro) nei modi a e b
	for(int i = 0; i < n; i++)
    	{
    		//(paletta a sx,tempo PMT a dx)-(paletta al centro,tempo PMT a dx)
    		dt1a[i]=Pmt2_s[i]-Pmt2_c[i];
    		//(paletta a dx,tempo PMT a sx)-(paletta al centro,tempo PMT a dx)
    		dt1b[i]=Pmt1_d[i]-Pmt2_c[i];
    		//(paletta a dx,tempo PMT a sx)-(paletta al centro,tempo PMT a sx)
    		dt2a[i]=Pmt1_d[i]-Pmt1_c[i];
    		//(paletta a sx,tempo PMT a dx)-(paletta al centro,tempo PMT a sx)
    		dt2b[i]=Pmt2_s[i]-Pmt1_c[i];
    	}
    	//determino la differenza tra i due modi a e b
    	for(int i = 0; i < n; i++)
    	{
    		dt1[i]=dt1a[i]-dt1b[i];
    		dt2[i]=dt2a[i]-dt2b[i];
    	}
	//riempio istogrammi per le differenze temporali nei modi a e b dei due intervalli (sx-centro, dx-centro)
	for(int j=0; j<n; j++)
	{
		ht1->Fill(dt1[j]);
		ht2->Fill(dt2[j]);
	}
	//riempio gli istogrammi con i singoli tempi dei file dat relativi alle posizioni sx,centro,dx della paletta
	for(int j=0; j<n; j++)
	{
		h1_s->Fill(Time_s[j]);
		h2_s->Fill(Pmt1_s[j]);
	  	h3_s->Fill(Pmt2_s[j]);
	  	h1_c->Fill(Time_c[j]);
		h2_c->Fill(Pmt1_c[j]);
	  	h3_c->Fill(Pmt2_c[j]);
	  	h1_d->Fill(Time_d[j]);
		h2_d->Fill(Pmt1_d[j]);
	  	h3_d->Fill(Pmt2_d[j]);
	}
	c1->Divide(2,3);
	c1->cd(1);
	h2_s->Draw();
  	c1->cd(2);
  	h3_s->Draw();
 	c1->cd(3);
  	h2_c->Draw();
  	c1->cd(4);
  	h3_c->Draw();
  	c1->cd(5);
  	h2_d->Draw();
  	c1->cd(6);
  	h3_d->Draw();
  	c2->Divide(2,1);
  	c2->cd(1);
  	ht1->Draw();
  	c2->cd(2);
  	ht2->Draw();
  	
  
}
