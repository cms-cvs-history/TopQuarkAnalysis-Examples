
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TPostScript.h"

void analyzeFullLepHypotheses(){

  gROOT->SetStyle("Plain");

  TFile* file = new TFile("analyzeFullLepHypotheses.root");

  TH1F* topPtKinSol;   file->GetObject("analyzeKinSolution/topPt;1",   topPtKinSol );
  topPtKinSol->SetLineColor(2); topPtKinSol->SetLineWidth(2);
  TH1F* topEtaKinSol;  file->GetObject("analyzeKinSolution/topEta;1",  topEtaKinSol ); 
  topEtaKinSol->SetLineColor(2); topEtaKinSol->SetLineWidth(2);  
  TH1F* topMassKinSol; file->GetObject("analyzeKinSolution/topMass;1", topMassKinSol );  
  topMassKinSol->SetLineColor(2); topMassKinSol->SetLineWidth(2); 
 
  TH1F* topPtGenMatch;   file->GetObject("analyzeGenMatch/topPt;1",   topPtGenMatch ); 
  topPtGenMatch->SetFillStyle(3554); topPtGenMatch->SetFillColor(3); topPtGenMatch->SetLineColor(3);
  TH1F* topEtaGenMatch;  file->GetObject("analyzeGenMatch/topEta;1",  topEtaGenMatch ); 
  topEtaGenMatch->SetFillStyle(3554); topEtaGenMatch->SetFillColor(3); topEtaGenMatch->SetLineColor(3);
  TH1F* topMassGenMatch; file->GetObject("analyzeGenMatch/topMass;1", topMassGenMatch ); 
  topMassGenMatch->SetFillStyle(3554); topMassGenMatch->SetFillColor(3); topMassGenMatch->SetLineColor(3);
  
  TH1F* topBarPtKinSol;   file->GetObject("analyzeKinSolution/topBarPt;1",   topBarPtKinSol );
  topBarPtKinSol->SetLineColor(2); topBarPtKinSol->SetLineWidth(2);
  TH1F* topBarEtaKinSol;  file->GetObject("analyzeKinSolution/topBarEta;1",  topBarEtaKinSol ); 
  topBarEtaKinSol->SetLineColor(2); topBarEtaKinSol->SetLineWidth(2);  
  TH1F* topBarMassKinSol; file->GetObject("analyzeKinSolution/topBarMass;1", topBarMassKinSol );  
  topBarMassKinSol->SetLineColor(2); topBarMassKinSol->SetLineWidth(2); 
 
  TH1F* topBarPtGenMatch;   file->GetObject("analyzeGenMatch/topBarPt;1",   topBarPtGenMatch ); 
  topBarPtGenMatch->SetFillStyle(3554); topBarPtGenMatch->SetFillColor(3); topBarPtGenMatch->SetLineColor(3);
  TH1F* topBarEtaGenMatch;  file->GetObject("analyzeGenMatch/topBarEta;1",  topBarEtaGenMatch ); 
  topBarEtaGenMatch->SetFillStyle(3554); topBarEtaGenMatch->SetFillColor(3); topBarEtaGenMatch->SetLineColor(3);
  TH1F* topBarMassGenMatch; file->GetObject("analyzeGenMatch/topBarMass;1", topBarMassGenMatch ); 
  topBarMassGenMatch->SetFillStyle(3554); topBarMassGenMatch->SetFillColor(3); topBarMassGenMatch->SetLineColor(3); 
  
  TH1F* wPlusPtKinSol;   file->GetObject("analyzeKinSolution/wPlusPt;1",   wPlusPtKinSol );
  wPlusPtKinSol->SetLineColor(2); wPlusPtKinSol->SetLineWidth(2);
  TH1F* wPlusEtaKinSol;  file->GetObject("analyzeKinSolution/wPlusEta;1",  wPlusEtaKinSol ); 
  wPlusEtaKinSol->SetLineColor(2); wPlusEtaKinSol->SetLineWidth(2);  
  TH1F* wPlusMassKinSol; file->GetObject("analyzeKinSolution/wPlusMass;1", wPlusMassKinSol );  
  wPlusMassKinSol->SetLineColor(2); wPlusMassKinSol->SetLineWidth(2); 
 
  TH1F* wPlusPtGenMatch;   file->GetObject("analyzeGenMatch/wPlusPt;1",   wPlusPtGenMatch ); 
  wPlusPtGenMatch->SetFillStyle(3554); wPlusPtGenMatch->SetFillColor(3); wPlusPtGenMatch->SetLineColor(3);
  TH1F* wPlusEtaGenMatch;  file->GetObject("analyzeGenMatch/wPlusEta;1",  wPlusEtaGenMatch ); 
  wPlusEtaGenMatch->SetFillStyle(3554); wPlusEtaGenMatch->SetFillColor(3); wPlusEtaGenMatch->SetLineColor(3);
  TH1F* wPlusMassGenMatch; file->GetObject("analyzeGenMatch/wPlusMass;1", wPlusMassGenMatch ); 
  wPlusMassGenMatch->SetFillStyle(3554); wPlusMassGenMatch->SetFillColor(3); wPlusMassGenMatch->SetLineColor(3);    
  
  TH1F* wMinusPtKinSol;   file->GetObject("analyzeKinSolution/wMinusPt;1",   wMinusPtKinSol );
  wMinusPtKinSol->SetLineColor(2); wMinusPtKinSol->SetLineWidth(2);
  TH1F* wMinusEtaKinSol;  file->GetObject("analyzeKinSolution/wMinusEta;1",  wMinusEtaKinSol ); 
  wMinusEtaKinSol->SetLineColor(2); wMinusEtaKinSol->SetLineWidth(2);  
  TH1F* wMinusMassKinSol; file->GetObject("analyzeKinSolution/wMinusMass;1", wMinusMassKinSol );  
  wMinusMassKinSol->SetLineColor(2); wMinusMassKinSol->SetLineWidth(2); 
 
  TH1F* wMinusPtGenMatch;   file->GetObject("analyzeGenMatch/wMinusPt;1",   wMinusPtGenMatch ); 
  wMinusPtGenMatch->SetFillStyle(3554); wMinusPtGenMatch->SetFillColor(3); wMinusPtGenMatch->SetLineColor(3);
  TH1F* wMinusEtaGenMatch;  file->GetObject("analyzeGenMatch/wMinusEta;1",  wMinusEtaGenMatch ); 
  wMinusEtaGenMatch->SetFillStyle(3554); wMinusEtaGenMatch->SetFillColor(3); wMinusEtaGenMatch->SetLineColor(3);
  TH1F* wMinusMassGenMatch; file->GetObject("analyzeGenMatch/wMinusMass;1", wMinusMassGenMatch ); 
  wMinusMassGenMatch->SetFillStyle(3554); wMinusMassGenMatch->SetFillColor(3); wMinusMassGenMatch->SetLineColor(3);    
  
  
       
  TH1F* topPullPtKinSol;   file->GetObject("analyzeKinSolution/topPullPt;1",   topPullPtKinSol );
  topPullPtKinSol->SetLineColor(2); topPullPtKinSol->SetLineWidth(2);
  TH1F* topPullEtaKinSol;  file->GetObject("analyzeKinSolution/topPullEta;1",  topPullEtaKinSol ); 
  topPullEtaKinSol->SetLineColor(2); topPullEtaKinSol->SetLineWidth(2);  
  TH1F* topPullMassKinSol; file->GetObject("analyzeKinSolution/topPullMass;1", topPullMassKinSol );  
  topPullMassKinSol->SetLineColor(2); topPullMassKinSol->SetLineWidth(2); 
 
  TH1F* topPullPtGenMatch;   file->GetObject("analyzeGenMatch/topPullPt;1",   topPullPtGenMatch ); 
  topPullPtGenMatch->SetFillStyle(3554); topPullPtGenMatch->SetFillColor(3); topPullPtGenMatch->SetLineColor(3);
  TH1F* topPullEtaGenMatch;  file->GetObject("analyzeGenMatch/topPullEta;1",  topPullEtaGenMatch ); 
  topPullEtaGenMatch->SetFillStyle(3554); topPullEtaGenMatch->SetFillColor(3); topPullEtaGenMatch->SetLineColor(3);
  TH1F* topPullMassGenMatch; file->GetObject("analyzeGenMatch/topPullMass;1", topPullMassGenMatch ); 
  topPullMassGenMatch->SetFillStyle(3554); topPullMassGenMatch->SetFillColor(3); topPullMassGenMatch->SetLineColor(3);
  
  TH1F* wPlusPullPtKinSol;   file->GetObject("analyzeKinSolution/wPlusPullPt;1",   wPlusPullPtKinSol );
  wPlusPullPtKinSol->SetLineColor(2); wPlusPullPtKinSol->SetLineWidth(2);
  TH1F* wPlusPullEtaKinSol;  file->GetObject("analyzeKinSolution/wPlusPullEta;1",  wPlusPullEtaKinSol ); 
  wPlusPullEtaKinSol->SetLineColor(2); wPlusPullEtaKinSol->SetLineWidth(2);  
  TH1F* wPlusPullMassKinSol; file->GetObject("analyzeKinSolution/wPlusPullMass;1", wPlusPullMassKinSol );  
  wPlusPullMassKinSol->SetLineColor(2); wPlusPullMassKinSol->SetLineWidth(2); 
 
  TH1F* wPlusPullPtGenMatch;   file->GetObject("analyzeGenMatch/wPlusPullPt;1",   wPlusPullPtGenMatch ); 
  wPlusPullPtGenMatch->SetFillStyle(3554); wPlusPullPtGenMatch->SetFillColor(3); wPlusPullPtGenMatch->SetLineColor(3);
  TH1F* wPlusPullEtaGenMatch;  file->GetObject("analyzeGenMatch/wPlusPullEta;1",  wPlusPullEtaGenMatch ); 
  wPlusPullEtaGenMatch->SetFillStyle(3554); wPlusPullEtaGenMatch->SetFillColor(3); wPlusPullEtaGenMatch->SetLineColor(3);
  TH1F* wPlusPullMassGenMatch; file->GetObject("analyzeGenMatch/wPlusPullMass;1", wPlusPullMassGenMatch ); 
  wPlusPullMassGenMatch->SetFillStyle(3554); wPlusPullMassGenMatch->SetFillColor(3); wPlusPullMassGenMatch->SetLineColor(3);
  

  TLegend* legend = new TLegend(.7,.7,1.0,1.0);
  legend->AddEntry(topPtKinSol  ,"KinSol"  ,"l");
  legend->AddEntry(topPtGenMatch,"GenMatch","f"); 
  
  
   
  
  TH2F* genNeutrinoSpectrum;   file->GetObject("analyzeGenMatch/genNeutrinoSpectrum;1",  genNeutrinoSpectrum );
  genNeutrinoSpectrum->SetTitle("Generated Neutrino Spectrum");
  genNeutrinoSpectrum->GetXaxis()->SetTitle("E_{#nu} [GeV]");       genNeutrinoSpectrum->GetXaxis()->SetTitleOffset(2);
  genNeutrinoSpectrum->GetYaxis()->SetTitle("E_{#bar{#nu}} [GeV]"); genNeutrinoSpectrum->GetYaxis()->SetTitleOffset(2);  
  TH2F* kinNeutrinoSpectrum;   file->GetObject("analyzeKinSolution/neutrinoSpectrum;1",     kinNeutrinoSpectrum );  
  kinNeutrinoSpectrum->SetTitle("KinSolution Spectrum");
  kinNeutrinoSpectrum->GetXaxis()->SetTitle("E_{#nu} [GeV]");       kinNeutrinoSpectrum->GetXaxis()->SetTitleOffset(2);
  kinNeutrinoSpectrum->GetYaxis()->SetTitle("E_{#bar{#nu}} [GeV]"); kinNeutrinoSpectrum->GetYaxis()->SetTitleOffset(2);   
  TH2F* matchNeutrinoSpectrum; file->GetObject("analyzeGenMatch/neutrinoSpectrum;1",        matchNeutrinoSpectrum );  
  matchNeutrinoSpectrum->SetTitle("GenMatch Spectrum");
  matchNeutrinoSpectrum->GetXaxis()->SetTitle("E_{#nu} [GeV]");       matchNeutrinoSpectrum->GetXaxis()->SetTitleOffset(2);
  matchNeutrinoSpectrum->GetYaxis()->SetTitle("E_{#bar{#nu}} [GeV]"); matchNeutrinoSpectrum->GetYaxis()->SetTitleOffset(2);   
  
  
  TH1F* topMassDiffKinSol;     file->GetObject("analyzeKinSolution/topMassDiff;1", topMassDiffKinSol ); 
  topMassDiffKinSol->SetTitle("m (top) - m (anti top) for KinSolution"); 
  TH1F* topMassDiffGenMatch;   file->GetObject("analyzeGenMatch/topMassDiff;1",    topMassDiffGenMatch );
  topMassDiffGenMatch->SetTitle("m (top) - m (anti top) for GenMatch");
  
  TH1F* solWeight;              file->GetObject("analyzeKinSolution/solWeight;1",              solWeight );  
  TH2F* solWeightVsTopPullMass; file->GetObject("analyzeKinSolution/solWeightVsTopPullMass;1", solWeightVsTopPullMass );  
      
  TH1F* genMatchDr;              file->GetObject("analyzeKinSolution/genMatchDr;1",              genMatchDr );  
  TH2F* genMatchDrVsTopPullMass; file->GetObject("analyzeKinSolution/genMatchDrVsTopPullMass;1", genMatchDrVsTopPullMass );    
  

  
  TPostScript ps (TString("FullLepHypotheses.ps"), 111);
  TCanvas* Canvas = new TCanvas("FullLepHypotheses", "FullLepHypotheses", 800, 1100);  
  Canvas->Clear(); 
  Canvas->Divide(2,3);  
  Canvas->cd(1);
  topPtGenMatch->Draw();
  topPtKinSol->Draw("same");
  legend->Draw("same");        
  Canvas->cd(2);
  topEtaGenMatch->Draw();
  topEtaKinSol->Draw("same");
  legend->Draw("same");    
  Canvas->cd(3);
  topMassGenMatch->Draw();
  topMassKinSol->Draw("same"); 
  legend->Draw("same");  
  Canvas->cd(4);
  wPlusPtGenMatch->Draw();
  wPlusPtKinSol->Draw("same");
  legend->Draw("same");        
  Canvas->cd(5);
  wPlusEtaGenMatch->Draw();  
  wPlusEtaKinSol->Draw("same");
  legend->Draw("same");  
  Canvas->cd(6);
  wPlusMassKinSol->Draw();
  wPlusMassGenMatch->Draw("same");
  legend->Draw("same");        
  Canvas->cd(); 
  Canvas->Update();           
  Canvas->Clear(); 
  
  Canvas->Divide(2,3);  
  Canvas->cd(1);
  topBarPtGenMatch->Draw();
  topBarPtKinSol->Draw("same"); 
  legend->Draw("same");       
  Canvas->cd(2);
  topBarEtaGenMatch->Draw();
  topBarEtaKinSol->Draw("same"); 
  legend->Draw("same");   
  Canvas->cd(3);
  topBarMassGenMatch->Draw();
  topBarMassKinSol->Draw("same"); 
  legend->Draw("same");  
  Canvas->cd(4);
  wMinusPtGenMatch->Draw();
  wMinusPtKinSol->Draw("same");  
  legend->Draw("same");      
  Canvas->cd(5);
  wMinusEtaGenMatch->Draw();  
  wMinusEtaKinSol->Draw("same"); 
  legend->Draw("same"); 
  Canvas->cd(6);
  wMinusMassKinSol->Draw();
  wMinusMassGenMatch->Draw("same");
  legend->Draw("same");        
  Canvas->cd(); 
  Canvas->Update();           
  Canvas->Clear();    
  
  Canvas->Divide(2,3);  
  Canvas->cd(1);
  topPullPtGenMatch->Draw();
  topPullPtKinSol->Draw("same"); 
  legend->Draw("same");       
  Canvas->cd(2);
  topPullEtaGenMatch->Draw();
  topPullEtaKinSol->Draw("same"); 
  legend->Draw("same");   
  Canvas->cd(3);
  topPullMassGenMatch->Draw();
  topPullMassKinSol->Draw("same"); 
  legend->Draw("same");  
  Canvas->cd(4);
  wPlusPullPtGenMatch->Draw();
  wPlusPullPtKinSol->Draw("same");
  legend->Draw("same");       
  Canvas->cd(5);
  wPlusPullEtaGenMatch->Draw();  
  wPlusPullEtaKinSol->Draw("same"); 
  legend->Draw("same"); 
  Canvas->cd(6);
  wPlusPullMassKinSol->Draw();
  wPlusPullMassGenMatch->Draw("same");
  legend->Draw("same");        
  Canvas->cd(); 
  Canvas->Update();           
  Canvas->Clear(); 

  const size_t NumColors = 20;    
  Int_t palette[NumColors];
    
  for(size_t i=0;i<NumColors;i++){
    TColor* color = new TColor(2000+i, 0.8-(0.8*i/(NumColors*1.0)), 0.8-(0.8*i/(NumColors*1.0)), 1);
    palette[i] = 2000+i ;               
  }  
  gStyle->SetPalette(NumColors,palette);
  
  Canvas->Divide(1,3); 
  Canvas->cd(1);
  Canvas->cd(1)->SetTheta(50);  
  Canvas->cd(1)->SetPhi(250);       
  genNeutrinoSpectrum->Draw("LEGO2 FB 0");
  Canvas->cd(2);
  Canvas->cd(2)->SetTheta(50);  
  Canvas->cd(2)->SetPhi(250);     
  kinNeutrinoSpectrum->Draw("LEGO2 FB 0");
  Canvas->cd(3); 
  Canvas->cd(3)->SetTheta(50);  
  Canvas->cd(3)->SetPhi(250);    
  matchNeutrinoSpectrum->Draw("LEGO2 FB 0");
  Canvas->cd(); 
  Canvas->Update();           
  Canvas->Clear();  
  
  Canvas->Divide(2,3);  
  Canvas->cd(1);
  topMassDiffKinSol->Draw();  
  Canvas->cd(2);
  topMassDiffGenMatch->Draw(); 
  Canvas->cd(3);
  solWeight->Draw();    
  Canvas->cd(4);
  solWeightVsTopPullMass->Draw("BOX");   
  Canvas->cd(5);
  genMatchDr->Draw();   
  Canvas->cd(6);
  genMatchDrVsTopPullMass->Draw("BOX");   
  Canvas->Update();
       
  Canvas->Close();  
}
