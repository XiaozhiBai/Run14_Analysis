#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "cmath"
#include "StEvtGen_Ana.h"
#include "StEvtGen_Daughter.h"
#include "TLorentzVector.h"

using namespace std;
StEvtGen_Ana::StEvtGen_Ana(const char* outName)
{
  mOutputFile=new TFile(outName,"RECREATE");
  TFile *input=new TFile("/star/u/xiao00/test_EvetGen/Weight.root","READ");
  Weight_pt=(TH1D *) input->Get("Eta"); 
}
StEvtGen_Ana::~StEvtGen_Ana()
{
  //..
  //
}
void StEvtGen_Ana::bookHistogram()
{ 
  //
  mh1pt=new TH1F("mh1pt","",400,0,20); 
  mh1ptBde=new TH1F("mh1ptBde","",400,0,20); 
  mh1ptBe=new TH1F("mh1ptBe","",400,0,20); 
  mh1Eta=new TH1F("mh1Eta","",100,-4,4); 
  mh1Phi=new TH1F("mh1Phi","",200,-4,4); 
  mh1Tao=new TH1F("mh1Tao","",400,0,20); 
  mh2EtaVspt=new TH2F("mh2EtaVspt","",100,-4,4,400,0,20);
  mh2PhiVspt=new TH2F("mh2PhiVspt","",200,-4,4,400,0,20);
  mh2EtaVsPhi=new TH2F("mh2EtaVsPhi","",100,-4,4,200,-4,4);
  //mother
  mh2mEtaVspt=new TH2F("mh2mEtaVspt","",100,-4,4,400,0,20);
  mh2mPhiVspt=new TH2F("mh2mPhiVspt","",200,-4,4,400,0,20);
  
  mh2TimeVsP=new TH2F("mh2TimeVsP","",200,0,30,400,0,20);
  mh2PathlenghVsParentP=new TH2F("mh2PathlenghVsParentP","",200,0,30,400,0,20);
  mh2PathlenghVsTime=new TH2F("mh2PathlenghVsTime","",200,0,20,400,0,20);
  //
  mh1InvMass=new TH1F("mh1InvMass","",400,0,3);
  mh2GammapVsParentp=new TH2F("mh2GammapVsParentp","",300,0,30,300,0,30); 
  mh2GammaptVsParentpt=new TH2F("mh2GammaptVsParentpt","",2000,0,20,2000,0,20); 
  mh2GammaEnergyVsParentEnergy=new TH2F("mh2GammaEnergyVsParentEnergy","",300,0,30,300,0,30); 
}
void StEvtGen_Ana::read(TString fileName)
{
  cout<<"!!!!!!!!!!!!!!!!!read"<<fileName<<endl;
  TFile * infile=new TFile(fileName.Data());
  TTree* Tree=(TTree*) infile->Get("Tree");
 
  StEvtGen_Daughter * Daughter=new StEvtGen_Daughter();
  Daughter->Init(Tree);

  for(Int_t iEvent=0;iEvent<Tree->GetEntries();iEvent++)//
    // for(Int_t iEvent=0;iEvent<20;iEvent++)//
    {
      if(iEvent%1000==0)
	cout<<"working on Event  "<<iEvent<<endl;
      Daughter->GetEntry(iEvent);

      TLorentzVector vP;
      TLorentzVector vM;
       
      for(Int_t iDaughter=0;iDaughter<Daughter->Ndaughter;iDaughter++)
	{
	  TLorentzVector v(Daughter->dPx[iDaughter],Daughter->dPy[iDaughter],Daughter->dPz[iDaughter],Daughter->dE[iDaughter]);
	  TLorentzVector mv(Daughter->mPx[iDaughter],Daughter->mPy[iDaughter],Daughter->mPz[iDaughter],Daughter->mE[iDaughter]);
	  double pathlenth= sqrt(Daughter->dvx[iDaughter]*Daughter->dvx[iDaughter]+Daughter->dvy[iDaughter]*Daughter->dvy[iDaughter]+Daughter->dvz[iDaughter]*Daughter->dvz[iDaughter]);
	  double p=sqrt(mv.Px()*mv.Px()+mv.Py()*mv.Py()+mv.Pz()*mv.Pz());

	  if(Daughter->dpdg[iDaughter]==22)
	    {
	      double weight_factor=Weight(mv.Pt());
	      mh2GammapVsParentp->Fill(mv.P(),v.P());
	      mh2GammaptVsParentpt->Fill(mv.Pt(),v.Pt(),weight_factor);
	      mh2GammaEnergyVsParentEnergy->Fill(mv.Energy(),v.Energy());
	    }
	  continue;
	  if(fabs(Daughter->dpdg[iDaughter])==11)
	    {
	      mh1pt->Fill(v.Pt());
	      if(fabs(Daughter->mpdg[iDaughter])!=511)
		mh1ptBde->Fill(v.Pt());
	      if(fabs(Daughter->mpdg[iDaughter])==511)
		mh1ptBe->Fill(v.Pt());
	      mh1Eta->Fill(v.Eta());
	      mh1Phi->Fill(v.Phi());
	      mh1Tao->Fill(Daughter->dct[iDaughter]);
	      mh2EtaVspt->Fill(v.Eta(),v.Pt());
	      mh2PhiVspt->Fill(v.Phi(),v.Pt());
	      mh2EtaVsPhi->Fill(v.Eta(),v.Phi());
	      mh2mEtaVspt->Fill(mv.Eta(),mv.Pt());
	      mh2mPhiVspt->Fill(mv.Phi(),mv.Pt());
	      mh2PathlenghVsParentP->Fill(p,pathlenth);
	      mh2TimeVsP->Fill(p,Daughter->dct[iDaughter]);
	      mh2PathlenghVsTime->Fill(Daughter->dct[iDaughter],pathlenth);
	    }
	
	  if(Daughter->dpdg[iDaughter]==11)
	    {
	      //	cout<< "electron "<<endl;
	      vM.SetPxPyPzE(Daughter->dPx[iDaughter],Daughter->dPy[iDaughter],Daughter->dPz[iDaughter],Daughter->dE[iDaughter]);
	    }
	  if(Daughter->dpdg[iDaughter]==-11)
	    {
	      //	cout<< "positron "<<endl;
	      vP.SetPxPyPzE(Daughter->dPx[iDaughter],Daughter->dPy[iDaughter],Daughter->dPz[iDaughter],Daughter->dE[iDaughter]);
	    }
	    
	  // cout<< Daughter->mpdg[iDaughter]<<endl;
	  // cout<< Daughter->dPx[iDaughter]<<endl;
	}
      // cout<< (vM+vP).M()<<endl;
      mh1InvMass->Fill((vM+vP).M());
    }
}
void StEvtGen_Ana::WriteHistogram()
{
  cout<<"  write"<<endl;
  mOutputFile->cd();
  // cout<<" 11 "<<endl;
  mh1pt->Write();
  mh1ptBe->Write();
  mh1ptBde->Write();
  mh1Eta->Write();
  mh1Phi->Write();
  mh1Tao->Write();
  mh2EtaVspt->Write();
  mh2PhiVspt->Write();
  mh2EtaVsPhi->Write();
  mh2mEtaVspt->Write();
  mh2mPhiVspt->Write();
  mh1InvMass->Write();
  mh2PathlenghVsParentP->Write();
  mh2TimeVsP->Write();
  mh2PathlenghVsTime->Write();
  mh2GammapVsParentp->Write();
  mh2GammaptVsParentpt->Write();
  mh2GammaEnergyVsParentEnergy->Write();
  mOutputFile->Close();
}
Double_t StEvtGen_Ana::Weight(Float_t pt)
{
  Double_t weight=0; 
  weight=Weight_pt->GetBinContent(Weight_pt->FindBin(pt));  
  //    return 1.0; 
  return weight;
}
