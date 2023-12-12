#include "ntuples_macro.h"

void ntuples_macro(){

  // Open the input file for reading

  //TString path="ttbar_reduced.root";
  TString path="ntup/410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_ntup.root";
  //TString path="ntup/700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto_ntup.root";
  
  TFile* inFile = TFile::Open(path);
  
  if (!inFile || inFile->IsZombie()) {
    cout << "The MC sample seems to be empty"<< endl; 
    return;
  }

  // Access the input tree
  TTree *inTree = (TTree*) inFile->Get("analysis");

  if(!inTree){
    cout << "The MC sample tree seems to be empty"<< endl;
    inFile->Close();
    return;
  }

  set_branch_address(inTree);
   
  int nentries = inTree->GetEntries();
  cout << "ttbar MC sample nentries: " << nentries << endl;

  for(int ii = 0; ii < inTree->GetListOfBranches()->GetEntries(); ii++){
    cout << ii << "\t" << inTree->GetListOfBranches()->At(ii)->GetName() << endl; 
  }
  
  // Open the output file for writing

  TFile* outFile = new TFile("ttbar.root", "RECREATE");

  TTree* outTree = new TTree("analysis", "analysis");

  TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);

  // Open the file with the histogram information
  
  TFile *file_hist = TFile::Open("hist/410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_hist.root");
  TH1F *hist_weights = (TH1F*) file_hist->Get("CutBookkeeper_410470_284500_NOSYS");
  hist_weights->Draw();
  canvas->Draw();

  // Save the weights in three variables that are going to be stored as branches
  
  Float_t initial_events = 0;
  Float_t initial_sum_of_weights = 0;
  Float_t initial_sum_of_weights_squared = 0;

  branch(outTree);
  
  outTree->Branch("initial_events", &initial_events, "initial_events/F");
  outTree->Branch("initial_sum_of_weights", &initial_sum_of_weights, "initial_sum_of_weights/F");
  outTree->Branch("initial_sum_of_weights_squared", &initial_sum_of_weights_squared, "initial_sum_of_weights_squared/F");

  int nbytes = 0;
  
  float fraction = 1.0; // To set the fraction of events considered from the whole set of events of the MC sample
  
  for(int ii=0; ii<nentries*fraction; ii++){
    
    nbytes = inTree->GetEntry(ii);
    
    initial_events = hist_weights->GetBinContent(1);
    initial_sum_of_weights = hist_weights->GetBinContent(2);
    initial_sum_of_weights_squared = hist_weights->GetBinContent(3);

    outTree->Fill();
  }
  
  // Write the output tree to the output file

  outFile->Write();

  // Close the files
  inFile->Close();
  outFile->Close();
  file_hist->Close();
}
