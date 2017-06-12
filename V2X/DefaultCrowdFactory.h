#pragma once
#include "CrowdFactory.h"
#include "DefaultCrowd.h"

/*默认分簇的工厂类，用于生产指向默认分簇类的指针*/
class DefaultCrowdFactory : public CrowdFactory {
public:
	Crowd* CreateCrowd() { return new DefaultCrowd(); }
};