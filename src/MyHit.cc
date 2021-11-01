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
/// \file MyHit.cc
/// \brief Implementation of the MyHit class

#include "MyHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<MyHit>* MyHitAllocator = 0;

MyHit::MyHit()
 : G4VHit(),
   fTrackID(-1),
   fHitCopyNo(-1),
   fkEdep(0.),
   fPos(G4ThreeVector())
{}

MyHit::MyHit(const MyHit& right)
  : G4VHit()
{
	fTrackID    = right.fTrackID;
	fHitParName = right.fHitParName;
	fHitCopyNo  = right.fHitCopyNo;
	fkEdep      = right.fkEdep;
	fPos        = right.fPos;
}

MyHit::~MyHit() {}

const MyHit& MyHit::operator=(const MyHit& right)
{
	fTrackID    = right.fTrackID;
	fHitParName = right.fHitParName;
	fHitCopyNo  = right.fHitCopyNo;
	fkEdep      = right.fkEdep;
	fPos        = right.fPos;

	return *this;
}



G4bool MyHit::operator==(const MyHit& right) const
{
	return ( this == &right ) ? true : false;
}



void MyHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	G4cout << pVVisManager << G4endl;
	if (pVVisManager) {
		G4Circle circle(fPos);
		circle.SetScreenSize(4.);
		circle.SetFillStyle(G4Circle::filled);
		circle.SetVisAttributes(G4Colour(1.,0.,0.));
		pVVisManager->Draw(circle);
	}

}

void MyHit::Print()
{
	G4cout << "Particle: " << fHitParName
		   << ", Copy #: " << fHitCopyNo
		   << ", pos:" << G4BestUnit(fPos,"Length")
		   << ", kEdep: " << G4BestUnit(fkEdep,"Energy") << G4endl;
}












