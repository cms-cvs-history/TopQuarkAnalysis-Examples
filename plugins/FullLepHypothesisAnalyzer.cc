#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

#include "TopQuarkAnalysis/Examples/plugins/FullLepHypothesisAnalyzer.h"

FullLepHypothesisAnalyzer::FullLepHypothesisAnalyzer(const edm::ParameterSet& cfg):
  fullLepEvt_  (cfg.getParameter<edm::InputTag>("fullLepEvent")),
  hypoClassKey_(cfg.getParameter<edm::InputTag>("hypoClassKey"))
{
}

void
FullLepHypothesisAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get a handle for the TtFullLeptonicEvent and a key to the hypothesis
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  edm::Handle<TtFullLeptonicEvent> fullLepEvt;
  event.getByLabel(fullLepEvt_, fullLepEvt);

  edm::Handle<int> hypoClassKeyHandle;
  event.getByLabel(hypoClassKey_, hypoClassKeyHandle);
  TtFullLeptonicEvent::HypoClassKey& hypoClassKey = (TtFullLeptonicEvent::HypoClassKey&) *hypoClassKeyHandle;

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // check if hypothesis is available and valid in this event
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if( !fullLepEvt->isHypoValid(hypoClassKey) ){
    edm::LogInfo("HypothesisAnalyzer") << "Hypothesis not valid for this event";
    return;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get reconstructed top quarks and W bosons from the hypothesis
  //////////////////////////////////////////////////////////////////////////////////////////////////

  const reco::Candidate* top    = fullLepEvt->top(hypoClassKey);
  const reco::Candidate* topBar = fullLepEvt->topBar(hypoClassKey);
  
  const reco::Candidate* wPlus  = fullLepEvt->wPlus(hypoClassKey);
  const reco::Candidate* wMinus = fullLepEvt->wMinus(hypoClassKey); 

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill simple histograms with pt, eta and the masses of the reconstructed particles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if(top) {
    topPt_  ->Fill( top->pt()   );
    topEta_ ->Fill( top->eta()  );
    topMass_->Fill( top->mass() );
  }

  if(topBar) {
    topBarPt_  ->Fill( topBar->pt()   );
    topBarEta_ ->Fill( topBar->eta()  );
    topBarMass_->Fill( topBar->mass() );
  }
   if(wPlus) {
    wPlusPt_  ->Fill( wPlus->pt()   );
    wPlusEta_ ->Fill( wPlus->eta()  );
    wPlusMass_->Fill( wPlus->mass() );
  }

  if(wMinus) {
    wMinusPt_  ->Fill( wMinus->pt()   );
    wMinusEta_ ->Fill( wMinus->eta()  );
    wMinusMass_->Fill( wMinus->mass() );
  } 
  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // get genParticles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  const reco::GenParticle* genTop   = fullLepEvt->genTop();
  const reco::GenParticle* genWPlus = fullLepEvt->genWPlus();

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill pull histograms for pt, eta and the masses of the reconstructed with respect to the generated particles
  //////////////////////////////////////////////////////////////////////////////////////////////////

  if(top && genTop) {
    topPullPt_  ->Fill( (top->pt()   - genTop->pt())   / genTop->pt()   );
    topPullEta_ ->Fill( (top->eta()  - genTop->eta())  / genTop->eta()  );
    topPullMass_->Fill( (top->mass() - genTop->mass()) / genTop->mass() );
  }

  if(wPlus && genWPlus) {
    wPlusPullPt_  ->Fill( (wPlus->pt()   - genWPlus->pt())   / genWPlus->pt()   );
    wPlusPullEta_ ->Fill( (wPlus->eta()  - genWPlus->eta())  / genWPlus->eta()  );
    wPlusPullMass_->Fill( (wPlus->mass() - genWPlus->mass()) / genWPlus->mass() );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // plot reconstructed and generated neutrino spectrum
  //////////////////////////////////////////////////////////////////////////////////////////////////

  const reco::Candidate* nu    = fullLepEvt->neutrino(hypoClassKey);
  const reco::Candidate* nuBar = fullLepEvt->neutrinoBar(hypoClassKey);
  
  const reco::GenParticle* genNu    = fullLepEvt->genNeutrino();
  const reco::GenParticle* genNuBar = fullLepEvt->genNeutrinoBar();  

  neutrinoSpectrum_->Fill(nu->energy(), nuBar->energy());
  genNeutrinoSpectrum_->Fill(genNu->energy(), genNuBar->energy());  

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // fill histograms with variables describing the quality of the hypotheses
  //////////////////////////////////////////////////////////////////////////////////////////////////

  topMassDiff_->Fill(top->mass() - topBar->mass());

  solWeight_->Fill(fullLepEvt->solWeight());
  genMatchDr_->Fill(fullLepEvt->genMatchSumDR());  

  if(top && genTop) {
    solWeightVsTopPullMass_ ->Fill((top->mass() - genTop->mass()) / genTop->mass(), fullLepEvt->solWeight());
    genMatchDrVsTopPullMass_->Fill((top->mass() - genTop->mass()) / genTop->mass(), fullLepEvt->genMatchSumDR());
  }      
}

void 
FullLepHypothesisAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // book histograms
  //////////////////////////////////////////////////////////////////////////////////////////////////

  topPt_   = fs->make<TH1F>("topPt"  , "p_{t} (top) [GeV]", 50,  0., 500.);
  topEta_  = fs->make<TH1F>("topEta" , "#eta (top)"       , 50,  -5., 5. );  
  topMass_ = fs->make<TH1F>("topMass", "m (top) [GeV]"    , 50,  0., 350.);  
  
  topBarPt_   = fs->make<TH1F>("topBarPt"  , "p_{t} (topBar) [GeV]", 50,  0., 500.);
  topBarEta_  = fs->make<TH1F>("topBarEta" , "#eta (topBar)"       , 50,  -5., 5. );  
  topBarMass_ = fs->make<TH1F>("topBarMass", "m (topBar) [GeV]"    , 50,  0., 350.);    
  
  wPlusPt_   = fs->make<TH1F>("wPlusPt"  , "p_{t} (wPlus) [GeV]", 50,  0., 500.);
  wPlusEta_  = fs->make<TH1F>("wPlusEta" , "#eta (wPlus)"       , 50,  -5., 5. );  
  wPlusMass_ = fs->make<TH1F>("wPlusMass", "m (wPlus) [GeV]"    , 50,  0., 350.); 
   
  wMinusPt_   = fs->make<TH1F>("wMinusPt"  , "p_{t} (wMinus) [GeV]", 50,  0., 500.);
  wMinusEta_  = fs->make<TH1F>("wMinusEta" , "#eta (wMinus)"       , 50,  -5., 5. );  
  wMinusMass_ = fs->make<TH1F>("wMinusMass", "m (wMinus) [GeV]"    , 50,  0., 350.);  
  
  topPullPt_   = fs->make<TH1F>("topPullPt"  , "(p_{t,rec}-p_{t,gen})/p_{t,gen} (t)"   , 40, -1., 1.);
  topPullEta_  = fs->make<TH1F>("topPullEta" , "(#eta_{rec}-#eta_{gen})/#eta_{gen} (t)", 60, -3., 3.);  
  topPullMass_ = fs->make<TH1F>("topPullMass", "(M_{rec}-M_{gen})/M_{gen} (t)"         , 40, -1., 1.); 
     
  wPlusPullPt_   = fs->make<TH1F>("wPlusPullPt"  , "(p_{t,rec}-p_{t,gen})/p_{t,gen} (W^{+})"   , 40, -1., 1.);
  wPlusPullEta_  = fs->make<TH1F>("wPlusPullEta" , "(#eta_{rec}-#eta_{gen})/#eta_{gen} (W^{+})", 60, -3., 3.);  
  wPlusPullMass_ = fs->make<TH1F>("wPlusPullMass", "(M_{rec}-M_{gen})/M_{gen} (W^{+})"         , 40, -1., 1.);    

  neutrinoSpectrum_ = fs->make<TH2F>("neutrinoSpectrum",
			             "E (#nu) vs E (#bar{#nu})",
			             20, 0., 200., 20, 0., 200.); 
				     
  genNeutrinoSpectrum_ = fs->make<TH2F>("genNeutrinoSpectrum",
			                "E (#nu_{gen}) vs E (#bar{#nu_{gen}})",
			                20, 0., 200., 20, 0., 200.); 				     

  topMassDiff_ = fs->make<TH1F>("topMassDiff", "m (top) - m (anti top)", 100, -50., 50.);

  solWeight_ = fs->make<TH1F>("solWeight", "Kin Solution Weight", 50, 0., 1.);

  solWeightVsTopPullMass_ = fs->make<TH2F>("solWeightVsTopPullMass",
					    "Solution Weight vs. (M_{rec}-M_{gen})/M_{gen} (t))",
					    40, -1., 1., 50, 0., 1.); 

  genMatchDr_ = fs->make<TH1F>("genMatchDr", "GenMatch #Sigma #Delta R", 40, 0., 4.);

  genMatchDrVsTopPullMass_ = fs->make<TH2F>("genMatchDrVsTopPullMass",
					    "GenMatch #Sigma #Delta R vs. (M_{rec}-M_{gen})/M_{gen} (t))",
					    40, -1., 1., 40, 0., 4.); 					   					        
}

void
FullLepHypothesisAnalyzer::endJob() 
{
}
