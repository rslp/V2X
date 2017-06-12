#pragma once
#include "Crowd.h"

/*
*分簇工厂父类
*/
class CrowdFactory {
public:
	virtual Crowd* CreateCrowd() = 0;
};