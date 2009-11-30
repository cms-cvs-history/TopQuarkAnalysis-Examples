import FWCore.ParameterSet.Config as cms

#
# make simple analysis plots for a comparison
# between a simple algorithmic, a gen match and
# an MVA discriminator based event hypothesis
#

# initialize analyzers
from TopQuarkAnalysis.Examples.HypothesisAnalyzer_cfi import *
analyzeGenMatch      = analyzeHypothesis.clone()
analyzeMaxSumPtWMass = analyzeHypothesis.clone()
analyzeGeom          = analyzeHypothesis.clone()

# configure analyzers
analyzeGenMatch.hypoClassKey      = "ttSemiLepHypGenMatch:Key"
analyzeMaxSumPtWMass.hypoClassKey = "ttSemiLepHypMaxSumPtWMass:Key"
analyzeGeom.hypoClassKey          = "ttSemiLepHypGeom:Key"

# define sequence
analyzeHypotheses = cms.Sequence(analyzeGenMatch *
                                 analyzeMaxSumPtWMass *
                                 analyzeGeom)
