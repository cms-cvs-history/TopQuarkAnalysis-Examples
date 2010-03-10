#include "TopQuarkAnalysis/Examples/plugins/BtagFilter.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

BtagFilter::BtagFilter(const edm::ParameterSet& cfg):
  hypoKey_    (cfg.getParameter<edm::InputTag>(       "hypoKey"        )),
  FullLepEvt_ (cfg.getParameter<edm::InputTag>(       "FullLepEvent"   )),
  jets_       (cfg.getParameter<edm::InputTag>(       "jets"           )),         
  bAlgo_      (cfg.getParameter<std::string >(        "bAlgorithm"     )),  
  bDisc_      (cfg.getParameter<std::vector<double> >("bDiscriminator" )),     
  beforeCuts_( 0 ), validCounter_( 0 ), afterCuts_( 0 )
{
}

bool BtagFilter::filter(edm::Event& evt, const edm::EventSetup& setup)
{ 
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get a handle for the TtFullLeptonicEvent and, key to the hypothesis and the jet collection
  //////////////////////////////////////////////////////////////////////////////////////////////////  
  
  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;
  
  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);   

  /// counter for events before cuts
  ++beforeCuts_;
         
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return false;
  }
  if( !FullLepEvt->isHypoValid(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    return false; 
  }
 
  // counter to count valid events
  ++validCounter_;

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get the indices of the jets from FullLepEvent ...
  ////////////////////////////////////////////////////////////////////////////////////////////////// 
  
  int bJetIdx    = FullLepEvt->jetLeptonCombination(hypoKey)[0];
  int bBarJetIdx = FullLepEvt->jetLeptonCombination(hypoKey)[1];  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // ... and get the jets using these indices
  ////////////////////////////////////////////////////////////////////////////////////////////////// 

  const pat::Jet B    = jets->at(bJetIdx);   
  const pat::Jet BBar = jets->at(bBarJetIdx);   

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // make b-tagging cuts
  ////////////////////////////////////////////////////////////////////////////////////////////////// 
  
  if(bDisc_.size()==1){
    if(!(B.bDiscriminator(bAlgo_)>=bDisc_[0] || BBar.bDiscriminator(bAlgo_)>=bDisc_[0])) return false;
  }
  else if(bDisc_.size()==2){
    if((B.bDiscriminator(bAlgo_)<bDisc_[0] || BBar.bDiscriminator(bAlgo_)<bDisc_[1]) 
      && (B.bDiscriminator(bAlgo_)<bDisc_[1] || BBar.bDiscriminator(bAlgo_)<bDisc_[0])) return false;
  } 
  
  /// counter for events that have passed the b-tagging cuts
  ++afterCuts_;

  return true;
}

void BtagFilter::beginJob()
{   
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // print out of cuts to be applied
  ////////////////////////////////////////////////////////////////////////////////////////////////// 
  
  edm::LogVerbatim log("BtagFilter");
  
  log << "b-tagging algorithm is " << bAlgo_ << " with following cuts \n";
  for(unsigned int i=0; i<bDisc_.size(); ++i){
    log << "  disc " << i+1 << " >= " << bDisc_[i] << "\n"; 
  }    
}

void BtagFilter::endJob()
{

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // result of selection
  ////////////////////////////////////////////////////////////////////////////////////////////////// 

  edm::LogVerbatim log("BtagFilter");

  log << std::setw( 20 ) << std::left  << "ValidityFullLepHyp" << " : "
      << std::setw( 10 ) << std::right << validCounter_ << "  out of "
      << std::setw( 10 ) << std::right << beforeCuts_ << "\n";  
	
  log << std::setw( 20 ) << std::left  << "b-tag cut     " << " : "
      << std::setw( 10 ) << std::right << afterCuts_ << "  out of "
      << std::setw( 10 ) << std::right << validCounter_ << "\n"; 	  	
}
