#pragma once
#ifndef RECEIVEQUENE_H
#define RECEIVEQUENE_H

#include <queue>
#include <list>
#include "SliceMessage.h"

/*
 *接收队列
*/
class ReceiveQueue {
private:
	long nodeID;
	std::queue<SliceMessage> *receiveQueue;

public:
	//构造函数
	ReceiveQueue();
	ReceiveQueue(long id, std::queue<SliceMessage> &qsm);
	//析构函数
	~ReceiveQueue();

	//获取接收队列的id
	long getNodeID();
	//设置接收队列id
	void setNodeID(long id);
	//获取该接收队列所有分片消息
	std::queue<SliceMessage>* getSliceMessage();
	//判断该接收队列是否为空
	bool isEmpty();
	//获取接收队列队首消息并删除
	SliceMessage* getMessage();
	//接收队列中增加一条消息
	void addMessage(SliceMessage &sMsg);
	//获取接收队列大小
	int getSize();
	//获取接收队列指针
	std::queue<SliceMessage> * getReceiveQueue();
};

#endif