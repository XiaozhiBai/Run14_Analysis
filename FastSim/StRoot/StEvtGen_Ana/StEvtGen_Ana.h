
/*/-----------------

  \class is for the eventGen decay sample for analysis 

  Auther:  Xiaozhi 5/1/2015 xiaozhi@uic.edu

  ----------------*/
#ifndef StEvtGen_Ana_h
#define  StEvtGen_Ana_h

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "StMaker.h"

class TString;
class TF1;
class TH1D;
class TH2D;
class  TH3F;

class StEvtGen_Ana : public StMaker
{
 public:
  StEvtGen_Ana(const char *outName);
  virtual ~StEvtGen_Ana();
  
  void bookHistogram() ;
  void read(TString filename);
  void WriteHistogram();
  Double_t Weight(Float_t pt); 

 private:
  TFile * mOutputFile;

  TH1D *Weight_pt;  
  
  TH1F * mh1pt;
  TH1F*  mh1ptBde;
  TH1F*  mh1ptBe;
  TH1F * mh1Eta;
  TH1F * mh1Phi;
  TH1F * mh1Tao;
  TH1F * mh1InvMass;
  TH2F * mh2EtaVspt;
  TH2F * mh2PhiVspt;
  TH2F * mh2EtaVsPhi;

  TH2F * mh2mEtaVspt;
  TH2F * mh2mPhiVspt;
  TH2F * mh2PathlenghVsParentP;
  TH2F *  mh2TimeVsP;
  TH2F *  mh2PathlenghVsTime;
  TH2F *  mh2GammapVsParentp;
  TH2F *  mh2GammaptVsParentpt;
  TH2F * mh2GammaEnergyVsParentEnergy;
  // mothter
  //  Float_t Pt_xx[9]={2.5,3.5,4.5,5.5,6.5,7.5,8.5,10.5,16.5};
 
  ClassDef(StEvtGen_Ana,1)
    };

#endif
