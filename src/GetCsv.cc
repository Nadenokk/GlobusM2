#include "GetCsv.hh"

#include "G4UnitsTable.hh"
#include "G4tgrUtils.hh"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

GetCsv* GetCsv::instance = nullptr;


GetCsv::GetCsv()
{
     if (instance) delete instance;
}

GetCsv::~GetCsv()
{
    delete[] instance;
}

vector<G4String> split(const G4String& line, const G4String& delimiter)
{
    vector<G4String> result;

    size_t current = 0;
    size_t pos = 0;

    while(pos != G4String::npos)
    {
        pos = line.find(delimiter, current);
        G4String token = line.substr(current, pos - current);

        token = token.strip(G4String::both, '\"');
        result.push_back(token);
        current = pos + delimiter.size();
    }
    return result;
}

void GetCsv::LoadLEMTable(vector<std::vector<G4double>> &position, vector<G4double> &probability, vector<G4double> &probabilitySumm)
{

    cout<<"Begin parset"<<endl;

    ifstream in(path);
    if (!in)
    {
        stringstream ss;
        ss << "Cannot open LEM table input file: " << path;
        G4Exception("GetCsv::LoadData", "WrongTable", FatalException, ss.str().c_str());
    }


    G4String line;
    G4double sumProbability;
    probability.push_back(0.0);
    position.push_back(vector<G4double>{0,0});
    probabilitySumm.push_back(0.0);

    while (getline(in, line))
    {
        vector<G4String> lineParts = split(line, ";");

        std::vector<G4double> linePartsD;
        std::vector<G4double> linePartsP;
        std::vector<G4double> temp;
        for(int j = 0;j < 2;j++) {
            temp.push_back(G4tgrUtils::GetDouble(lineParts[j]));
        }
        position.push_back(temp);
        G4double tmp = G4tgrUtils::GetDouble( lineParts[2]);
        probability.push_back(tmp);
        sumProbability += tmp;
        probabilitySumm.push_back(sumProbability);
    }
}

void GetCsv::Reset()
{
        G4cout << "RBE: Reset(): ";
}
