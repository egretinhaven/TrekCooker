# TrekCooker

##Developer's Note
### How to make a plugin

- Adding a tree structure. Take csitree as an example.
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
- add a plugin
  - create a directory *src/plugins/detector/CsI*
  - modify *src/plugins/CMakeLists.txt*
  - create CMakeList.txt in *src/plugins/detector/CsI* 
  - create a directory *src/plugins/detector/CsI/src*
  - create a directory *src/plugins/detector/CsI/src/include*
  - create a file *src/plugins/detector/CsI/src/include/Det_Csi.h*
  - create LinkDef file for root *src/plugins/detector/CsI/src/include/LinkDef.hh*
  - create a file *src/plugins/detector/CsI/src/Det_Csi.cpp* and implement at least 6 functions: constructor, destructor, Long_t histos();  Long_t startup();  Long_t process();  Long_t done();
  - createa init xml files *src/plugins/detector/CsI/init/demo.xml* and *src/plugins/detector/CsI/init/demo.xsd*
  - create recipe file *recipe/CsI/test.xml*
