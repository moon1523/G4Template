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
:G4Run(), fCollID_eDep(-1)
{
	fCollID_eDep = G4SDManager::GetSDMpointer()->GetCollectionID("boxSD/eDep");
}

Run::~Run()
{
	edepMap.clear();
}

void Run::RecordEvent(const G4Event* event)
{
	// Hits Collection
	//
	G4HCofThisEvent* hce = event->GetHCofThisEvent();
	G4VHitsCollection* hc = hce->GetHC(fCollID_eDep);

	// Energy
	G4THitsMap<G4double>* hitsMap_energy = static_cast<G4THitsMap<G4double>*>(hc);
	auto hitsMap = *hitsMap_energy->GetMap();


	for (auto itr:hitsMap)
	{
		G4cout << event->GetEventID() <<  "HITS!: " << itr.first << " " << *itr.second << G4endl;

		edepMap[itr.first].first  += (*itr.second);
		edepMap[itr.first].second += (*itr.second) * (*itr.second);
	}


	G4Run::RecordEvent(event);
}

void Run::Merge(const G4Run* run)
{
	const Run* localRun = static_cast<const Run*>(run);
	// merge the data fram each thread
	EDEPMAP localMap = localRun->edepMap;

	for(auto itr:localMap)
	{
		G4cout << "local HITS!: " << itr.first << " " << itr.second.first << G4endl;
		edepMap[itr.first].first  += itr.second.first;
		edepMap[itr.first].second += itr.second.second;
	}

	G4Run::Merge(run);
}











