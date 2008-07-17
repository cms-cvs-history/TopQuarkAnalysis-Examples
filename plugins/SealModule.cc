#include "TopQuarkAnalysis/Examples/interface/TtSemiEvtKit.h"
#include "TopQuarkAnalysis/Examples/plugins/SemiLepHypothesesAnalyzer.h"

typedef SemiLepHypothesesAnalyzer HypothesisAnalyzer;

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TtSemiEvtKit);
DEFINE_FWK_MODULE(HypothesisAnalyzer);


#include "TopQuarkAnalysis/Examples/plugins/TopMuonAnalyzer.h"
#include "TopQuarkAnalysis/Examples/plugins/TopElecAnalyzer.h"
#include "TopQuarkAnalysis/Examples/plugins/TopJetAnalyzer.h"
DEFINE_FWK_MODULE(TopMuonAnalyzer);
DEFINE_FWK_MODULE(TopElecAnalyzer);
DEFINE_FWK_MODULE(TopJetAnalyzer);


