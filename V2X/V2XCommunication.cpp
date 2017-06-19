#include "V2XCommunication.h"
#include "ProtocolFactory.h"
#include "Protocol.h"
#include "DefaultProtocolFactory.h"
#include "Util.h"
#include "ProcessManagement.h"
#include "CommunicationNode.h"
#include "ChannelFactory.h"
#include "DefaultChannelFactory.h"
#include "Crowd.h"
#include "DefaultCrowd.h"
#include "CrowdFactory.h"
#include "DefaultCrowdFactory.h"
#include <sstream>

std::string V2XCommunication()
{
	//初始化协议栈
	ProtocolFactory *f = new DefaultProtocolFactory();
	Protocol *protocol = (*f).CreateProtocol();

	//初始化物理信道
	ChannelFactory *c = new DefaultChannelFactory();
	Channel *channel = (*c).CreateChannel();

	//初始化分簇过程
	CrowdFactory *cf = new DefaultCrowdFactory();
	Crowd *crowd = (*cf).CreateCrowd();

	//获取通信节点
	string comNodeStr;
	list<CommunicationNode> *comNode = getAllCommunicationNode(comNodeStr);

	//开始模拟
	ProcessManagement process;
	process.startSimulation(*comNode, *protocol, *channel, *crowd);

	//将模拟之后的结果保存成json串
	stringstream ss;
	string res = "";
	list<CommunicationNode>::iterator iter;
	bool flag = true;
	ss << "\"CommunicationNode\": " << "[";
	for (iter = (*comNode).begin(); iter != (*comNode).end(); iter++)
	{
		if (flag == true) {
			ss << (*iter).toJson();
			flag = false;
		}
		else {
			ss << ", " << (*iter).toJson();
		}
	}
	ss << "]}";
	ss >> res;
	return res;
}
