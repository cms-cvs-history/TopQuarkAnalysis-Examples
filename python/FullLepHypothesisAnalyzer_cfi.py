import FWCore.ParameterSet.Config as cms

#
# module to make simple analyses of top event hypotheses
#
analyzeFullLepHypothesis = cms.EDAnalyzer("FullLepHypothesisAnalyzer",
    fullLepEvent = cms.InputTag("ttFullLepEvent"),
    hypoClassKey = cms.InputTag("ttFullLepHypMaxSumPtWMass","Key")
)


