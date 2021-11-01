//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file main.cc
/// \brief G4Template code

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "ParallelWorld.hh"
#include "G4ParallelWorldPhysics.hh"

#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

int main(int argc,char** argv)
{
	G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
		ui = new G4UIExecutive(argc, argv);
	}

	auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::MT);

	// Choose the Random engine
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(1000);

	// Set mandatory initialization classes
	//
	// Detector construction
	DetectorConstruction* det = new DetectorConstruction();
	det->RegisterParallelWorld(new ParallelWorld("parallel"));
	runManager->SetUserInitialization(det);

	// Physics list
	G4VModularPhysicsList* physicsList = new FTFP_BERT;
	physicsList->RegisterPhysics(new G4ParallelWorldPhysics("parallel", true));
	runManager->SetUserInitialization(physicsList);

	// User action initialization
	runManager->SetUserInitialization(new ActionInitialization());

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	//
	if ( ! ui ) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else {
		// interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}

	delete visManager;
	delete runManager;

	return EXIT_SUCCESS;
}

