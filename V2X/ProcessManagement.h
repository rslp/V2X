#pragma once
#include "CommunicationNode.h"
#include "Protocol.h"
#include "Channel.h"
#include "Crowd.h"
#include <list>

/*
 *总流程
*/
class ProcessManagement {
	//开始模拟
public:
	void startSimulation(std::list<CommunicationNode> &comNode, Protocol &protocol, Channel &channel, Crowd &crowd);
};