#! /bin/csh

if ($#argv < 1) then
    echo "(famoscomparison.csh) use: ./famoscomparison.csh [variable] [object = e/mu/jet] [index] [nbins] [min] [max] [filename1.root] [filename2.root]"
    exit
endif

set variable=$1
set object=$2
if ($#argv < 2) then
    echo "(famoscomparison.csh) default object: jet"
    set object = jet
endif
set index=$3
if ($#argv < 3) then
    echo "(famoscomparison.csh) default index: 0"
    set index = 0
endif
@ order = ( $index + 1 )
echo "(famoscomparison.csh) order: ${order}"
set nbins=$4
if ($#argv < 4) then
    echo "(famoscomparison.csh) default bins: 30"
    set nbins = 30
endif
set min=$5
if ($#argv < 5) then
    echo "(famoscomparison.csh) default min: 0"
    set min = 0
endif
set max=$6
if ($#argv < 6) then
    echo "(famoscomparison.csh) default max: 300"
    set max = 300
endif
set sample1=$7
if ($#argv < 7) then
    echo "(famoscomparison.csh) default sample 1: TtSemiMuEvents_fullsim.root"
    set sample1 = TtSemiMuEvents_fullsim.root
endif
set sample2=$8
if ($#argv < 8) then
    echo "(famoscomparison.csh) default sample 2: TtSemiMuEvents_fastsim.root"
    set sample2 = TtSemiMuEvents_fastsim.root
endif

if ( ${object} == jet ) then
    set branch = TopJets_selectedTopJets__TtEventReco.obj
else if ( ${object} == e ) then
    set branch = recoPixelMatchGsfElectronTopLeptons_selectedTopElectrons__TtEventReco.obj
else if ( ${object} == mu ) then
    set branch = recoMuonTopLeptons_selectedTopMuons__TtEventReco.obj
else
    echo "(famoscomparison.csh) unavailable object type ${object}: exiting"
    exit
endif

set method = "${variable}()"
if ( ${variable} == btag ) then
#    set method = getBDiscriminator\(\"trackCountingJetTags\"\)
    set method = getBDiscriminator\(\"default\"\)
#    set method = "dumpBTagLabels()"
    echo $method
endif


set macro = FamosComparison.C

if (-f "${macro}") rm ${macro}
cat > ${macro} <<EOF
void FamosComparison(TString sample1="${sample1}", TString sample2="${sample2}") {

  if (gSystem->Load("libFWCoreFWLite") == 0) { // if not loaded yet, load it
    AutoLibraryLoader::enable();
  }
  
  gStyle->SetOptStat(0000);
  gStyle->SetCanvasBorderMode(-1);
  gStyle->SetCanvasBorderSize(1);
  gStyle->SetCanvasColor(10);
  
  TH1F *h1 = fillHisto(sample1);
  TH1F *h2 = fillHisto(sample2);

  h1->SetLineColor(2);
  h2->SetLineColor(4);

  h1->SetLineWidth(3);
  h2->SetLineWidth(3);
  
  TCanvas* myCanvas = new TCanvas("myCanvas","Jets",100,10,800,800);
  myCanvas->SetFillColor(10);
  myCanvas->cd();

  h1->DrawCopy("e");
  h1->DrawCopy("same");
  h2->DrawCopy("same");

  TLegend *legend = new TLegend(0.80,0.85,0.95,0.95,"","NDC");
  legend->AddEntry(h1,"full","l");
  legend->AddEntry(h2,"fast","l");
  legend->Draw();
  myCanvas->Update();
 
  // output:
  TString gif("comparison_${variable}_${object}${order}.gif");
  myCanvas->Print(gif);

  delete h1;
  delete h2;
}


TH1F* fillHisto(TString path)
{
  gSystem->Load ("libRFIO.so");

  cout << "Opening " << path << endl;
  TFile* f = TFile::Open(path);
  if ( (!f->IsOpen()) || (f->IsZombie()) ) {
    cout << "File " << path << " not open, exiting." << endl;
    return 0;
  }

  TTree * events = (TTree *) f->Get( "Events" );
  if (events == 0) {
    cout << "File " << path << " has 0 events, exiting." << endl;
    return 0;
  }

  TBranch * branch = events->GetBranch( "${branch}" );

  vector<TopJet> jet;
  vector<TopElectron> e;
  vector<TopMuon> mu;

  // Loop over events and fill histogram
  TH1F* h = new TH1F("h","${variable} of ${object} ${order}",${nbins},${min},${max});
  int nev = events->GetEntries();
  for( int ev = 0; ev < nev; ++ev ) { 
    branch -> SetAddress( & ${object} );
    branch -> GetEntry( ev );

    if (${object}.size()>${index}) {
	double var=${object}[${index}].${method};
	h->Fill(var);
    }
  }

  return h;
}
EOF

setenv SCRAM_ARCH slc4_ia32_gcc345
eval `scramv1 runtime -csh`

root -l <<- EOF 
    .x ${macro}
    .q
EOF
