/** 
 * This file has the definition of the ToF tree branch objects 
 */

#ifndef __CSITREE_H_
#define __CSITREE_H_
#include "cookerrawtree.h" // for CRTBase
#include <vector>
class CRTRawCsI:public CRTBase
{
 public:
  UInt_t runNo;
  UInt_t eventNo;
  Int_t isBad;
  UInt_t nChannel;
  std::vector<UInt_t> nameModule;
  std::vector<UInt_t> indexChannel;
  std::vector<UInt_t> nameCsI;
  std::vector<UInt_t> indexCsI;
  std::vector<ULong64_t> timeStamp;
  std::vector<UInt_t> timeCFD;
  std::vector<ULong64_t> charge;
  std::vector<UInt_t> nSample;
  std::vector<std::vector<UShort_t> > data;  
  CRTRawCsI();
  virtual ~CRTRawCsI();
  ClassDef(CRTRawCsI,1);
};
class CRTFitCsI:public CRTBase
{
 public:
  UInt_t runNo;
  UInt_t eventNo;
  UInt_t nChannel;
  std::vector<UInt_t> indexCsI;
  std::vector<UInt_t> nWave;
  std::vector< std::vector<double> > timeFit;
  std::vector< std::vector<double> > chargeFit;
  CRTFitCsI();
  virtual ~CRTFitCsI();
  ClassDef(CRTFitCsI,1);
};

#endif
