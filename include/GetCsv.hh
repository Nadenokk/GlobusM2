#ifndef GetCsv_H
#define GetCsv_H 1
#include "globals.hh"
#include <vector>
#include <valarray>
#include <map>
#include "G4Pow.hh"

class GetCsv
{
public:
    virtual ~GetCsv();

    // Initialization of data from a CSV file
    void LoadLEMTable(std::vector<std::vector<G4double>> &, std::vector<G4double> &, std::vector<G4double> &);

    // Alias for matrix type
    using array_type = std::valarray<G4double>;

    // Clear accumulated data
    static void Reset();

    GetCsv();

protected:


private:

    G4int fVerboseLevel { 1 };
    G4String path {"3121_Unix.csv"};
    static GetCsv* instance;
    using vector_type = std::map<G4int, std::vector<G4double>>;

};
#endif
