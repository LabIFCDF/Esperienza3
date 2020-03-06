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

void Tof()
{
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE
	int n=580;
	int i;
	TH1D* hRit1 =  new TH1D("hRit1", "Costante di ritardo 1",200 ,0,0);	
	TH1D* hRit2 =  new TH1D("hRit2", "Costante di ritardo 2",200 ,0,0);	
	TCanvas* c1= new TCanvas("c1", "Costanti di ritardo", 2000,500);
	TH1D* hx = new TH1D("hx", "Punto di impatto",200,0,0);
	TH1D* hl = new TH1D("hl", "Lunghezza percorsa in volo",200,0,0);
	TCanvas* c2= new TCanvas("c2", "Lunghezza percorsa e punti di impatto", 2000,500);
	TH1D* hDl =  new TH1D("hDl", "errori su l",200 ,0,0);
	TCanvas* c3= new TCanvas("c3", "Errore su Lunghezza percorsa", 2000,500);
        TH1D* hv = new TH1D("hv", "distribuzione di velocità", 200,0,40);
	TCanvas* c4= new TCanvas("c4", "distribuzione di velocità", 2000,500);

	//Legge il file e crea 9 vector n dimensionali    	
	std::vector<double> Time(n), Pmt1(n), Pmt2(n);
	std::ifstream f_read("tofc0403.dat");
	//Riempio i vector
    	for(int i = 0; i < n; i++)
    	{
		f_read >> Time[i] >> Pmt1[i] >> Pmt2[i];
	}
/* Parte dedicata alla determinazione del punto di impatto nella barra di scintillatore, avendo la differenza temporale tra PMT 1-3, e 2-3, posso fare la differenza tra questi
due per avere il tempo che ci ha messo la luce a fare una distanza pari a due volte la distanza tra il centro della barra e il punto di impatto, sapendo la distanza tra il centro
della barra e l'estremo trovo il punto di impatto */
	double csbarra=14 ; //velocità luce nella barra
	double x[n]; // distanza dei punti di impatto sulla barra rispetto al centro
	double h=110 ; //distanza verticale tra Pmt3 e barra di scintillatore
	double l[n]; //distanza obliqua percorsa dalla particella
	double l0[n]; // l calcolato al minimo
	double l20[n]; // l calcolato al massimo
	double Dl[n]; //errore massimo su l
	double Rit1[n]; //costante di ritardo per il segnale di 1 - 3
	double Rit2[n];//costante di ritardo per il segnale di 2 - 3
	double c=30 ; //velocità della luce in cm al ns
	double x10[n];
	double x20[n];
	double tRit1;
	double v[n];
	for(int i = 0; i<n; i++)
	  {
	    Pmt1[i]=Pmt1[i]*40;
	    Pmt2[i]=Pmt2[i]*40;
	    x[i]=csbarra*(Pmt1[i] - Pmt2[i])/2;
	    x10[i]= (x[i]+10);
	    l[i]=TMath::Sqrt(TMath::Power(x10[i],2) + TMath::Power(h,2));
	    l0[i]=TMath::Sqrt(TMath::Power(x[i],2) + TMath::Power(h,2));
	    x20[i]=x[i]+20;
	    l20[i]=TMath::Sqrt(TMath::Power(x20[i],2) + TMath::Power(h,2));
	    Dl[i]=(l20[i] - l0[i])/2;
	    if(Dl[i]<0) {Dl[i]=-Dl[i];}
	    Rit2[i]=Pmt2[i]-(l[i]/c)+((140 +  x[i])/csbarra);
	    Rit1[i]=Pmt1[i]-(l[i]/c)+((140 - x[i])/csbarra);
	  }

	for(int i=0; i<n; i++)
	  {
	    if(x[i]<-140 ||  x[i]>140) {}
	    else{
	    hRit1->Fill(Rit1[i]);
	    hRit2->Fill(Rit2[i]);
	    hx->Fill(x[i]);
	    if(l[i]<100) {cout<<i<<endl;}
	    hl->Fill(l[i]);
	    hDl->Fill(Dl[i]);
	    }
	  }
	
	c1->Divide(1,2);
	c2->Divide(1,2);
	c1->cd(1);
	hRit1->Draw();
	c1->cd(2);
	hRit2->Draw();
	c2->cd(1);
	hx->Draw();
	c2->cd(2);
	hl->Draw();
	c3->cd();
        hDl->Draw();

	tRit1=hRit1->GetMean();
	cout<<tRit1<<endl;
	for(i=0; i<n; i++)
	  {
	    v[i]=l[i]/(Pmt1[i]- tRit1 + ((140-x[i])/csbarra));
	    if(x[i]<-140 ||  x[i]>140 || v[i]<0 || v[i]>40) {}
	     else{
	    hv->Fill(v[i]);
	     }
	  }
	c4->cd();
	hv->Draw();
	
}	  
	
