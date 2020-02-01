#ifndef _DENNIS_THINK_IMAP_HANDLER_H_
#define _DENNIS_THINK_IMAP_HANDLER_H_
#include <memory>
#include "IMAP_Cmd.h"
#include "CommonMsg.h"
#include "Log.h"
class C_IMAP_Handler
{
public:
	C_IMAP_Handler();
	virtual ~C_IMAP_Handler();
	bool HandleServerRsp(const std::string strSmtpRsp);
	static IpPortCfg GetImapIpServerAddr(const std::string strUserEmail);
	std::shared_ptr<C_IMAP_BASE> GetNextMsg();
	void SaveUserLogin(const UserLoginReqMsg& reqMsg);
	static std::shared_ptr<spdlog::logger> ms_loger;
private:
	
	UserLoginReqMsg loginReq;
	SendEmailReq sendEmailReq;
	std::shared_ptr<C_IMAP_BASE> m_pNextMsg;
};
using C_IMAP_Handler_PTR = std::shared_ptr<C_IMAP_Handler>;
#endif