#ifndef _DENNIS_THINK_C_SMTP_HANDLER_H_
#define _DENNIS_THINK_C_SMTP_HANDLER_H_

#include <memory>
#include "SMTP_Cmd.h"
#include "CommonMsg.h"
#include "Log.h"
class C_SMTP_Handler
{
public:
	C_SMTP_Handler();
	virtual ~C_SMTP_Handler();
	bool HandleServerRsp(const std::string strSmtpRsp);
	static IpPortCfg GetSmtpIpServerAddr(const std::string strUserEmail);
	std::shared_ptr<C_SMTP_CMD_BASE> GetNextMsg();
	void SaveUserLogin(const UserLoginReqMsg& reqMsg);
	void SaveSendEmail(const SendEmailReq& reqMsg);
	static std::shared_ptr<spdlog::logger> ms_loger;
private:
	bool HandleServer220Rsp(const C_SMTP_Server_On_Connect_Rsp& rspMsg);
	bool HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg);
	bool HandleServerUserNameReq(const C_SMTP_Server_UserNameReq& rspMsg);
	bool HandleServerPasswordReq(const C_SMTP_Server_PassWordReq& rspMsg);
	bool HandleServerDataBeginRsp(const C_SMTP_Server_DataBeginRsp& rspMsg);
	bool HandleServerQuitRsp(const C_SMTP_Server_QuitRsp& rspMsg);
	UserLoginReqMsg loginReq;
	SendEmailReq sendEmailReq;
	std::shared_ptr<C_SMTP_CMD_BASE> m_pNextMsg;
	SMTP_STEP m_step;
};
using C_SMTP_Handler_PTR = std::shared_ptr<C_SMTP_Handler>;
#endif