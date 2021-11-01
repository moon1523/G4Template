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
/// \file MySD.cc
/// \brief Implementation of the MySD class

#include "MySD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"



MySD::MySD(const G4String& name, const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name), fHitsCollection(NULL)
{
	collectionName.insert(hitsCollectionName);
}



MySD::~MySD()
{}



void MySD::Initialize(G4HCofThisEvent* hce)
{
	// Create hits collection
	fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);

	// Add this collection in hce
	G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	hce->AddHitsCollection( hcID, fHitsCollection );

}



G4bool MySD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	const std::vector<const G4Track*> *secondary = aStep->GetSecondaryInCurrentStep();
	G4int count = (*secondary).size();
	G4String name = (*secondary)[count-1]->GetDefinition()->GetParticleName();
	G4ThreeVector position = (*secondary)[count-1]->GetPosition();
	G4double eKinE = (*secondary)[count-1]->GetKineticEnergy();
	G4int copyNo = aStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4int trackID = (*secondary)[count-1]->GetTrackID();

	if (position != aStep->GetPostStepPoint()->GetPosition()) {
		return false;
	}



//	G4cout << count << G4endl;
//	G4String name; G4ThreeVector position; G4double eKinE; G4int copyNo, trackID;
//    for (size_t i=0;i<count;i++) {
//		name = (*secondary)[i]->GetDefinition()->GetParticleName();
//		position = (*secondary)[i]->GetPosition();
//		eKinE = (*secondary)[i]->GetKineticEnergy();
//		copyNo = aStep->GetPostStepPoint()->GetTouchable()->GetCopyNumber(0);
//		trackID = (*secondary)[i]->GetTrackID();
//			G4cout << " ** check secondary: " << name  << " " << position << " " << eKinE << G4endl;
//			G4cout << " " << i << "  post step: " << copyNo << " " << aStep->GetPostStepPoint()->GetPosition() << G4endl;
//	}


//	G4cout << " ** check secondary: " << name  << " " << position << " " << eKinE << G4endl;
//	G4cout << " " << count << "  post step: " << copyNo << " " << aStep->GetPostStepPoint()->GetPosition() << G4endl;


	MyHit* newHit = new MyHit();
	newHit->SetTrackID(trackID);
	newHit->SetHitParName(name);
	newHit->SetHitCopyNo(copyNo);
	newHit->SetPos(position);
	newHit->SetkEdep(eKinE);


//	newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
//	newHit->SetHitParName(aStep->GetTrack()->GetDefinition()->GetParticleName());
//	newHit->SetHitCopyNo(aStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber());
//	newHit->SetEdep(aStep->GetTotalEnergyDeposit());
//	newHit->SetkEdep(aStep->GetPostStepPoint()->GetKineticEnergy());
//	newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());




//	G4int nofHits = fHitsCollection->entries();
//	G4cout << G4endl
//		   << "-------->Hits Collection: in this event they are " << nofHits
//		   << " hits in the tracker chambers: " << G4endl;
//	for ( G4int i=0; i < nofHits; i++ )
//		(*fHitsCollection)[i]->Print();


	fHitsCollection->insert ( newHit );
	return true;
}



void MySD::EndOfEvent(G4HCofThisEvent*)
{
//	if ( verboseLevel > 1 ) {
		G4int nofHits = fHitsCollection->entries();
		G4cout << G4endl
			   << "-------->Hits Collection: in this event they are " << nofHits
			   << " hits in the tracker chambers: " << G4endl;
		for ( G4int i=0; i < nofHits; i++ )
			(*fHitsCollection)[i]->Print();
//	}

}


