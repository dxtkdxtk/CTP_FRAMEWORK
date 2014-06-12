#ifndef STASTRUCT_H
#define STATRUCT_H
#include"MdUserApi.h"
#include"TraderApi.h"
using namespace std;
class StrategyStruct
{
    //定义策略使用的数据结构
public:
    StrategyStruct()
    {
        msgQueue = new CTPMsgQueue();
        callbackSet = new FunctionCallBackSet();
        msgQueue->RegisterCallback(callbackSet);
        md = new MdUserApi();
        md->RegisterMsgQueue(msgQueue);
        td = new TraderApi();
        td->RegisterMsgQueue(msgQueue);
        msgQueue->StartThread();
    }
    ~StrategyStruct()
    {
        msgQueue->StopThread();
        msgQueue->Clear();
        td->Disconnect();
        md->Disconnect();
        delete callbackSet;
        delete msgQueue;
    }
    void readInifile(char* file)
    {
        GetPrivateProfileStringA("simServer", "path", "", tmp, sizeof(tmp), file);
        streamPath = tmp;
        GetPrivateProfileStringA("simServer", "mdserver", "", tmp, sizeof(tmp), file);
        mdServer = tmp;
        GetPrivateProfileStringA("simServer", "tdserver", "", tmp, sizeof(tmp), file);
        tdServer = tmp;
        GetPrivateProfileStringA("simServer", "brokerid", "", tmp, sizeof(tmp), file);
        brokerId = tmp;
        GetPrivateProfileStringA("investor", "investorid", "", tmp, sizeof(tmp), file);
        investorId = tmp;
        GetPrivateProfileStringA("investor", "password", "", tmp, sizeof(tmp), file);
        password = tmp;
        GetPrivateProfileStringA("simServer", "instrument", "", tmp, sizeof(tmp), file);
        instrumentId = tmp;
    }
    char tmp[105];
    CTPMsgQueue *msgQueue;
    string streamPath;
    string mdServer;
    string tdServer;
    string brokerId;
    string investorId;
    string password;
    string instrumentId;
    MdUserApi *md;
    TraderApi *td;
    FunctionCallBackSet *callbackSet;


};

#endif

