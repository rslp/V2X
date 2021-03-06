#include <iostream>
#include <list>
#include "DefaultProtocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <string>
#include "constUtil.h"


using namespace std;

DefaultProtocol::DefaultProtocol()
{
}


//切割消息
list<SliceMessage>* DefaultProtocol::cutMessage(list<Message> &lm)//切割消息
{//假定MTU：400B 头大小40B
	list<SliceMessage>* lsm = new list<SliceMessage>;
	list<Message>::iterator iter;//迭代器
	for (iter = lm.begin(); iter != lm.end(); iter++) {//遍历通信节点要发的所有消息
		int size = (*iter).getSize();//获取当前消息大小
		if (size <= MTU - HEADLENGTH) {//小于MTU-头
			SliceMessage sm = SliceMessage((*iter).getMessageID(), (*iter).getSourceAddress(), (*iter).getDestinationAddress(), size + HEADLENGTH, false, 1);
			sm.setTotalSize(size);//设置分片消息所属消息总大小
			(*lsm).push_back(sm);
		}
		else {//大于MTU 进行分片
			int num = size / (MTU - HEADLENGTH);//分片个数为num+1
			int remainder = size % (MTU - HEADLENGTH);//剩余的分片大小
			for (int i = 0; i < num; i++) {//从第一片到第num片都是以MTU大小发送
				SliceMessage sm;
				if ((i == num - 1) && (remainder == 0)) {
					sm = SliceMessage((*iter).getMessageID(), (*iter).getSourceAddress(), (*iter).getDestinationAddress(), MTU, false, i);
				}
				else {
					sm = SliceMessage((*iter).getMessageID(), (*iter).getSourceAddress(), (*iter).getDestinationAddress(), MTU, true, i);
				}
				sm.setTotalSize(size);//设置分片消息所属消息总大小
				(*lsm).push_back(sm);
			}
			if (remainder != 0) {
				//第num+1片以剩余+头大小发送
				SliceMessage sm1 = SliceMessage((*iter).getMessageID(), (*iter).getSourceAddress(), (*iter).getDestinationAddress(), remainder + HEADLENGTH, false, num);
				sm1.setTotalSize(size);//设置分片消息所属消息总大小
				(*lsm).push_back(sm1);
			}
		}
	}
	return lsm;
}

//整合消息
list<Message> * DefaultProtocol::mergeMessage(list<SliceMessage> &lsm)//整合消息
{
	list<Message> * lm = new list<Message>;//返回的消息
	map<string, Message*> tmp;//内部存储发送节点id和对应消息节点指针

	list<SliceMessage>::iterator iter;//开始节点迭代器

	for (iter = lsm.begin(); iter != lsm.end(); ++iter) {
		long messageID = (*iter).getMessageID();//获取初始变量
		long sendID = (*iter).getSourceAddress();
		long receiveID = (*iter).getDestinationAddress();
		int size = (*iter).getSize();
		int TotalSize = (*iter).getTotalSize();
		float delay = (*iter).getDelay();//获取当前分片消息的延迟大小

		string twoID = to_string(sendID) + " " + to_string(messageID);
		map<string, Message*>::iterator it;
		it = tmp.find(twoID);
		if (it == tmp.end()) {//若内部存储没有当前结点 则新建并存储消息指针
			Message * sm = new Message(messageID, sendID, receiveID, size - HEADLENGTH);
			(*sm).setDelay(delay);//新建节点的延迟
			tmp[twoID] = sm;
		}
		else {//若内部存储有当前结点 则修改消息大小
			int current_size = (*((*it).second)).getSize();
			current_size = current_size + size - HEADLENGTH;
			(*((*it).second)).setSize(current_size);

			if ((*((*it).second)).getDelay() < delay) {//若当前消息的延迟小于新分片消息延迟
				(*((*it).second)).setDelay(delay);//设置位新的消息延迟
			}
		}
		if (tmp[twoID]->getSize() == TotalSize) {//若整合后的消息大小符合最初消息大小 则置传输完成标志位为true
			tmp[twoID]->setTransFinish(true);
		}
	}
	map<string, Message*>::iterator iter1;
	for (iter1 = tmp.begin(); iter1 != tmp.end(); ++iter1) {//遍历内部存储
		(*lm).push_back(*(*iter1).second);//放入消息队列
	}
	return lm;
}
//单独一个队列的退避算法
void DefaultProtocol::backOffAQueue(CommunicationNode &communicationNode)
{
	if ((*(communicationNode.getSendQueue())).getBackOff() == true)
	{
		srand((int)time(NULL));
		int back = (int)rand() % BACK_OFF;
		(*communicationNode.getSendQueue()).setBackOffCount(back);
		(*communicationNode.getSendQueue()).setBackOff(false);
	}
}

//对所有发送队列关于退避时间的预处理
void DefaultProtocol::preBackOff(list<CommunicationNode> communicationNodes)
{
	list<CommunicationNode>::iterator iter;
	SendQueue *tempQueue;
	for (iter = communicationNodes.begin(); iter != communicationNodes.end(); ++iter)
	{
		tempQueue = (*iter).getSendQueue();
		//每个时隙开始时，将退避时间减一
		if ((*tempQueue).getBackOffCount() != 0)
		{
			(*tempQueue).setBackOffCount((*tempQueue).getBackOffCount() - 1);
		}
	}
}
