#pragma once
#include <list>
#include "SliceMessage.h"
#include "Message.h"
#include "CommunicationNode.h"
#include "SendQueue.h"

/*
 协议栈父类
*/
class Protocol {
public:
	Protocol() {};
//	virtual ~Protocol() = 0;

	//消息分片
	virtual std::list<SliceMessage> * cutMessage(std::list<Message> &lm) = 0;
	//消息组装
	virtual std::list<Message> * mergeMessage(std::list<SliceMessage> &lsm) = 0;
	//单独一个队列的退避算法
	virtual void backOffAQueue(CommunicationNode &communicationNode) = 0;
	//对退避算法的相应处理
	virtual void preBackOff(std::list<CommunicationNode> communicationNodes) = 0;
};