#pragma once
#include "SliceMessage.h"
#include "CommunicationNode.h"
#include <list>

class Channel {
public:
	Channel() {};
	virtual void bitSimulation(SliceMessage &sMsg) = 0;
	virtual void delaySimulation(SliceMessage &sMsg, int index, std::list<CommunicationNode> communicationNodes, int simulation_count) = 0;

};