#include "TopQuarkAnalysis/Examples/interface/TtSemiEvtKit.h"
#include "TopQuarkAnalysis/Examples/plugins/SemiLepHypothesesAnalyzer.h"

typedef SemiLepHypothesesAnalyzer HypothesisAnalyzer;

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TtSemiEvtKit);
DEFINE_FWK_MODULE(HypothesisAnalyzer);

