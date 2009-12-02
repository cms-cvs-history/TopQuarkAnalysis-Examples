#include <vector>
#include <iostream>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TROOT.h>

void setHistoStyle(TH1* hist, unsigned int i, bool norm = false);

void drawStack(THStack* stack, TH1F* hist, bool norm = false, double max = 0.2);

void analyzeTopHypothesesComparison(TString ComparisonFile = "analyzeTopHypothesisBTagHadCor.root")
{

  // open input file
  std::vector<TFile*> files_;
  files_.push_back(new TFile("analyzeTopHypothesis.root"));
  files_.push_back(new TFile(ComparisonFile));

  TString directories[3] = {"analyzeGenMatch",
			    "analyzeMaxSumPtWMass",
			    "analyzeGeom"};

  gROOT->cd();
  gROOT->SetStyle("Plain");

  // get histograms
  
  TH1F* hadWPt  [6];
  TH1F* hadWEta [6];
  TH1F* hadWMass[6];

  TH1F* hadWPullPt  [6];
  TH1F* hadWPullEta [6];
  TH1F* hadWPullMass[6];

  TH1F* hadTopPt  [6];
  TH1F* hadTopEta [6];
  TH1F* hadTopMass[6];

  TH1F* hadTopPullPt  [6];
  TH1F* hadTopPullEta [6];
  TH1F* hadTopPullMass[6];

  for(unsigned int j = 0; j < 2; j++) {
  for(unsigned int i = 0; i < 3; i++) {
    hadWPt  [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWPt"  )->Clone();
    hadWEta [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWEta" )->Clone();
    hadWMass[i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWMass")->Clone();

    hadWPullPt  [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWPullPt"  )->Clone();
    hadWPullEta [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWPullEta" )->Clone();
    hadWPullMass[i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadWPullMass")->Clone();

    hadTopPt  [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopPt"  )->Clone();
    hadTopEta [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopEta" )->Clone();
    hadTopMass[i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopMass")->Clone();

    hadTopPullPt  [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopPullPt"  )->Clone();
    hadTopPullEta [i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopPullEta" )->Clone();
    hadTopPullMass[i+3*j] = (TH1F*) files_[j]->Get(directories[i]+"/hadTopPullMass")->Clone();
  }
  }
  TH1F* genMatchDr = (TH1F*) files_[0]->Get("analyzeGenMatch/genMatchDr")->Clone();

  TH2F* genMatchDrVsHadTopPullMass = (TH2F*) files_[0]->Get("analyzeGenMatch/genMatchDrVsHadTopPullMass")->Clone();

  // close input file

  //file->Close();

  // configure histograms
  for(unsigned int j = 0; j < 2; j++) {
  for(unsigned int i = 0; i < 3; i++) {
    setHistoStyle(hadWEta [i+3*j], i);
    setHistoStyle(hadWMass[i+3*j], i);

    setHistoStyle(hadWPullEta [i+3*j], i, true);
    setHistoStyle(hadWPullMass[i+3*j], i, true);

    setHistoStyle(hadTopEta [i+3*j], i);
    setHistoStyle(hadTopMass[i+3*j], i);

    setHistoStyle(hadTopPullEta [i+3*j], i, true);
    setHistoStyle(hadTopPullMass[i+3*j], i, true);
  }
  }
  setHistoStyle(genMatchDr, 0);
  //  setHistoStyle(mvaDisc, 2);

  setHistoStyle(genMatchDrVsHadTopPullMass, 0);
  //  setHistoStyle(mvaDiscVsHadTopPullMass, 2);

  genMatchDrVsHadTopPullMass->SetFillStyle(0);

  genMatchDrVsHadTopPullMass->SetXTitle("(M_{rec}-M_{gen})/M_{gen} (t_{had})");
  genMatchDrVsHadTopPullMass->SetYTitle("GenMatch #Sigma #Delta R");

//   mvaDiscVsHadTopPullMass->SetXTitle("(M_{rec}-M_{gen})/M_{gen} (t_{had})");
//   mvaDiscVsHadTopPullMass->SetYTitle("MVA discriminator");

  // use THStack to create histogram collections

  THStack* stackHadWEta  = new THStack("stackHadWEta", "");
  THStack* stackHadWMass = new THStack("stackHadWMass", "");

  THStack* stackHadWPullEta  = new THStack("stackHadWPullEta", "");
  THStack* stackHadWPullMass = new THStack("stackHadWPullMass", "");

  THStack* stackHadTopEta  = new THStack("stackHadTopEta", "");
  THStack* stackHadTopMass = new THStack("stackHadTopMass", "");

  THStack* stackHadTopPullEta  = new THStack("stackHadTopPullEta", "");
  THStack* stackHadTopPullMass = new THStack("stackHadTopPullMass", "");

  THStack* stackHadWEtaBTagHadCor  = new THStack("stackHadWEtaBTagHadCor", "");
  THStack* stackHadWMassBTagHadCor = new THStack("stackHadWMassBTagHadCor", "");

  THStack* stackHadWPullEtaBTagHadCor  = new THStack("stackHadWPullEtaBTagHadCor", "");
  THStack* stackHadWPullMassBTagHadCor = new THStack("stackHadWPullMassBTagHadCor", "");

  THStack* stackHadTopEtaBTagHadCor  = new THStack("stackHadTopEtaBTagHadCor", "");
  THStack* stackHadTopMassBTagHadCor = new THStack("stackHadTopMassBTagHadCor", "");

  THStack* stackHadTopPullEtaBTagHadCor  = new THStack("stackHadTopPullEtaBTagHadCor", "");
  THStack* stackHadTopPullMassBTagHadCor = new THStack("stackHadTopPullMassBTagHadCor", "");

  for(unsigned int i = 0; i < 3; i++) {
    stackHadWEta ->Add(hadWEta [i]);
    stackHadWMass->Add(hadWMass[i]);

    stackHadWPullEta ->Add(hadWPullEta [i]);
    stackHadWPullMass->Add(hadWPullMass[i]);

    stackHadTopEta ->Add(hadTopEta [i]);
    stackHadTopMass->Add(hadTopMass[i]);

    stackHadTopPullEta ->Add(hadTopPullEta [i]);
    stackHadTopPullMass->Add(hadTopPullMass[i]);

    stackHadWEtaBTagHadCor ->Add(hadWEta [i+3]);
    stackHadWMassBTagHadCor->Add(hadWMass[i+3]);

    stackHadWPullEtaBTagHadCor ->Add(hadWPullEta [i+3]);
    stackHadWPullMassBTagHadCor->Add(hadWPullMass[i+3]);

    stackHadTopEtaBTagHadCor ->Add(hadTopEta [i+3]);
    stackHadTopMassBTagHadCor->Add(hadTopMass[i+3]);

    stackHadTopPullEtaBTagHadCor ->Add(hadTopPullEta [i+3]);
    stackHadTopPullMassBTagHadCor->Add(hadTopPullMass[i+3]);
  }

  // create a legend

  TLegend *legend = new TLegend(0.1, 0.65, 0.45, 0.9);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.045);
  legend->AddEntry(hadWEta[0], "GenMatch"     , "F");
  legend->AddEntry(hadWEta[1], "MaxSumPtWMass", "L");
  legend->AddEntry(hadWEta[2], "Geom"         , "L");

  TLegend *legend1 = new TLegend(0.55, 0.8, 0.9, 0.9, "without");
  legend1->SetFillStyle(0);
  legend1->SetBorderSize(0);
  legend1->SetTextSize(0.08);
  legend1->SetTextColor(kRed);

  TLegend *legend2 = new TLegend(0.55, 0.8, 0.9, 0.9, "with");
  legend2->SetFillStyle(0);
  legend2->SetBorderSize(0);
  legend2->SetTextSize(0.08);
  legend2->SetTextColor(kRed);

  TLegend *legend3 = new TLegend(0.55, 0.7, 0.9, 0.8, "btag and hadCor");
  legend3->SetFillStyle(0);
  legend3->SetBorderSize(0);
  legend3->SetTextSize(0.06);
  legend3->SetTextColor(kRed);

  // draw canvas for the hadronic W eta

  TCanvas* canvasHadWEta = new TCanvas("canvasHadWEta", "hadronic W eta", 900, 600);
  canvasHadWEta->Divide(2,2);

  canvasHadWEta->cd(1);
  drawStack(stackHadWPullEta, hadWPullEta[0], true, 0.22);
  legend->Draw();
  legend1->Draw();
  legend3->Draw();

  canvasHadWEta->cd(2);
  drawStack(stackHadWPullEtaBTagHadCor, hadWPullEta[0], true, 0.22);
  legend2->Draw();
  legend3->Draw();

  canvasHadWEta->cd(3);
  drawStack(stackHadWEta, hadWEta[0]);
  
  canvasHadWEta->cd(4);
  drawStack(stackHadWEtaBTagHadCor, hadWEta[0]);

  // draw canvas for the hadronic W mass

  TCanvas* canvasHadWMass = new TCanvas("canvasHadWMass", "hadronic W mass", 900, 600);
  canvasHadWMass->Divide(2,2);

  canvasHadWMass->cd(1);
  drawStack(stackHadWPullMass, hadWPullMass[0], true, 0.12);
  legend->Draw();
  legend1->Draw();
  legend3->Draw();
  
  canvasHadWMass->cd(2);
  drawStack(stackHadWPullMassBTagHadCor, hadWPullMass[0], true, 0.12);
  legend2->Draw();
  legend3->Draw();

  canvasHadWMass->cd(3);
  drawStack(stackHadWMass, hadWMass[0]);
  
  canvasHadWMass->cd(4);
  drawStack(stackHadWMassBTagHadCor, hadWMass[0]);

  // draw canvas for the hadronic top eta

  TCanvas* canvasHadTopEta = new TCanvas("canvasHadTopEta", "hadronic top eta", 900, 600);
  canvasHadTopEta->Divide(2,2);

  canvasHadTopEta->cd(1);
  drawStack(stackHadTopPullEta, hadTopPullEta[0], true, 0.2);
  legend->Draw();
  legend1->Draw();
  legend3->Draw();
  
  canvasHadTopEta->cd(2);
  drawStack(stackHadTopPullEtaBTagHadCor, hadTopPullEta[3], true, 0.2);
  legend2->Draw();
  legend3->Draw();

  canvasHadTopEta->cd(3);
  drawStack(stackHadTopEta, hadTopEta[0]);
  
  canvasHadTopEta->cd(4);
  drawStack(stackHadTopEtaBTagHadCor, hadTopEta[3]);

  // draw canvas for the hadronic top mass

  TCanvas* canvasHadTopMass = new TCanvas("canvasHadTopMass", "hadronic top mass", 900, 600);
  canvasHadTopMass->Divide(2,2);

  canvasHadTopMass->cd(1);
  drawStack(stackHadTopPullMass, hadTopPullMass[0], true, 0.12);
  legend->Draw();
  legend1->Draw();
  legend3->Draw();
  
  canvasHadTopMass->cd(2);
  drawStack(stackHadTopPullMassBTagHadCor, hadTopPullMass[3], true, 0.12);
  legend2->Draw();
  legend3->Draw();

  canvasHadTopMass->cd(3);
  drawStack(stackHadTopMass, hadTopMass[0]);
  
  canvasHadTopMass->cd(4);
  drawStack(stackHadTopMassBTagHadCor, hadTopMass[3]);

  // draw canvas with quality criteria of GenMatch and MVADisc hypotheses

  TCanvas* canvasQuali = new TCanvas("canvasQuali", "quality criteria of hypotheses", 900, 460);
  canvasQuali->Divide(2,1);

  canvasQuali->cd(1);
  genMatchDr->Draw();

  canvasQuali->cd(2);
  genMatchDrVsHadTopPullMass->Draw("box");

//   canvasQuali->cd(4);
//   mvaDisc->Draw();

//   canvasQuali->cd(5);
//   mvaDiscVsHadTopPullMass->Draw("box");

  // write postscript file

  canvasHadWEta   ->Print("analyzeTopHypothesesComparison.ps(");
  canvasHadWMass  ->Print("analyzeTopHypothesesComparison.ps");
  canvasHadTopEta ->Print("analyzeTopHypothesesComparison.ps");
  canvasHadTopMass->Print("analyzeTopHypothesesComparison.ps");
  canvasQuali     ->Print("analyzeTopHypothesesComparison.ps)");

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

void drawStack(THStack* stack, TH1F* hist, bool norm, double max) {

  stack->Draw("nostack");
  stack->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
  stack->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());
  stack->Draw("nostack");
  stack->GetXaxis()->SetLabelSize(0.05);
  stack->GetXaxis()->SetTitleSize(0.05);
  stack->GetYaxis()->SetLabelSize(0.05);
  stack->GetYaxis()->SetTitleSize(0.05);

  if(norm)stack->SetMaximum(max);
  
}
