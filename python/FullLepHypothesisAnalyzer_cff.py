import FWCore.ParameterSet.Config as cms

#
# make simple analysis plots for a comparison
# between a kinematic reconstruction and a
# gen match event hypothesis
#

# initialize analyzers
from TopQuarkAnalysis.Examples.FullLepHypothesisAnalyzer_cfi import *
analyzeGenMatch    = analyzeFullLepHypothesis.clone()
analyzeKinSolution = analyzeFullLepHypothesis.clone()


# configure analyzers
analyzeGenMatch.hypoClassKey    = "ttFullLepHypGenMatch:Key"
analyzeKinSolution.hypoClassKey = "ttFullLepHypKinSolution:Key"

# define sequence
analyzeHypotheses = cms.Sequence(analyzeGenMatch *
                                 analyzeKinSolution)
