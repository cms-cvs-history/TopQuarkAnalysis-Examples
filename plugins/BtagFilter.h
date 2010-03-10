#ifndef BtagFilter_h
#define BtagFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

class BtagFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit BtagFilter(const edm::ParameterSet&);
  /// default destructor
  ~BtagFilter(){};
  
 private:
  /// prints out a summary of the applied cuts if 'topFilter' is appended to message logger
  virtual void beginJob();
  /// filters events on validity, invariant dilepton mass and b-taggging 
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  /// gives a summary of how many events passed each cut if 'topFilter' is appended to message logger 
  virtual void endJob();

 private:
  /// choose in config file which hypothesis type you want to be filtered
  edm::InputTag hypoKey_;  
  /// input is the ttFullLepEvent 
  edm::InputTag FullLepEvt_;
  /// needed for b-tagging cuts and has to be the same collection which has been used for event  reconstruction
  edm::InputTag jets_;
  
  /// b-Tagging to be used, default is 'simpleSecondaryVertexBJetTags'  
  std::string bAlgo_;
  /// cut value(s) of the b-tagging discriminator, default is 1 (only one tag required with simpleSV)
  std::vector<double> bDisc_; 

  /// event counter for events before cuts are applied
  unsigned int beforeCuts_;
  /// event counter for events with valid event solution
  unsigned int validCounter_;   
  /// event counter for events after all cuts
  unsigned int afterCuts_;  
};

#endif
