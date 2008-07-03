import FWCore.ParameterSet.Config as cms

process = cms.Process("TtSemiEvtKit")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("TopQuarkAnalysis.Examples.RecoInput_ttSemiMu_cfi")

# Load pat
process.load("PhysicsTools.PatAlgos.patLayer0_cff")
process.load("PhysicsTools.PatAlgos.patLayer1_cff")
process.load("PhysicsTools.PatAlgos.patLayer1_EventContent_cff")

# Load TQAF layer 2
process.load("TopQuarkAnalysis.TopEventProducers.tqafLayer2_ttSemiLeptonic_cff")

# Load TtSemiEvtKit
process.load("TopQuarkAnalysis.Examples.TtSemiEvtKit_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200)
)
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('TtSemiEvtKitHistos.root')
)

process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    )
)
process.patEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring('drop *')
)
process.patEventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    )
)
process.out = cms.OutputModule("PoolOutputModule",
    process.patEventSelection,
    process.patEventContent,
    verbose = cms.untracked.bool(False),
    fileName = cms.untracked.string('TtSemiEvtKitOutput.root')
)

process.p = cms.Path(process.patLayer0*
                     process.patLayer1*
                     process.tqafLayer2_ttSemiLeptonic_semiLepFilter*
                     process.ttSemiEvtKit
                     )
process.outpath = cms.EndPath(process.out)
process.patEventContent.outputCommands.extend(process.patLayer1EventContent.outputCommands)
process.patEventContent.outputCommands.extend(['keep *_TtSemiEvtKit_*_*', 'keep *_solutions_*_*'])
