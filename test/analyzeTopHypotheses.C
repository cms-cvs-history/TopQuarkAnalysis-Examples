#include <iostream>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TROOT.h>

void setHistoStyle(TH1* hist, unsigned int i, bool norm = false);

void drawStack(THStack* stack, TH1F* hist);

void analyzeTopHypotheses()
{

  // open input file

  TFile* file = new TFile("analyzeTopHypothesis.root");

  TString directories[3] = {"analyzeGenMatch",
			    "analyzeMaxSumPtWMass",
			    "analyzeMVADisc"};

  gROOT->cd();
  gROOT->SetStyle("Plain");

  // get histograms
  
  TH1F* hadWPt  [3];
  TH1F* hadWEta [3];
  TH1F* hadWMass[3];

  TH1F* hadWPullPt  [3];
  TH1F* hadWPullEta [3];
  TH1F* hadWPullMass[3];

  TH1F* hadTopPt  [3];
  TH1F* hadTopEta [3];
  TH1F* hadTopMass[3];

  TH1F* hadTopPullPt  [3];
  TH1F* hadTopPullEta [3];
  TH1F* hadTopPullMass[3];

  for(unsigned int i = 0; i < 3; i++) {
    hadWPt  [i] = (TH1F*) file->Get(directories[i]+"/hadWPt"  )->Clone();
    hadWEta [i] = (TH1F*) file->Get(directories[i]+"/hadWEta" )->Clone();
    hadWMass[i] = (TH1F*) file->Get(directories[i]+"/hadWMass")->Clone();

    hadWPullPt  [i] = (TH1F*) file->Get(directories[i]+"/hadWPullPt"  )->Clone();
    hadWPullEta [i] = (TH1F*) file->Get(directories[i]+"/hadWPullEta" )->Clone();
    hadWPullMass[i] = (TH1F*) file->Get(directories[i]+"/hadWPullMass")->Clone();

    hadTopPt  [i] = (TH1F*) file->Get(directories[i]+"/hadTopPt"  )->Clone();
    hadTopEta [i] = (TH1F*) file->Get(directories[i]+"/hadTopEta" )->Clone();
    hadTopMass[i] = (TH1F*) file->Get(directories[i]+"/hadTopMass")->Clone();

    hadTopPullPt  [i] = (TH1F*) file->Get(directories[i]+"/hadTopPullPt"  )->Clone();
    hadTopPullEta [i] = (TH1F*) file->Get(directories[i]+"/hadTopPullEta" )->Clone();
    hadTopPullMass[i] = (TH1F*) file->Get(directories[i]+"/hadTopPullMass")->Clone();
  }

  TH1F* genMatchDr = (TH1F*) file->Get("analyzeGenMatch/genMatchDr")->Clone();
  TH1F* mvaDisc    = (TH1F*) file->Get("analyzeMVADisc/mvaDisc"    )->Clone();

  TH2F* genMatchDrVsHadTopPullMass = (TH2F*) file->Get("analyzeGenMatch/genMatchDrVsHadTopPullMass")->Clone();
  TH2F* mvaDiscVsHadTopPullMass    = (TH2F*) file->Get("analyzeMVADisc/mvaDiscVsHadTopPullMass"    )->Clone();

  // close input file

  file->Close();

  // configure histograms

  for(unsigned int i = 0; i < 3; i++) {
    setHistoStyle(hadWPt  [i], i);
    setHistoStyle(hadWEta [i], i);
    setHistoStyle(hadWMass[i], i);

    setHistoStyle(hadWPullPt  [i], i, true);
    setHistoStyle(hadWPullEta [i], i, true);
    setHistoStyle(hadWPullMass[i], i, true);

    setHistoStyle(hadTopPt  [i], i);
    setHistoStyle(hadTopEta [i], i);
    setHistoStyle(hadTopMass[i], i);

    setHistoStyle(hadTopPullPt  [i], i, true);
    setHistoStyle(hadTopPullEta [i], i, true);
    setHistoStyle(hadTopPullMass[i], i, true);
  }

  setHistoStyle(genMatchDr, 0);
  setHistoStyle(mvaDisc, 2);

  setHistoStyle(genMatchDrVsHadTopPullMass, 0);
  setHistoStyle(mvaDiscVsHadTopPullMass, 2);

  genMatchDrVsHadTopPullMass->SetFillStyle(0);

  genMatchDrVsHadTopPullMass->SetXTitle("(M_{rec}-M_{gen})/M_{gen} (t_{had})");
  genMatchDrVsHadTopPullMass->SetYTitle("GenMatch #Sigma #Delta R");

  mvaDiscVsHadTopPullMass->SetXTitle("(M_{rec}-M_{gen})/M_{gen} (t_{had})");
  mvaDiscVsHadTopPullMass->SetYTitle("MVA discriminator");

  // use THStack to create histogram collections

  THStack* stackHadWPt   = new THStack("stackHadWPt", "");
  THStack* stackHadWEta  = new THStack("stackHadWEta", "");
  THStack* stackHadWMass = new THStack("stackHadWMass", "");

  THStack* stackHadWPullPt   = new THStack("stackHadWPullPt", "");
  THStack* stackHadWPullEta  = new THStack("stackHadWPullEta", "");
  THStack* stackHadWPullMass = new THStack("stackHadWPullMass", "");

  THStack* stackHadTopPt   = new THStack("stackHadTopPt", "");
  THStack* stackHadTopEta  = new THStack("stackHadTopEta", "");
  THStack* stackHadTopMass = new THStack("stackHadTopMass", "");

  THStack* stackHadTopPullPt   = new THStack("stackHadTopPullPt", "");
  THStack* stackHadTopPullEta  = new THStack("stackHadTopPullEta", "");
  THStack* stackHadTopPullMass = new THStack("stackHadTopPullMass", "");

  for(unsigned int i = 0; i < 3; i++) {
    stackHadWPt  ->Add(hadWPt  [i]);
    stackHadWEta ->Add(hadWEta [i]);
    stackHadWMass->Add(hadWMass[i]);

    stackHadWPullPt  ->Add(hadWPullPt  [i]);
    stackHadWPullEta ->Add(hadWPullEta [i]);
    stackHadWPullMass->Add(hadWPullMass[i]);

    stackHadTopPt  ->Add(hadTopPt  [i]);
    stackHadTopEta ->Add(hadTopEta [i]);
    stackHadTopMass->Add(hadTopMass[i]);

    stackHadTopPullPt  ->Add(hadTopPullPt  [i]);
    stackHadTopPullEta ->Add(hadTopPullEta [i]);
    stackHadTopPullMass->Add(hadTopPullMass[i]);
  }

  // create a legend

  TLegend *legend = new TLegend(0.45, 0.65, 0.9, 0.9);
  legend->SetFillStyle(0);
  legend->AddEntry(hadWPt[0], "GenMatch"     , "F");
  legend->AddEntry(hadWPt[1], "MaxSumPtWMass", "L");
  legend->AddEntry(hadWPt[2], "MVADisc"      , "L");

  // draw canvas for the hadronic W

  TCanvas* canvasHadW = new TCanvas("canvasHadW", "hadronic W kinematics", 900, 600);
  canvasHadW->Divide(3,2);

  canvasHadW->cd(1);
  drawStack(stackHadWPt, hadWPt[0]);
  legend->Draw();
  
  canvasHadW->cd(2);
  drawStack(stackHadWEta, hadWEta[0]);
  
  canvasHadW->cd(3);
  drawStack(stackHadWMass, hadWMass[0]);
  
  canvasHadW->cd(4);
  drawStack(stackHadWPullPt, hadWPullPt[0]);
  
  canvasHadW->cd(5);
  drawStack(stackHadWPullEta, hadWPullEta[0]);
  
  canvasHadW->cd(6);
  drawStack(stackHadWPullMass, hadWPullMass[0]);

  // draw canvas for the hadronic top

  TCanvas* canvasHadTop = new TCanvas("canvasHadTop", "hadronic top kinematics", 900, 600);
  canvasHadTop->Divide(3,2);

  canvasHadTop->cd(1);
  drawStack(stackHadTopPt, hadTopPt[0]);
  legend->Draw();
  
  canvasHadTop->cd(2);
  drawStack(stackHadTopEta, hadTopEta[0]);
  
  canvasHadTop->cd(3);
  drawStack(stackHadTopMass, hadTopMass[0]);
  
  canvasHadTop->cd(4);
  drawStack(stackHadTopPullPt, hadTopPullPt[0]);
  
  canvasHadTop->cd(5);
  drawStack(stackHadTopPullEta, hadTopPullEta[0]);
  
  canvasHadTop->cd(6);
  drawStack(stackHadTopPullMass, hadTopPullMass[0]);

  // draw canvas with quality criteria of GenMatch and MVADisc hypotheses

  TCanvas* canvasQuali = new TCanvas("canvasQuali", "quality criteria of hypotheses", 900, 600);
  canvasQuali->Divide(3,2);

  canvasQuali->cd(1);
  genMatchDr->Draw();

  canvasQuali->cd(2);
  genMatchDrVsHadTopPullMass->Draw("box");

  canvasQuali->cd(4);
  mvaDisc->Draw();

  canvasQuali->cd(5);
  mvaDiscVsHadTopPullMass->Draw("box");

  // write postscript file

  canvasHadW  ->Print("analyzeTopHypotheses.ps(");
  canvasHadTop->Print("analyzeTopHypotheses.ps");
  canvasQuali ->Print("analyzeTopHypotheses.ps)");

}

void setHistoStyle(TH1* hist, unsigned int i, bool norm) {

  int lineColors[3] = {kGreen+1, kBlue, kRed};
  int lineStyles[3] = {1, 3, 1};
  int fillColors[3] = {kGreen+1, kBlue, 0};
  int fillStyles[3] = {3554, 0, 0};

  hist->SetLineWidth(2);
  hist->SetLineColor(lineColors[i]);
  hist->SetLineStyle(lineStyles[i]);
  hist->SetFillColor(fillColors[i]);
  hist->SetFillStyle(fillStyles[i]);

  hist->SetXTitle(hist->GetTitle());
  hist->SetYTitle("events");
  hist->SetTitle("");
  hist->SetStats(kFALSE);

  if(norm) {
    hist->Scale(1./hist->Integral());
    hist->SetYTitle("a.u.");
  }

}

void drawStack(THStack* stack, TH1F* hist) {

  stack->Draw("nostack");
  stack->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
  stack->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());
  stack->Draw("nostack");

}
