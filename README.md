# TrekCooker

##Developer's Note
### How to make a plugin
Take csitree as an example.
- Adding a tree structure
  - add a header file *csitree.h* in *include* inheriting CRTBase. Array can be represented by std::vector
  ```
class CRTRawCsI:public CRTBase
{
 public:
  UInt_t runNo;
  ...
  std::vector<UInt_t> nameModule;
  ...
  CRTRawCsI();
  virtual ~CRTRawCsI();
  ClassDef(CRTRawCsI,1);
};
  ```
  - add a cpp file in *src/tree/src*. It is typically as simple as
  ```
#include "csitree.h"

CRTRawCsI::CRTRawCsI()
{};

CRTRawCsI::~CRTRawCsI()
{};

ClassImp(CRTRawCsI);
  ```
  - modify *src/tree/src/include/LinkDef.hh* file to add #pragma link C++ class CRTRawCsI+;
  - modify *src/tree/CMakeLists.txt* 
  ```
FILE(GLOB HEADERS src/include/*.h
${CMAKE_SOURCE_DIR}/include/cookerrawtree.h
${CMAKE_SOURCE_DIR}/include/mctree.h
${CMAKE_SOURCE_DIR}/include/generatortree.h
${CMAKE_SOURCE_DIR}/include/csitree.h
)
  ```