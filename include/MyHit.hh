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
/// \file MyHit.hh
/// \brief Definition of the MyHit class

#ifndef MyHit_h
#define MyHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Tracker hit class
///
/// It defines data members to store the trackID, chamberNb, energy deposit,
/// and position of charged particles in a selected volume:
/// - fTrackID, fChamberNB, fEdep, fPos

class MyHit : public G4VHit
{
  public:
    MyHit();
    MyHit(const MyHit&);
    virtual ~MyHit();

    // operators
    const MyHit& operator=(const MyHit&);
    G4bool operator==(const MyHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
	void SetTrackID  (G4int track)      { fTrackID = track; };
	void SetHitParName(G4String name)   { fHitParName = name; };
	void SetHitCopyNo(G4int chamb)      { fHitCopyNo = chamb; };
	void SetkEdep     (G4double kE)      { fkEdep = kE; };
	void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

	// Get methods
	G4int GetTrackID()   const     { return fTrackID; };
	G4String GetHitParName() const { return fHitParName; };
	G4int GetHitCopyNo() const   { return fHitCopyNo; };
	G4double GetkEdep()  const     { return fkEdep; };
	G4ThreeVector GetPos() const { return fPos; };


  private:
	G4int         fTrackID;
	G4String      fHitParName;
    G4int         fHitCopyNo;
    G4double      fkEdep;
    G4ThreeVector fPos;

};

typedef G4THitsCollection<MyHit> MyHitsCollection;

extern G4ThreadLocal G4Allocator<MyHit>* MyHitAllocator;

inline void* MyHit::operator new(size_t)
{
	if(!MyHitAllocator)
		MyHitAllocator = new G4Allocator<MyHit>;
	return (void *) MyHitAllocator->MallocSingle();
}

inline void MyHit::operator delete(void *hit)
{
	MyHitAllocator->FreeSingle((MyHit*) hit);
}





#endif
