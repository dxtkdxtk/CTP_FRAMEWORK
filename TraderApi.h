#include"ThostTraderApi\ThostFtdcTraderApi.h"

#include<set>
#include<map>
#include<list>
#include<string>

using namespace std;

class TraderApi : public CThostFtdcTraderSpi
{
public :
    TraderApi(void);
    ~TraderApi(void);

    void Connect(const string& szPath,
        const string& szAddresses,
        const string& szBrokerId,
        const string& szInvestorId,
        const string& szPassword,
        THOST_TE_RESUME_TYPE nResumeType,
        const string& szUserProductInfo,
        const string& szAuthCode);
    void Disconnect();

    int ReqOrderInsert(
        const string& szInstrumentId,
        TThostFtdcDirectionType Direction,
        const TThostFtdcCombOffsetFlagType CombOffsetFlag,
        const TThostFtdcCombHedgeFlagType CombHedgeFlag,
        TThostFtdcVolumeType VolumeTotalOriginal,
        TThostFtdcPriceType LimitPrice,
        TThostFtdcOrderPriceTypeType OrderPriceType,
        TThostFtdcTimeConditionType TimeCondition,
        TThostFtdcContingentConditionType ContingentCondition,
        TThostFtdcPriceType StopPrice,
        TThostFtdcVolumeConditionType VolumeCondition);
    void ReqOrderAction(CThostFtdcOrderField *pOrder);
    

    void ReqQryTradingAccount();
    void ReqQryInvestorPosition(const string& szInstrumentId);
    void ReqQryInvestorPositionDetail(const string& szInstrumentId);
    void ReqQryInstrument(const string& szInstrumentId);
    void ReqQryInstrumentCommissionRate(const string& szInstrumentId);
    void ReqQryInstrumentMarginRate(const string& szInstrumentId, TThostFtdcHedgeFlagType HedgeFlag = THOST_FTDC_HF_Speculation);
    void ReqQryDepthMarketData(const string& szInstrumentId);

private:
    //登陆相关
    void ReqAuthenticate();
    void ReqUserLogin();
    void ReqSettlementInfoConfirm();

    //错误信息
    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);//不输出信息

    //连接
    virtual void OnFrontConnected();
    virtual void OnFrontDisconnected(int nReason);

    //认证
    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //下单
    virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

    //撤单
    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

    //报单回报
    virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

    //撤单回报
    virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

    //仓位
    virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    //资金
    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //合约、手续费
    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //查询行情响应
    virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    //其它
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);
private:
    
};