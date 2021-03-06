#pragma once
#include "SliceMessage.h"
#include "CommunicationNode.h"
 
/*消息检查*/

//误码检查
bool errorCheck(SliceMessage sMsg);

//可达检测
bool reachCheck(SliceMessage sMsg, CommunicationNode dest, list<CommunicationNode> communicationNodes);