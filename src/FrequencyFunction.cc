#include "FrequencyFunction.hh"
#include "Randomize.hh"


G4ThreeVector FrequencyFunction::GetPosition(G4double *p) const
{

  G4double z = p[1];
  G4double fi = G4UniformRand() * pi * 2;
  G4double x = p[0] * cos(fi);
  G4double y = p[0] * sin(fi);
  return G4ThreeVector(x + 7990, y +16060 , z+ 4200 );
  //return G4ThreeVector(x, y, z);
}

G4ThreeVector FrequencyFunction::GetMomentumDirection() const
{
   G4double u = 1-2*G4UniformRand();
   G4double v = G4UniformRand();
   G4double theta = 2*pi*v;
   G4double x = sqrt(1 - u*u)*cos(theta);
   G4double y = sqrt(1 - u*u)*sin(theta);
   G4double z = u;

  return G4ThreeVector(x, y, z);

}

