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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"

#include "G4Box.hh"



DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  lv_world(0), pv_world(0), lv_Box(0)
{ }



DetectorConstruction::~DetectorConstruction()
{ }



G4VPhysicalVolume* DetectorConstruction::Construct()
{
	SetupWorldGeometry();

	G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4VSolid* sol_Box = new G4Box("sol_Box", 0.5*m, 0.5*m, 0.5*m);
	lv_Box = new G4LogicalVolume(sol_Box, water, "lv_Box");
	lv_Box->SetVisAttributes(new G4VisAttributes(G4Colour(1.0,1.0,0.0,0.5)));
	G4PVPlacement* pv_Box = new G4PVPlacement(0, G4ThreeVector(0,0,1.0*m), lv_Box, "pv_Box", lv_world, false, 10);

	massMap[pv_Box->GetCopyNo()] = water->GetDensity() * lv_Box->GetSolid()->GetCubicVolume();

	return pv_world;
}

void DetectorConstruction::SetupWorldGeometry()
{
	// Define the world box (size: 10*10*5 m3)
	G4double world_halfX = 5. * m;
	G4double world_halfY = 5. * m;
	G4double world_halfZ = 2.5 * m;

	G4VSolid* sol_world = new G4Box("sol_world", world_halfX, world_halfY, world_halfZ);
	lv_world = new G4LogicalVolume(sol_world, G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"), "lv_world");
	pv_world = new G4PVPlacement(0, G4ThreeVector(), lv_world, "pv_world", 0, false, 0, false);
	G4VisAttributes* va_world = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	va_world->SetForceWireframe(true);
	lv_world->SetVisAttributes(va_world);
}

void DetectorConstruction::ConstructSDandField()
{
	G4MultiFunctionalDetector* MFDet = new G4MultiFunctionalDetector("boxSD");
	G4SDManager* boxSDman = G4SDManager::GetSDMpointer();
	boxSDman->AddNewDetector( MFDet );
	MFDet->RegisterPrimitive(new G4PSEnergyDeposit("eDep"));
	SetSensitiveDetector(lv_Box, MFDet);
}

















