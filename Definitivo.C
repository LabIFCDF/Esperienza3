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

void Definitivo()
{
	//INSERIRE n=MINIMO NUMERO RIGHE DEI 3 FILE
	int n=9070;
	int i;
	TH1D* hRit1 =  new TH1D("hRit1", "Costante di ritardo 1",200 ,0,0);	
	TH1D* hRit2 =  new TH1D("hRit2", "Costante di ritardo 2",200 ,0,0);	
	TCanvas* c1= new TCanvas("c1", "Costanti di ritardo", 2000,500);
	TH1D* hx = new TH1D("hx", "Punto di impatto",200,0,0);
	TH1D* hl = new TH1D("hl", "Lunghezza percorsa in volo",200,0,0);
	TCanvas* c2= new TCanvas("c2", "Lunghezza percorsa e punti di impatto", 2000,500);
	TH1D* hDl =  new TH1D("hDl", "errori su l",200 ,0,0);
	TCanvas* c3= new TCanvas("c3", "Errore su Lunghezza percorsa", 2000,500);
        TH1D* hv1 = new TH1D("hv1", "distribuzione di velocità", 200,0,40);
	 TH1D* hv2 = new TH1D("hv2", "distribuzione di velocità", 200,0,40);
	TCanvas* c4= new TCanvas("c4", "distribuzione di velocità", 2000,500);

	 TH1D* hPmt1 = new TH1D("hPmt1", "Pmt1", 200,80,140);
	 TH1D* hPmt2 = new TH1D("hPmt2", "Pmt2", 200,80,140);
	TCanvas* c5= new TCanvas("c5", "distribuzione di velocità", 2000,500);
	TCanvas* c6= new TCanvas("c6", "distribuzione in angolo", 2000,500);
	TH1D* hTheta = new TH1D("hTheta", "Theta", 200, 0,0);
	   TCanvas* c7= new TCanvas("c7", "distribuzione degli errori nei tempi  di ritardo", 2000,500);
    TH1D* hDTRit1 =  new TH1D("hDRit1", "Errore su Costante di ritardo 1",200 ,0,0);	
    TH1D* hDTRit2 =  new TH1D("hDRit2", "Errore su Costante di ritardo 2",200 ,0,0); 

	//Legge il file e crea 9 vector n dimensionali    	
    std::vector<double> Time(n), Pmt1(n), Pmt2(n);
	std::ifstream f_read("15LugDown3.dat");
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
	double h=180 ; //distanza verticale tra Pmt3 e barra di scintillatore
	double l[n]; //distanza obliqua percorsa dalla particella
	double lmax[n]; // l calcolato al massimo
	double lmin[n]; // l calcolato al minimo
	double Dl[n]; //errore massimo su l
	double Rit1[n]; //costante di ritardo per il segnale di 1 - 3
	double Rit2[n];//costante di ritardo per il segnale di 2 - 3
	double DTRit1[n];
	double DTRit2[n];
	double c=30 ; //velocità della luce in cm al ns
	double xmax[n];
	double xmin[n];
	double tRit1;
	double tRit2;
	double DRit1;
	double DRit2;
	double v1[n];
	double v2[n];
	double Theta[n];
	double T23[n];
	double g[n];
	double gord;
	double T23ord;
	double g2[n];
	double T13[n];
	for(int i = 0; i<n; i++)
	  {
	    Pmt1[i]=Pmt1[i]*40;
	    Pmt2[i]=Pmt2[i]*40;
	    x[i]=csbarra*(Pmt1[i] - Pmt2[i])/2;
	    if(x[i]>=0){
	    xmax[i]= (x[i]+10);
	    lmax[i]=TMath::Sqrt(TMath::Power(xmax[i],2) + TMath::Power(h,2));
	    l[i]=TMath::Sqrt(TMath::Power(x[i],2) + TMath::Power(h,2));
	    xmin[i]=x[i]-10;
	    lmin[i]=TMath::Sqrt(TMath::Power(xmin[i],2) + TMath::Power(h,2));
	    Dl[i]=(lmax[i] - lmin[i])/2;
	    if(Dl[i]<0) {Dl[i]=-Dl[i];}
	    }
	    else {
	    xmax[i]= (x[i]-10);
	    lmax[i]=TMath::Sqrt(TMath::Power(xmax[i],2) + TMath::Power(h,2));
	    l[i]=TMath::Sqrt(TMath::Power(x[i],2) + TMath::Power(h,2));
	    xmin[i]=x[i]+10;
	    lmin[i]=TMath::Sqrt(TMath::Power(xmin[i],2) + TMath::Power(h,2));
	    Dl[i]=(lmax[i] - lmin[i])/2;
	    if(Dl[i]<0) {Dl[i]=-Dl[i];}
	    }
	    Rit2[i]=Pmt2[i]-(l[i]/c)+((140 -  x[i])/csbarra);
	    Rit1[i]=Pmt1[i]-(l[i]/c)+((140 + x[i])/csbarra);
	    g[i]= (l[i]/c) - ((140 -  x[i])/csbarra);
	    T23[i]=Pmt2[i];
	    g2[i]= +(l[i]/c) - ((140 +  x[i])/csbarra);
	    T13[i]=Pmt1[i];
	  }
	/*	TMath::Sort(n,g,gord,0);
	for(int i=0; i<n; i++) {
	  for(int j=0; j<n; j++){
	    if (Rit2[j]+gord[i]==Pmt2array[j])
	      T23[j]=Pmt2[j];
	  }
	  }*/
	int j;
	for(int i=0; i<n; i++)
	  {
	    T23ord=T23[i];
	    gord= g[i];
	    j=i-1;
	    while((g[j]>gord) && (j>=0))
	      {g[j+1]=g[j];
		T23[j+1] = T23[j];
		j--;
	      }
	    T23[j+1]=T23ord;
	    g[j+1]=gord;
	    
	  }
	    
	/*for(int i=0; i<n; i++){
	  cout << g[i] << endl;}
	for(int i=0; i<n; i++){
	cout << T23[i] << endl;}*/
      	

	for(int i=0; i<n; i++)
	  {
	    T23ord=T13[i];
	    gord= g2[i];
	    j=i-1;
	    while((g2[j]>gord) && (j>=0))
	      {g2[j+1]=g2[j];
		T13[j+1] = T13[j];
		j--;
	      }
	    T13[j+1]=T23ord;
	    g2[j+1]=gord;
	    
	  }
	    
	for(int i=0; i<n; i++){
	  cout << g2[i] << endl;}
	for(int i=0; i<n; i++){
	  cout << T13[i] << endl;}
      	
	    
	    
	    
	  

	for(int i=0; i<n; i++)
	  {
	    if(x[i]<-140 ||  x[i]>140) {}
	    else{
	      DTRit1[i]=Dl[i]/c;
	      DTRit2[i]=Dl[i]/c;
	    hRit1->Fill(Rit1[i]);
	    hRit2->Fill(Rit2[i]);
	    hDTRit1->Fill(DTRit1[i]);
	    hDTRit2->Fill(DTRit2[i]);
	    hx->Fill(x[i]);
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
	c7->Divide(1,2);
	c7->cd(1);
	hDTRit1->Draw();
	c7->cd(2);
	hDTRit2->Draw();
	
	tRit1=hRit1->GetMean();
	tRit2=hRit2->GetMean();
	cout<<tRit1<<endl;
      	cout<<tRit2<<endl;
	DRit1=hDTRit1->GetMean();
	DRit2=hDTRit2->GetMean();
	cout<<DRit1<<endl;
      	cout<<DRit2<<endl;
	for(i=0; i<n; i++)
	  {
	    Theta[i]= TMath::ATan(x[i]/h);
	    v1[i]=l[i]/(+Pmt1[i]- 108.5  + ((140+x[i])/csbarra));
	    v2[i]=l[i]/(+Pmt2[i]- 104.8 + ((140 - x[i])/csbarra));
	    if(x[i]<-140 ||  x[i]>140/* || v1[i]>30 || v2[i]>30*/) {}
	     else{
	    hv1->Fill(v1[i]);
	    hv2->Fill(v2[i]);
	    hPmt1->Fill(Pmt1[i]);
	    hPmt2->Fill(Pmt2[i]);
	    hTheta->Fill(Theta[i]);
	     }
	  }
	c4->Divide(1,2);
	c4->cd(1);
	hv1->Draw();
	c4->cd(2);
	hv2->Draw();
	c5->Divide(1,2);
	c5->cd(1);
	hPmt1->Draw();
	c5->cd(2);
	hPmt2->Draw();
	c6->cd();
	  hTheta->Draw();
	  double dt[n];
	  double dg[n];
	  double dg2[n];
	  for(int i=0; i<n; i++){
	    dt[i]=0.1;
	    dg[i]=2*(g[i]/100);
	    dg2[i]=2*(g2[i]/100);
	   }
 	//TGraph per il fit
	  TGraphErrors *grafico= new TGraphErrors(n,g,T23,dg,dt);
	grafico->SetTitle("Tempi di ritardo2; t[ns];lunghezza [cm]");
	TCanvas* c8= new TCanvas("c8", "Tempi di ritardo", 2000,500);
	//Disegno il grafico
	grafico->DrawClone("APE");
	
	//Funzione lineare
	double chi;
	TF1 *f= new TF1("Legge lineare","[0]+[1]*x",0,300);
	f->SetParameter(0,100);
	f->SetParameter(1,1);
	//Linea carina
	f->SetLineColor(kRed); f->SetLineStyle(2);
	//Fit
	grafico->Fit(f);
	f->DrawClone("Same");
	chi=f->GetChisquare();
	c8->cd();
	grafico->Draw();
	cout << chi << endl;

		//TGraph per il fit
	  TGraphErrors *grafico2= new TGraphErrors(n,g2,T13,dg,dt);
	grafico2->SetTitle("Tempi di ritardo1; t[ns];lunghezza [cm]");
		TCanvas* c9= new TCanvas("c9", "Tempi di ritardo", 2000,500);
	//Disegno il grafico
	grafico->DrawClone("APE");
	
	//Funzione lineare
	double chi2;
	TF1 *s= new TF1("Legge lineare","[0]+[1]*x",0,300);
	s->SetParameter(0,100);
	s->SetParameter(1,1);
	//Linea carina
	s->SetLineColor(kRed); s->SetLineStyle(2);
	//Fit
	grafico2->Fit(s);
	s->DrawClone("Same");
	chi2=s->GetChisquare();
	c9->cd();
	grafico2->Draw();
	cout << chi2 << endl;
    
    
}	  
	
