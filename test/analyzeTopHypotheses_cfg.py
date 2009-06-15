import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.categories.append('HypothesisAnalyzer')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    default             = cms.untracked.PSet( limit = cms.untracked.int32( 0) ),
    TtSemiLeptonicEvent = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    HypothesisAnalyzer  = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
)

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'rfio:/castor/cern.ch/user/r/rwolf/test/patTuple_PATv2_ttbar_tauola_1.root'
     ),
     skipEvents = cms.untracked.uint32(0)
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## simple event selection for semileptonic ttbar events with an isolated muon
process.load("TopQuarkAnalysis.Examples.TtSemiLepEvtSelection_cff")

## sequence for the ttGenEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## sequence for the ttSemiLepEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
process.ttSemiLepEvent.verbosity = 1
## change maximum number of jets taken into account per event (default: 4)
#process.ttSemiLepEvent.maxNJets = 5
## change jet-parton matching algorithm
#process.ttSemiLepJetPartonMatch.algorithm = "unambiguousOnly"

## load HypothesisAnalyzer
process.load("TopQuarkAnalysis.Examples.HypothesisAnalyzer_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTopHypothesis.root')
)

## end path   
process.p1 = cms.Path(process.ttSemiLepEvtSelection *
                      process.makeGenEvt *
                      process.makeTtSemiLepEvent *
                      process.analyzeAllHypotheses)

