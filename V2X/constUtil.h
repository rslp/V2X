#pragma once
/*
 *相关常量的定义
*/

#define CHANNEL_COUNT 7 //信道个数，也是待送达队列的长度
#define BIT_RATE 1000000000 //误码率10^-9
#define REACHDISTANCE 300   //两车能通信的最远距离
#define EARTH_RADIUS 6371004; //地球半径
#define PI 3.14159 //π值
#define BACK_OFF 3  //退避时间的最大值
#define MTU 400//分片消息的最大大小
#define HEADLENGTH 6//消息头部大小