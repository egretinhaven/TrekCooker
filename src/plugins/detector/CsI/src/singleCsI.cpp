#include <singleCsI.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TList.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TFrame.h>
#include <TSpectrum.h>
Double_t WaveformCsI::waveformSingleSignal(Double_t *x,Double_t *par){
  if(x[0]<par[1]) return 0;
  Double_t termFirst=par[0]/(1+TMath::Exp(-par[2]*(x[0]-par[6])));
  Double_t termSecond=(x[0]-par[1])/(par[3]*par[3]);
  Double_t termThird=TMath::Exp(-(x[0]-par[1])/par[3])+par[4]*TMath::Exp(-(x[0]-par[1])/par[5]);
  Double_t value=termFirst*termSecond*termThird;
  return value;
}
Double_t WaveformCsI::waveformSignal(Double_t *x,Double_t* par){
  Double_t value=0;
  for(unsigned int iWave=0;iWave<mNWave;iWave++){
    value+=waveformSingleSignal(x,&par[iWave*7]);
  }
  return value;
}
Double_t WaveformCsI::waveform(Double_t *x,Double_t* par){
  Double_t value=waveformSignal(x,par);
  unsigned int iPar=mNWave*7+1;
  value+=par[iPar-1];
  return value;
}
Double_t WaveformCsI::waveformCut(Double_t *x,Double_t* par){
  Double_t value=waveform(x,par);
  if(value>1023.0) value=1023.0;
  return value;
}
void SingleCsI::setData(const vector<UShort_t>& listD){
  for(unsigned int iS=0,nS=listD.size();iS<nS;iS++){
    mListData.push_back(listD[iS]);
  }
}
static Double_t waveformPure(Double_t *x,Double_t *par){
  if(x[0]<par[1]) return 0;
  Double_t termFirst=par[0]/(1+TMath::Exp(-par[2]*(x[0]-par[6])));
  Double_t termSecond=(x[0]-par[1])/(par[3]*par[3]);
  Double_t termThird=TMath::Exp(-(x[0]-par[1])/par[3])+par[4]*TMath::Exp(-(x[0]-par[1])/par[5]);
  Double_t value=termFirst*termSecond*termThird;
  return value;
}

static Double_t findZero(Double_t *par){
  Double_t x=par[6];
  Double_t stepSize=0.01;
  while(true){
    Double_t value=waveformPure(&x,par);
    if(value<1) return x;
    x+=stepSize;
  }
}
static Double_t derivativeSingle(Double_t *x,Double_t *par){
  if(x[0]<par[1]) return 0;
  Double_t firstExp=par[4]*TMath::Exp(-(x[0]-par[1])/par[5]);
  Double_t secondExp=TMath::Exp(-(x[0]-par[1])/par[3]);
  Double_t thirdExp=TMath::Exp(par[2]*par[6]-par[2]*x[0]);
  Double_t termFirst=par[0]*(x[0]-par[1])*(-firstExp/par[5]-secondExp/par[3])/(par[3]*par[3]*(thirdExp+1));
  Double_t termSecond=par[0]*(firstExp+secondExp)/(par[3]*par[3]*(thirdExp+1));
  Double_t termThird=par[0]*par[2]*(x[0]-par[1])*(firstExp+secondExp)*thirdExp/(par[3]*par[3]*(thirdExp+1)*(thirdExp+1));
  Double_t value=termFirst+termSecond+termThird;
  return value;
}
static Double_t findTime(Double_t *par){
  Double_t x=par[1];
  Double_t slopePre=0;
  const Double_t stepSize=0.001;
  while(true){
    Double_t value=derivativeSingle(&x,par);
    //    cout<<value<<" "<<slopePre<<endl;
    if(value<slopePre) return x-stepSize/2.0;
    slopePre=value;
    x+=stepSize;
    if(x>250) return 250;
  }

}
static Double_t findEnergy(Double_t *par){
  Double_t xLow=par[1];
  Double_t xHigh=findZero(par);

  TF1* f1=new TF1("pure",waveformPure,1,250,7);
  Double_t epsilon=0.01;
  Double_t value=f1->Integral(xLow,xHigh,par,epsilon);
  return value;
}
static Double_t findPeak(Double_t *par){
  Double_t x=par[1];
  bool wasPositive=false;
  const Double_t stepSize=0.001;
  while(true){
    Double_t value=derivativeSingle(&x,par);
    if(!wasPositive){
      if(value>0) wasPositive=true;
    }
    else{
      if(value<0) return x-stepSize/2.0;
    }
    x+=stepSize;
  }

}

static Double_t fillEnergy(Double_t *par,unsigned int nEvent,TH1D* h1){

  Double_t xLow=par[1];
  Double_t xHigh=findZero(par);
  Double_t xPeak=findPeak(par);
  TRandom3* poolRandom=new TRandom3();
  for(int i=0;i<nEvent;i++){
    Double_t x=poolRandom->Uniform(xLow,xHigh);
    h1->Fill(x,waveformPure(&x,par));
  }
  return h1->Integral("width");
}


char* SingleCsI::nameCsI(unsigned int index){
  if(index<1){
    sprintf(mName,"0000");
  }
  unsigned int iClock=(index-1)/(2*2*16)+1;
  unsigned int iInside=index-1-(iClock-1)*2*2*16;
  unsigned int iFB=iInside/(2*16);
  unsigned int iUD=(iInside-iFB*2*16)/16;
  unsigned int iPaddle=iInside%16;
  char NameFB[3]="fb";
  char NameUD[3]="ud";
  sprintf(mName,"%i%c%c%i",iClock,NameFB[iFB],NameUD[iUD],iPaddle+1);
  return mName;
}

bool SingleCsI::fit(){
  static unsigned int count=0;
  char name[256];
  cout<<"processing "<<mIndexCsI<<" "<<nameCsI(mIndexCsI)<<endl;
  sprintf(name,"wave_run%d_%dCsI_%s_%u",mRunNo,mEventNo,nameCsI(mIndexCsI),count);
  char title[256];
  sprintf(title,"fAdc waveform");
  TH1D* h1=new TH1D(name,title,250,0.5,250.5);
  for(UInt_t iData=0,nData=mListData.size();iData<nData;iData++){
    h1->SetBinContent(iData+1,mListData[iData]);
    h1->SetBinError(iData+1,1.1);
  }
  mNWave=1;
  tryFit(h1);
  Double_t chi2Reduced=findChi2(h1);
  cout<<chi2Reduced<<endl;
  if(chi2Reduced>80){
    mNWave=2;
    tryFit(h1);
  Double_t chi2Reduced=findChi2(h1);
  cout<<chi2Reduced<<endl;

  }
  /*
  for(mNWave=1;mNWave<2;mNWave++){
    tryFit(h1);
    Double_t chi2Reduced=findChi2(h1);
    if(chi2Reduced<100){
      cout<<chi2Reduced<<endl;
      break;
    }
  }
  */
  drawWaves(h1);

  return true;
  /*



  Double_t par[8];
  for(int i=0;i<8;i++){
    par[i]=h1->GetFunction("wave")->GetParameter(i);
  }
  Double_t time=findTime(par);
  TLine* line=new TLine(time,0,time,1000);
  Double_t peak=findPeak(par);
  Double_t valuePeak=waveformSingle(&peak,par);
  TLine* line2=new TLine(peak,0,peak,valuePeak);
  line2->SetLineColor(kRed);
  line->Draw("same");
  line2->Draw("same");
  Double_t energy=findEnergy(par);
  sprintf(name,"energy_run%d_%dCsI_%s",mRunNo,mEventNo,nameCsI(mIndexCsI));
  TH1D* h1Energy=new TH1D(name,"energy",5000,par[1],findZero(par));
  Double_t mySum=fillEnergy(par,int(10000000),h1Energy);
  cout<<mySum<<" "<<energy<<endl;
  h1Energy->Scale(energy/mySum);
  h1Energy->SetFillColor(1);
  h1Energy->SetFillStyle(3003);
  pad1->Update();
  c1->cd();
  TPad *pad2 = new TPad("pad2","",0,0,1,1);
  pad2->SetFillStyle(4000); //will be transparent
  pad2->Draw();
  pad2->cd();
  Double_t ymin = pad1->GetFrame()->GetY1();
  Double_t ymax = pad1->GetFrame()->GetY2();
  Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom                                                                                                                           
  Double_t xmin = pad1->GetFrame()->GetX1();
  Double_t xmax = pad1->GetFrame()->GetX2();
  Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
  pad2->Range(xmin-0.1*dx,ymin-0.1*dy-par[7],xmax+0.1*dx,ymax+0.1*dy-par[7]);

  h1Energy->SetLineColorAlpha(0,0.2);
  h1Energy->Draw("][same");
  pad2->Update();
  */
}
void SingleCsI::findLocalMax(TH1D* h1){
  TF1* f1=h1->GetFunction("waveCut");
  int nBin=h1->GetNbinsX();
  double maxValue=0;
  double newPeak;
  for(int iBin=1;iBin<=nBin;iBin++){
    float vBin=h1->GetBinContent(iBin);
    float value=f1->Eval(h1->GetBinCenter(iBin));
    if(vBin-value>maxValue){
      maxValue=vBin-value;
      newPeak=h1->GetBinCenter(iBin);
    }
  }
  mListLocalMax.push_back(newPeak);
}
void SingleCsI::tryFit(TH1D* h1){
  const unsigned int NPar=mNWave*7+1;
  WaveformCsI* myWave=new WaveformCsI(mNWave);
  TF1* f1=new TF1("waveCut",myWave,&WaveformCsI::waveformCut,1,250,NPar,"WaveformCsI","waveformCut");
  Double_t par[NPar];
  if(mNWave==1){
    f1->SetParameters(5035,26.69,0.1782,12.280,32.91,12.28,h1->GetBinCenter(h1->GetMaximumBin()),72.79);    
    f1->SetLineStyle(6);
    f1->SetLineColor(1);
    f1->SetLineWidth(3);
    h1->Fit(f1,"Q");
    for(int i=0;i<NPar;i++){
      mPar[i]=h1->GetFunction("waveCut")->GetParameter(i);
    }
  }
  else{
    findLocalMax(h1);
    f1->SetParameter(0,5035);
    f1->SetParameter(1,26.69);
    f1->SetParameter(2,0.1782);
    f1->SetParameter(3,12.280);
    f1->SetParameter(4,32.91);
    f1->SetParameter(5,12.28);
    f1->SetParameter(6,mListLocalMax[0]);    
    
    for(int i=0,n=h1->GetFunction("waveCut")->GetNpar();i<n;i++){
      f1->SetParameter(7+i,h1->GetFunction("waveCut")->GetParameter(i));
    }

    f1->SetLineStyle(6);
    f1->SetLineColor(1);
    f1->SetLineWidth(3);
    h1->Fit(f1,"Q");
    for(int i=0;i<NPar;i++){
      mPar[i]=h1->GetFunction("waveCut")->GetParameter(i);
    }
  }
}
void SingleCsI::drawWaves(TH1D* h1){
  char name[256];
  sprintf(name,"canvas_run%d_%dCsI_%s",mRunNo,mEventNo,nameCsI(mIndexCsI));
  TCanvas* c1=new TCanvas(name,name,1200,900);

  if(h1!=0){
    TPad *pad1 = new TPad("pad1","",0,0,1,1);
    pad1->Draw();
    pad1->cd();
    h1->SetMarkerStyle(2);
    h1->SetMarkerSize(1.2);
    h1->Draw();
    WaveformCsI* myWave=new WaveformCsI(mNWave);
    TF1* f2=new TF1("waveform",myWave,&WaveformCsI::waveform,1,250,mNWave*7+1,"WaveformCsI","waveform");
    Double_t par[mNWave*7+1];
    par[mNWave*7]=h1->GetFunction("waveCut")->GetParameter(mNWave*7);
    for(int i=0;i<mNWave;i++){
      //      TF1* f3=new TF1(name,derivativeSingle,1,250,7);
      for(int iPar=0;iPar<7;iPar++){
	double myPar=h1->GetFunction("waveCut")->GetParameter(i*7+iPar);
	f2->FixParameter(i*7+iPar,myPar);
	//	f3->FixParameter(iPar,h1->GetFunction("waveCut")->GetParameter(i*7+iPar));
	
      }
      //      f3->SetLineColor(kRed);
      //      h1->GetListOfFunctions()->Add(f3);

      for(int i=0;i<7*mNWave;i++){
	par[i]=h1->GetFunction("waveCut")->GetParameter(i);
      }
      Double_t time=findTime(&par[i*7]);
      TLine* line=new TLine(time,0,time,1000);
      line->Draw("same");
    }
    f2->FixParameter(mNWave*7,par[mNWave*7]);
    f2->SetLineStyle(9);
    f2->SetLineColor(kBlue);
    h1->GetListOfFunctions()->Add(f2);
    pad1->Update();
    c1->cd();

    TPad *pad2 = new TPad("pad2","",0,0,1,1);
    pad2->SetFillStyle(4000); //will be transparent
    pad2->Draw();
    pad2->cd();
    Double_t ymin = pad1->GetFrame()->GetY1();
    Double_t ymax = pad1->GetFrame()->GetY2();
    Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom                                                                                                                           
    Double_t xmin = pad1->GetFrame()->GetX1();
    Double_t xmax = pad1->GetFrame()->GetX2();
    Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
    pad2->Range(xmin-0.1*dx,ymin-0.1*dy-par[mNWave*7],xmax+0.1*dx,ymax+0.1*dy-par[mNWave*7]);
    for(int i=0;i<mNWave;i++){
      Double_t par[7];
      for(int j=0;j<7;j++){
	par[i*7+j]=h1->GetFunction("waveCut")->GetParameter(i*7+j);
      }
      Double_t energy=findEnergy(&par[i*7]);
      sprintf(name,"energy_run%d_%dCsI_%s_%i",mRunNo,mEventNo,nameCsI(mIndexCsI),i);
      TH1D* h1Energy=new TH1D(name,"energy",100,par[i*7+1],findZero(&par[i*7]));
      Double_t mySum=fillEnergy(&par[i*7],int(1000000),h1Energy);
      h1Energy->Scale(energy/mySum);
      h1Energy->SetFillColorAlpha(i+1, 0.35);
      h1Energy->SetFillStyle(3010);
      
      h1Energy->SetLineColorAlpha(0,0.2);
      //      h1Energy->Draw("][same");
      pad2->Update();
    }

  }

  c1->Write();
  sprintf(name,"wave_run%d_%dCsI_%s.png",mRunNo,mEventNo,nameCsI(mIndexCsI));
  c1->SaveAs(name);
}
Double_t SingleCsI::findChi2(TH1D* h1){
  unsigned int iLow=1;
  unsigned int iUp=h1->GetNbinsX();
  TF1* funFit=h1->GetFunction("waveCut");
  Double_t chi2=0;
  for(int i=iLow;i<=iUp;i++){
    Double_t x=h1->GetBinCenter(i);
    Double_t y=h1->GetBinContent(i);
    Double_t error=h1->GetBinError(i);
    Double_t value=funFit->Eval(x);
    Double_t thisChi2=(value-y)*(value-y)/error/error;
    chi2+=thisChi2;

  }
  chi2/=(iUp-1-h1->GetFunction("waveCut")->GetNpar());
  return chi2;
}
