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
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"

#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "MyHit.hh"
#include "G4SystemOfUnits.hh"

SteppingAction::SteppingAction()
: G4UserSteppingAction()
,fCollID_eDep(-1), fCollID_eKinE(-1),
eCopyNo(0), eKinE(0), secondaryCount(0), trackID(1), eventID(0)
{

}


SteppingAction::~SteppingAction()
{

	G4cout << "!!@ hi" << G4endl;
	for (auto itr: eKEdepMap) {
		G4cout << itr.first << " " << itr.second / keV << G4endl;
	}


}


void SteppingAction::UserSteppingAction(const G4Step* step)
{



	//
	if (fCollID_eKinE < 0)
		fCollID_eKinE = G4SDManager::GetSDMpointer()->GetCollectionID("mySD/myHitsCollection");

	const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
	G4HCofThisEvent* hce = event->GetHCofThisEvent();
	G4VHitsCollection* hc = hce->GetHC(fCollID_eKinE);

	if ( eventID != event->GetEventID() ) {
		eventID = event->GetEventID();
		secondaryCount = 0;
	}
	if ( trackID != step->GetTrack()->GetTrackID() ) {
		trackID = step->GetTrack()->GetTrackID();
		secondaryCount = 0;
	}

	if (hc->GetSize() <= 0) return;
	const std::vector<const G4Track*> *secondary = step->GetSecondaryInCurrentStep();
	G4int secondaryNo = (*secondary).size();

	if (secondaryNo == 0) return;
	secondaryCount += (*secondary).size();
	auto myHitsCollection = static_cast<MyHitsCollection*>(hc);

	eCopyNo = (*myHitsCollection)[secondaryCount-1]->GetHitCopyNo();
	G4ThreeVector ePos = (*myHitsCollection)[secondaryNo-1]->GetPos();
	eKinE = (*myHitsCollection)[secondaryCount-1]->GetkEdep();
	G4cout <<  " !!! " << secondaryNo << "/" << secondaryCount << " "<< eCopyNo << " " << eKinE << " " << ePos << G4endl;

	eKEdepMap[eCopyNo] += eKinE;
	G4cout << eKEdepMap[eCopyNo] << G4endl;







//	size_t nofHits = myHitsCollection->entries();
//
//	for (size_t i=0; i<nofHits; i++) {
//		G4int copyNo = (*myHitsCollection)[i]->GetHitCopyNo();
//		G4ThreeVector ePos = (*myHitsCollection)[i]->GetPos();
//		eKinE = (*myHitsCollection)[i]->GetkEdep();
//		G4cout <<  " !!! " << secondaryNo2 << "/" << secondaryNo << " "<< copyNo << " " << eKinE << G4endl;
//	}



//	// Check electron
//	const std::vector<const G4Track*>* secondary = step->GetSecondaryInCurrentStep();
//	G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
//	for (size_t i=0; i<(*secondary).size(); i++) {
//		particle = (*secondary)[i]->GetDefinition();
//		G4String name = particle->GetParticleName();
//		eKinE = (*secondary)[i]->GetKineticEnergy();
////		G4cout << " ** check secondary: " << name << " " << eKinE << G4endl;
//	}



//	G4cout << ">> 1) Hits Collection ----" << G4endl;
//	G4cout << hc1->GetColID() << G4endl;
//	G4cout << hc1->GetName() << G4endl;
//	G4cout << hc1->GetSDname() << G4endl;
//	G4cout << "hc size: " << hc1->GetSize() << G4endl;
//
//
//	if (hc1->GetSize() > 0) {
//		auto hit = static_cast<MyHit*>(hc1->GetHit(fCollID_eKinE));
////		if (hc1->GetSize() != 1) return;
////		hit->Print();
//
//		eCopyNo = hit->GetHitCopyNo();
//
//
//		G4cout << "Position: " << hit->GetPos() << G4endl;
//		G4cout << "Position: " << step->GetPostStepPoint()->GetPosition() << G4endl;
//		G4cout << "Copy_num: " << eCopyNo << G4endl;
//		G4cout << "eKINE: " << eKinE << G4endl;
//		eKEdepMap[eCopyNo] += eKinE;
//	}






	// MFD
//	if (fCollID_eDep < 0) {
//		fCollID_eDep = G4SDManager::GetSDMpointer()->GetCollectionID("pBoxSD/eDep");
//	}

//	G4VHitsCollection* hc2 = hce->GetHC(fCollID_eDep);
//	G4cout << ">> 2) Hits Collection ----" << G4endl;
//	G4cout << hc2->GetColID() << G4endl;
//	G4cout << hc2->GetName() << G4endl;
//	G4cout << hc2->GetSDname() << G4endl;
//	G4cout << "hc size: " << hc2->GetSize() << G4endl;

//	if (hc->GetSize() > 0) {
//		auto hit = static_cast<MyHit*>(hc->GetHit(fCollID_eKinE));
//		hit->Print();
//	}

//	G4THitsMap<G4double>* evtMap =
//			static_cast<G4THitsMap<G4double>*>(hc);
//
//
//
//	if ( !( evtMap->GetObject(eCopyNo) ) ) {
//		evtMap->set(eCopyNo, eKinE);
//	}
//	else {
//		evtMap->add(eCopyNo, eKinE);
//	}


}














