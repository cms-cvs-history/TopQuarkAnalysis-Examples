import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_1.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_2.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_3.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_4.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_5.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_6.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_7.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_8.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_9.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_10.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_11.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_12.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_13.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_14.root',
    'rfio:/castor/cern.ch/user/h/henderle/ttbar/patTuple_15.root'
     ),
     skipEvents = cms.untracked.uint32(0)                            
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## sequences for ttGenEvent and TtSemiLeptonicEvent
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
## enable additional per-event printout from the TtSemiLeptonicEvent
#process.ttSemiLepEvent.verbosity = 1
## change jet-parton matching algorithm
#process.ttSemiLepJetPartonMatch.algorithm = "unambiguousOnly"

## use b-tagging two distinguish between light and b jets
process.ttSemiLepHypGeom.useBTagging = False
## choose algorithm for b-tagging
process.ttSemiLepHypGeom.bTagAlgorithm = "trackCountingHighEffBJetTags"
## minimum b discriminator value required for b jets
process.ttSemiLepHypGeom.minBDiscBJets     = 1.90
## maximum b discriminator value allowed for non-b jets
process.ttSemiLepHypGeom.maxBDiscLightJets = 3.99
## specify jet correction level
process.ttSemiLepHypGeom.jetCorrectionLevel = "abs"

## choose which hypotheses to produce
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import addTtSemiLepHypotheses
addTtSemiLepHypotheses(process,
                       ["kMaxSumPtWMass", "kGeom"]
                       )

## change some attribute for all hypotheses
#setForAllTtSemiLepHypotheses(process, "maxNJets", 5) # default: 4

## load HypothesisAnalyzer
process.load("TopQuarkAnalysis.Examples.HypothesisAnalyzer_cff")

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTopHypothesis.root')
)

## end path   
process.path = cms.Path(process.makeGenEvt *
                        process.makeTtSemiLepEvent *
                        process.analyzeHypotheses)
