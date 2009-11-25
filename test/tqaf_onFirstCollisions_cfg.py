import FWCore.ParameterSet.Config as cms

process = cms.Process("TQAF")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TtSemiLeptonicEvent')
process.MessageLogger.cerr.TtSemiLeptonicEvent = cms.untracked.PSet(
    limit = cms.untracked.int32(100)
)

## define input (139238 events in Run 122314)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F62B040F-6CD8-DE11-9007-001D09F24664.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/F4387297-74D8-DE11-996C-001D09F24F1F.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/EE7B1AC4-6CD8-DE11-97BB-0030487A1FEC.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/9264A28F-87D8-DE11-83A1-001D09F24763.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/7C7495C2-71D8-DE11-ACF2-001D09F248F8.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/4CAB3B6C-6BD8-DE11-845C-000423D9890C.root',
    '/store/data/BeamCommissioning09/MinimumBias/RECO/v2/000/122/314/02E8544C-70D8-DE11-85CF-001617C3B66C.root'
    )
)
process.source.firstRun = cms.untracked.uint32(122314)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP31X_V1::All')

#-------------------------------------------------
# PAT and TQAF configuration
#-------------------------------------------------

## std sequence for PAT
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## remove MC specific stuff in PAT
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, "All")

## sequences in the TQAF
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff")
#process.ttSemiLepEvent.verbosity = 1

## remove MC specific stuff in TQAF
from TopQuarkAnalysis.TopEventProducers.sequences.ttSemiLepEvtBuilder_cff import *
addTtSemiLepHypotheses(process, ["kGeom"])
removeTtSemiLepHypGenMatch(process)

## some EDAnalyzers, just as examples
process.load("TopQuarkAnalysis.Examples.TopJetAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.TopMuonAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi")
process.analyzeHypothesis.hypoClassKey = "ttSemiLepHypGeom:Key"

# register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('tqaf_onFirstCollisions.root')
)

## process path
process.p = cms.Path(process.patDefaultSequence *
                     process.makeTtSemiLepEvent *
                     process.analyzeJet *
                     process.analyzeMuon *
                     process.analyzeHypothesis
                     )
