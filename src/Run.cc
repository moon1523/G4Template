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

#include "Run.hh"

Run::Run()
:G4Run()
{
//	G4cout << "Run() is invoked" << G4endl;

//	fCollID_eDep = G4SDManager::GetSDMpointer()->GetCollectionID("mySD/myHitsCollection");


}

Run::~Run()
{
	edepMap.clear();

}

void Run::RecordEvent(const G4Event* event)
{
//	G4HCofThisEvent* hce = event->GetHCofThisEvent();
//	G4VHitsCollection* hc = hce->GetHC(fCollID_eDep);
//		G4cout << ">> 2) Hits Collection ----" << G4endl;
//		G4cout << hc->GetColID() << G4endl;
//		G4cout << hc->GetName() << G4endl;
//		G4cout << hc->GetSDname() << G4endl;
//		G4cout << "hc size: " << hc->GetSize() << G4endl;
//
//
//	G4THitsMap<G4double>* evtMap =
//			static_cast<G4THitsMap<G4double>*>(hc);
//	auto hitsMap = *evtMap->GetMap();
//
//	G4cout << "hitsMap.size(): " << hitsMap.size() << G4endl;
//
//
//
//	for (auto itr:hitsMap) {
////		edepMap[itr.first].first += *itr.second;
////		edepMap[itr.first].first += (*itr.second) * (*itr.second);
//		G4cout << "@@@" << itr.first << " " << *itr.second << G4endl;
//	}
	G4Run::RecordEvent(event);
}

void Run::Merge(const G4Run* run)
{



	G4Run::Merge(run);
}











