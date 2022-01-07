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
#include "ParallelWorld.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"

ParallelWorld::ParallelWorld(G4String parallelWorldName)
:G4VUserParallelWorld(parallelWorldName),
 fConstructed(false), lv_pBox(0)
{
}

ParallelWorld::~ParallelWorld()
{

}

void ParallelWorld::Construct()
{
	if (fConstructed) return;
	fConstructed = true;

	G4VPhysicalVolume* ghost_world = GetWorld();
	G4LogicalVolume* lv_pWorld = ghost_world->GetLogicalVolume();

	G4VSolid* sol_pBox = new G4Box("sol_pBox", 0.5*m, 0.5*m, 0.5*m);
	lv_pBox = new G4LogicalVolume(sol_pBox, G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"), "lv_pBox");
	new G4PVPlacement(0, G4ThreeVector(0,0,1.0*m), lv_pBox, "pv_pBox", lv_pWorld, false, 10);
	G4VisAttributes* va_pBox = new G4VisAttributes(G4Colour(1.0,1.0,0.0,1.0));
	va_pBox->SetForceWireframe(true);
	lv_pBox->SetVisAttributes(va_pBox);
}

void ParallelWorld::ConstructSD()
{
//	G4MultiFunctionalDetector* MFDet = new G4MultiFunctionalDetector("pBoxSD");
//	pSDman->AddNewDetector( MFDet );
//	MFDet->RegisterPrimitive(new MyPSEnergyDeposit("eDep"));
//	SetSensitiveDetector(lv_pBox2, MFDet);
}












