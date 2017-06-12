#pragma once
#include "Channel.h"
/*
*协议栈工厂父类
*/
class ChannelFactory {
public:
	virtual Channel* CreateChannel() = 0;
};