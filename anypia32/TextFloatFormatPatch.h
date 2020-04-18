// $Id: TextFloatFormatPatch.h 1.1 2017/12/12 08:20:06EST 277133 Development  $
//
// Header for reimplementation of AfxTextFloatFormat because of buggy _sntscanf_s function


void AFXAPI AfxTextFloatFormat2(CDataExchange* pDX, int nIDC,
  void* pData, double value, int nSizeGcvt);
void AFXAPI DDX_Text2(CDataExchange* pDX, int nIDC, float& value);
void AFXAPI DDX_Text2(CDataExchange* pDX, int nIDC, double& value);
