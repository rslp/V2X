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

	//将模拟之后的结果保存
	string res = "";
	list<CommunicationNode>::iterator iter;
	for (iter = (*comNode).begin(); iter != (*comNode).end(); iter++)
	{
		list<Message> recvList = *(*iter).getMessageToRecv();
		if (recvList.size() == 0) {
			continue;
		}
		else {
			if (iter == (*comNode).begin()) {
				res += "{\"CommunicationNode:\": [{\"ID\":";
			}
			else {
				res += ", {\"ID\":"; //通信节点ID
			}
				res += (*iter).getNodeID();
				res += ",";
				res += "\"ReceiveMessage\": [ ";
				//通信节点收到的消息
				list<Message>::iterator msgIter;
				for (msgIter = recvList.begin(); msgIter != recvList.end(); msgIter++) {

					if (msgIter != recvList.begin()) {
						res += ",";
					}
					res += "{\"MessageID\":";
					res += (*msgIter).getMessageID();
					res += ", \"sendID\": ";
					res += (*msgIter).getSourceAddress();
					res += ", \"size\": ";
					res += (*msgIter).getSize();
				}
				res += "]}";
		}
	}
	return res;
}
