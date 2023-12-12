// Declaration of variables to save the information from the branches

Float_t ScaleFactor_PILEUP;
Float_t ScaleFactor_ELE;
Float_t ScaleFactor_MUON;
Float_t mcWeight;
Bool_t trigE;
Bool_t trigM;
Int_t jet_n;
vector<float> *jet_pt;
vector<float> *jet_eta;
vector<float> *jet_phi;
vector<float> *jet_e;
Int_t lep_n;
vector<unsigned int> *lep_type;
vector<float> *lep_pt;
vector<float> *lep_eta;
vector<float> *lep_phi;
vector<float> *lep_e;
vector<float> *lep_ptcone30;
vector<float> *lep_etcone20;
vector<float> *lep_z0;
vector<float> *lep_d0;
vector<float> *lep_d0sig;
vector<bool> *lep_isTightID;
Float_t met;
Float_t met_phi;
Float_t met_mpx;
Float_t met_mpy;


// Some info variables

Float_t initial_events_ttbar;
Float_t initial_sum_of_weights_ttbar;
Float_t initial_sum_of_weights_squared_ttbar;

// Declaration of functions

void set_branch_address(TTree* tree);
void copyTree(TString name_sample);


void set_branch_address(TTree* tree){

  tree->SetBranchAddress("ScaleFactor_PILEUP", &ScaleFactor_PILEUP); 
  tree->SetBranchAddress("ScaleFactor_ELE", &ScaleFactor_ELE);
  tree->SetBranchAddress("ScaleFactor_MUON", &ScaleFactor_MUON);
  tree->SetBranchAddress("mcWeight", &mcWeight);
  tree->SetBranchAddress("trigE", &trigE);
  tree->SetBranchAddress("trigM", &trigM);
  tree->SetBranchAddress("jet_n", &jet_n);
  tree->SetBranchAddress("jet_pt", &jet_pt);
  tree->SetBranchAddress("jet_eta", &jet_eta);
  tree->SetBranchAddress("jet_phi", &jet_phi);
  tree->SetBranchAddress("jet_e", &jet_e);
  tree->SetBranchAddress("lep_n", &lep_n);
  tree->SetBranchAddress("lep_type", &lep_type);
  tree->SetBranchAddress("lep_pt", &lep_pt);
  tree->SetBranchAddress("lep_eta", &lep_eta);
  tree->SetBranchAddress("lep_phi", &lep_phi);
  tree->SetBranchAddress("lep_e", & lep_e);
  tree->SetBranchAddress("lep_ptcone30", &lep_ptcone30);
  tree->SetBranchAddress("lep_etcone20", &lep_etcone20);
  tree->SetBranchAddress("lep_z0", &lep_z0);
  tree->SetBranchAddress("lep_d0", &lep_d0);
  tree->SetBranchAddress("lep_d0sig", &lep_d0sig);
  tree->SetBranchAddress("lep_isTightID", &lep_isTightID);
  tree->SetBranchAddress("met", &met);
  tree->SetBranchAddress("met_phi", &met_phi);
  tree->SetBranchAddress("met_mpx", &met_mpx);
  tree->SetBranchAddress("met_mpy", &met_mpy);

}


void branch(TTree* tree){

  tree->Branch("ScaleFactor_PILEUP", &ScaleFactor_PILEUP); 
  tree->Branch("ScaleFactor_ELE", &ScaleFactor_ELE);
  tree->Branch("ScaleFactor_MUON", &ScaleFactor_MUON);
  tree->Branch("mcWeight", &mcWeight);
  tree->Branch("trigE", &trigE);
  tree->Branch("trigM", &trigM);
  tree->Branch("jet_n", &jet_n);
  tree->Branch("jet_pt", &jet_pt);
  tree->Branch("jet_eta", &jet_eta);
  tree->Branch("jet_phi", &jet_phi);
  tree->Branch("jet_e", &jet_e);
  tree->Branch("lep_n", &lep_n);
  tree->Branch("lep_type", &lep_type);
  tree->Branch("lep_pt", &lep_pt);
  tree->Branch("lep_eta", &lep_eta);
  tree->Branch("lep_phi", &lep_phi);
  tree->Branch("lep_e", & lep_e);
  tree->Branch("lep_ptcone30", &lep_ptcone30);
  tree->Branch("lep_etcone20", &lep_etcone20);
  tree->Branch("lep_z0", &lep_z0);
  tree->Branch("lep_d0", &lep_d0);
  tree->Branch("lep_d0sig", &lep_d0sig);
  tree->Branch("lep_isTightID", &lep_isTightID);
  tree->Branch("met", &met);
  tree->Branch("met_phi", &met_phi);
  tree->Branch("met_mpx", &met_mpx);
  tree->Branch("met_mpy", &met_mpy);
}


void copyTree(TString name_sample){

  // Open the input file for reading
  TString path="ntup/";
    
  if(name_sample == "ttbar"){
      path+="410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_ntup.root";
  }
  if(name_sample == "Zee"){
    path+="700322.Sh_2211_Zee_maxHTpTV2_CVetoBVeto_ntup.root";
  }

  TFile* inFile = TFile::Open(path);
  
  if (!inFile || inFile->IsZombie()) {
    cout << "The MC sample seems to be empty"<< endl; 
    return;
  }

  // Access the input tree
  TTree *inTree = (TTree*) inFile->Get("analysis");

  if (!inTree) {
    cout << "The MC sample tree seems to be empty"<< endl;
    inFile->Close();
    return;
  }

  TString name_output_file = name_sample + "_reduced.root";
  
  // Open the output file for writing

  TFile* outFile = new TFile(name_output_file, "RECREATE");

  // Create a clone of the input tree in the output file

  // TTree* outTree = new TTree("analysis", "analysis");
  // TTree* outTree = (TTree*) inTree->CloneTree();
  TTree* outTree = new TTree("analysis", "analysis");
  
  // set_branch_address(outTree);
  set_branch_address(inTree);
  
  // Optionally, you can modify the data in outTree if needed

  int nentries = inTree->GetEntries();  
  int nbytes = 0;
  float fraction = 0.000001;

  branch(outTree);
  
  for(int ii=0; ii<nentries*fraction; ii++){
    //nbytes = outTree->GetEntry(ii);
    nbytes = inTree->GetEntry(ii);
    outTree->Fill();
  }
  // Write the output tree to the output file

  outFile->Write();

  // Close the files
  inFile->Close();
  outFile->Close();
}
