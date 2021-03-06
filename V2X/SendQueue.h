#pragma once
#include "SliceMessage.h"
#include <queue>
#include <iostream>
using namespace std;

/*
 *发送队列
*/
class SendQueue
{
public:
	//构造函数
	SendQueue();
	SendQueue(long ID, queue<SliceMessage> & qsm);
	//析构函数
	~SendQueue();

	//获取发送队列指针
	queue<SliceMessage>* getSendQueue();
	//判断发送队列是否为空
	bool isEmpty();
	//往发送队列中添加消息
	void addMessage(SliceMessage &sMsg);
	//获取发送队列对头的消息，并删除对头消息
	SliceMessage* getMessage();
	//获取发送队列的大小
	int getSize();
	//获取发送队列对应的通信节点ID
	long getNodeID();
	//设置发送队列对应的通信节点ID
	void setNodeID(long id);
	//获取该发送队列的退避时间
	int getBackOffCount();
	//设置该发送队列的退避时间
	void setBackOffCount(int count);
	//获取当前是否需要退避
	bool getBackOff();
	//设置当前队列退避状态
	void setBackOff(bool back);

private:
	//发送队列对应的通信节点ID
	long nodeID;
	//当前发送队列的退避时间
	int backOffCount = 0;
	//当前队列是否需要退避
	bool backOff = false;
	//发送队列
	queue<SliceMessage> *sendQueue;
};