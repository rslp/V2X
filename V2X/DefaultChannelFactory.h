#pragma once
#include "ChannelFactory.h"
#include "DefaultChannel.h"
/*
*生产默认协议栈的工厂
*/
class DefaultChannelFactory : public ChannelFactory {
public:
	Channel* CreateChannel() { return new DefaultChannel(); }
};