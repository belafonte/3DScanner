#include "scanParams.h"

class CamCalib
{

public:
	CamCalib(void);
	~CamCalib(void);
	int camCalib(ScanParams *scanParams);
};