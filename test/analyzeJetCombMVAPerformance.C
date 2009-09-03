#include <iomanip>
#include <iostream>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TSystem.h>

void Draw(const TString& title, TH1F* h_sig, TH1F* h_bkg = 0, const bool yMaxToOne = false, const bool drawLegend = false);

void analyzeJetCombMVAPerformance()
{

  // get histograms from file

  TFile *file = new TFile("train_monitoring.root");

  gROOT->cd();

  TH1F* h_hyp_discr[2];

  h_hyp_discr[0] = (TH1F*) (file->Get("input_norm_monitor_hyp/like_discr_bkg"))->Clone();
  h_hyp_discr[1] = (TH1F*) (file->Get("input_norm_monitor_hyp/like_discr_sig"))->Clone();

  TH1F* h_evt_discr[2];

  h_evt_discr[0] = (TH1F*) (file->Get("input_norm_monitor_evt/split_best_discr_bkg"))->Clone();
  h_evt_discr[1] = (TH1F*) (file->Get("input_norm_monitor_evt/split_best_discr_sig"))->Clone();

  file->Close();

  // calculate efficiency and purity

  double xbins[h_evt_discr[1]->GetNbinsX()+2];
  xbins[0] = 0.0;
  for(unsigned int b = 1; b <= (unsigned) h_evt_discr[1]->GetNbinsX()+1; b++)
    xbins[b] = h_evt_discr[1]->GetBinLowEdge(b);

  TH1F* h_eff = new TH1F("h_eff", "efficiency", h_evt_discr[1]->GetNbinsX()+1, xbins);
  TH1F* h_pur = new TH1F("h_pur", "purity"    , h_evt_discr[1]->GetNbinsX()+1, xbins);

  double sumSig = 0.;
  double sumBkg = 0.;
  for(unsigned int b = h_eff->GetNbinsX(); b >= 1; b--) {
    if( b > 1 ) { // exclude underflow bin (best_discr histos have one bin less than h_eff)
      sumSig += h_evt_discr[1]->GetBinContent(b-1);
      sumBkg += h_evt_discr[0]->GetBinContent(b-1);
    }
    h_eff->SetBinContent(b, sumSig/(h_evt_discr[0]->GetEntries()+h_evt_discr[1]->GetEntries()) );
    if(sumSig+sumBkg != 0.)
      h_pur->SetBinContent(b, sumSig/(sumSig+sumBkg) );
    else
      h_pur->SetBinContent(b, 1.);
  }

  // configure histograms

  int fillColor[2] = {2, 0};
  int lineColor[2] = {2, 4};
  int fillStyle[2] = {3554, 1};

  for(unsigned s=0; s<2; s++) {
    h_hyp_discr[s]->SetFillColor(fillColor[s]);
    h_evt_discr[s]->SetFillColor(fillColor[s]);

    h_hyp_discr[s]->SetLineColor(lineColor[s]);
    h_evt_discr[s]->SetLineColor(lineColor[s]);

    h_hyp_discr[s]->SetLineWidth(2);
    h_evt_discr[s]->SetLineWidth(2);

    h_hyp_discr[s]->SetFillStyle(fillStyle[s]);
    h_evt_discr[s]->SetFillStyle(fillStyle[s]);
  }

  h_eff->SetLineColor(lineColor[1]);
  h_pur->SetLineColor(lineColor[1]);

  h_eff->SetLineWidth(2);
  h_pur->SetLineWidth(2);

  // create canvas

  gROOT->SetStyle("Plain");

  TCanvas *canvas = new TCanvas("JetCombMVAPerformace", "JetCombMVAPerformance", 600, 600);
  canvas->Divide(2,2);

  // draw histograms

  TString plotDir = "JetCombMVAPerformace_plots";
  gSystem->mkdir(plotDir);

  canvas->cd(1);
  Draw("all hypotheses", h_hyp_discr[1], h_hyp_discr[0], false, true);
  gPad->Print(plotDir + "/allHyps.eps");

  canvas->cd(2);
  Draw("best hypothesis per event", h_evt_discr[1], h_evt_discr[0]);
  gPad->Print(plotDir + "/bestHyp.eps");

  canvas->cd(3);
  Draw("cut efficiencies", h_eff, 0, true);
  gPad->Print(plotDir + "/efficiency.eps");

  canvas->cd(4);
  Draw("cut purities", h_pur, 0, true);
  gPad->Print(plotDir + "/purity.eps");

  canvas->Print(plotDir + "/summary.ps");

  // provide tabular printout

  std::cout << "========================================" << std::endl
	    << "discr. cut    efficiency      purity    " << std::endl
	    << "----------------------------------------" << std::endl;

  for(double d = 0.00; d < 1.00; d += 0.05) {
    double e = h_eff->GetBinContent( h_eff->FindBin(d) );
    double p = h_pur->GetBinContent( h_pur->FindBin(d) );
    std::cout << std::fixed << std::setprecision(2)
	      << std::setw(7) << d
	      << std::setw(14) << e
	      << std::setw(14) << p
	      << std::endl;
  }

  std::cout << "========================================" << std::endl;

}

void Draw(const TString& title, TH1F* h_sig, TH1F* h_bkg, const bool yMaxToOne, const bool drawLegend)
{

  Double_t yMax = h_sig->GetMaximum();
  if(h_bkg && !yMaxToOne) yMax = 1.05 * TMath::Max(h_sig->GetMaximum(), h_bkg->GetMaximum());
  if(yMaxToOne) {
    yMax = 1.005;
    gPad->SetGridy();
  }

  TH1F *tmp = new TH1F("h_tmp", title, 1, 0.0, 1.02);
  tmp->SetStats(kFALSE);
  tmp->GetYaxis()->SetRangeUser(0.0, yMax);
  tmp->SetXTitle("discriminator");

  tmp->Draw();

  if(drawLegend) {
    TLegend *leg = new TLegend(0.6 - gPad->GetRightMargin(),
			       1.0 - gPad->GetTopMargin() - 0.15,
			       1.0 - gPad->GetRightMargin(),
			       1.0 - gPad->GetTopMargin());
    leg->SetFillStyle(0);
    leg->AddEntry(h_sig, "Signal", "F");
    if(h_bkg) leg->AddEntry(h_bkg, "Background", "F");
    leg->SetBorderSize(1);
    leg->SetMargin(0.3);
    leg->Draw("same");
  }

  if(h_bkg) h_bkg->Draw("same");
  h_sig->Draw("same");

  gPad->RedrawAxis();

}
