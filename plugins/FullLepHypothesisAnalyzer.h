#ifndef FullLepHypothesisAnalyzer_h
#define FullLepHypothesisAnalyzer_h

#include "TH1F.h"
#include "TH2F.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"

class FullLepHypothesisAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit FullLepHypothesisAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~FullLepHypothesisAnalyzer(){};
  
 private:
  /// things that have to be done before event loop: book histograms
  virtual void beginJob();
  /// analysis in event loop
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// empty
  virtual void endJob();

  /// choose in config file which hypothesis type you want to be filtered
  edm::InputTag fullLepEvt_;
  /// choose in config file which hypothesis type you want to analyze
  edm::InputTag hypoClassKey_;

  /// kinematic histograms
  TH1F* topPt_;
  TH1F* topEta_;
  TH1F* topMass_;  
  TH1F* topBarPt_;
  TH1F* topBarEta_;
  TH1F* topBarMass_;    
  TH1F* wPlusPt_;
  TH1F* wPlusEta_;
  TH1F* wPlusMass_;    
  TH1F* wMinusPt_;
  TH1F* wMinusEta_;
  TH1F* wMinusMass_;  
  
  /// pull histograms
  TH1F* topPullPt_;
  TH1F* topPullEta_;
  TH1F* topPullMass_;    
  TH1F* wPlusPullPt_;
  TH1F* wPlusPullEta_;
  TH1F* wPlusPullMass_; 

  /// reconstructed neutrino spectrum
  TH2F* neutrinoSpectrum_;
  /// generated neutrino spectrum
  TH2F* genNeutrinoSpectrum_;  
  /// difference between top and anti-top mass
  TH1F* topMassDiff_; 
  /// propability weight of kinematic solution 
  TH1F* solWeight_; 
  /// deltaR sum of GenMatch hypothesis    
  TH1F* genMatchDr_;    
};

#endif
