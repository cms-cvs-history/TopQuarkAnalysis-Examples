#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopQuarkAnalysis/Examples/plugins/TopJetAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "PhysicsTools/PatAlgos/interface/KinematicResolutionRcd.h"
#include "PhysicsTools/PatAlgos/interface/KinematicResolutionProvider.h"


TopJetAnalyzer::TopJetAnalyzer(const edm::ParameterSet& cfg):
  input_(cfg.getParameter<edm::InputTag>("input"))
{
  edm::Service<TFileService> fs;
  
  Num_Jets   = fs->make<TH1I>("Number_of_Jets","Num_{Jets}",    10,  0 ,  10 );
  pt_Jets    = fs->make<TH1F>("pt_of_Jets",    "pt_{Jets}",    100,  0., 300.);
  energy_Jets=fs->make<TH1F> ("energy_of_Jets","energy_{Jets}",100,  0., 300.);
  eta_Jets   =fs->make<TH1F> ("eta_of_Jets",   "eta_{Jets}",   100, -3.,   3.);
  phi_Jets   =fs->make<TH1F> ("phi_of_Jets",   "phi_{Jets}",   100, -5.,   5.);
  btag_Jets  =fs->make<TH1F> ("btag_of_Jets",  "btag_{Jet}",   400,-20.,  20.);
}

TopJetAnalyzer::~TopJetAnalyzer()
{
}

void
TopJetAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<std::vector<pat::Jet> > jets;
  evt.getByLabel(input_, jets); 
 
  // to test resolutions
  edm::ESHandle<KinematicResolutionProvider> provider;
  setup.get<KinematicResolutionRcd>().get("jetResolution", provider);
  provider->setup(setup); // this might be needed for some providers
 
  Num_Jets->Fill( jets->size());
  for( std::vector<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
    pt_Jets    ->Fill( jet->pt()    );
    energy_Jets->Fill( jet->energy());
    eta_Jets   ->Fill( jet->eta()   );
    phi_Jets   ->Fill( jet->phi()   );

    std::cout << "test resolution A: " << provider->getResolution(*jet).resolEt(jet->p4()) << std::endl;
    std::cout << "test resolution B: " << jet->resolEt() << std::endl;


    // test JEC from PAT
    if(jet == jets->begin()){
    edm::LogVerbatim log("TopJetAnalyzer_jec");
    log << "--------------------------------\n";
    log << " Jet Energy Correction Factors: \n";
    log << "--------------------------------\n";
    log << "  " << jet->corrStep() << ": " << jet->pt() << " (default) \n";
    log << "--------------------------------\n";
    log << "  " << jet->correctedJet("raw")        .corrStep() << ": " << jet->correctedJet("raw")        .pt() << "\n";
    log << "  " << jet->correctedJet("off")        .corrStep() << ": " << jet->correctedJet("off")        .pt() << "\n";
    log << "  " << jet->correctedJet("rel")        .corrStep() << ": " << jet->correctedJet("rel")        .pt() << "\n";
    log << "  " << jet->correctedJet("abs")        .corrStep() << ": " << jet->correctedJet("abs")        .pt() << "\n";
    log << "  " << jet->correctedJet("emf")        .corrStep() << ": " << jet->correctedJet("emf")        .pt() << "\n";
    log << "  " << jet->correctedJet("had",  "glu").corrStep() << ": " << jet->correctedJet("had",  "glu").pt() << " (gluon )\n";
    log << "  " << jet->correctedJet("had",  "uds").corrStep() << ": " << jet->correctedJet("had",  "uds").pt() << " (uds   )\n";
    log << "  " << jet->correctedJet("had",  "c"  ).corrStep() << ": " << jet->correctedJet("had",  "c"  ).pt() << " (charm )\n";
    log << "  " << jet->correctedJet("had",  "b"  ).corrStep() << ": " << jet->correctedJet("had",  "b"  ).pt() << " (beauty)\n";
    log << "  " << jet->correctedJet("ue",   "glu").corrStep() << ": " << jet->correctedJet("ue",   "glu").pt() << " (gluon )\n";
    log << "  " << jet->correctedJet("ue",   "uds").corrStep() << ": " << jet->correctedJet("ue",   "uds").pt() << " (uds   )\n";
    log << "  " << jet->correctedJet("ue",   "c"  ).corrStep() << ": " << jet->correctedJet("ue",   "c"  ).pt() << " (charm )\n";
    log << "  " << jet->correctedJet("ue",   "b"  ).corrStep() << ": " << jet->correctedJet("ue",   "b"  ).pt() << " (beauty)\n";
    log << "  " << jet->correctedJet("part", "glu").corrStep() << ": " << jet->correctedJet("part", "glu").pt() << " (gluon )\n";
    log << "  " << jet->correctedJet("part", "uds").corrStep() << ": " << jet->correctedJet("part", "uds").pt() << " (uds   )\n";
    log << "  " << jet->correctedJet("part", "c"  ).corrStep() << ": " << jet->correctedJet("part", "c"  ).pt() << " (charm )\n";
    log << "  " << jet->correctedJet("part", "b"  ).corrStep() << ": " << jet->correctedJet("part", "b"  ).pt() << " (beauty)\n";    
   }
    btag_Jets  ->Fill( jet->bDiscriminator("combinedSecondaryVertexBJetTags") );
  }    
}

void TopJetAnalyzer::beginJob(const edm::EventSetup&)
{
}

void TopJetAnalyzer::endJob()
{
}

  
