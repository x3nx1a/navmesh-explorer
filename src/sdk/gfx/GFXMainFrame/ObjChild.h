#pragma once

#include <Windows.h>
#include "sdk/BSLib/Obj.h"

class CObjChild : public CObj { // size 28 + 4 = 32

public:
	virtual int F3(); // Returns weird pointer ...
	virtual int F4(int a1); // Returns -1
	virtual void F5(int a1); // Nothing
	virtual int OnPacket_MAYBE(void* pMsg); // 

	char cobjchild_padding[28];
};
