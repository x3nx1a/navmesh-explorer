#pragma once

#include "RuntimeClass.h"

class CObj {
public:
	virtual CRuntimeClass *GetRuntimeClass();
	virtual CRuntimeClass *GetParentType();
	virtual ~CObj();
};
