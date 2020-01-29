#include "SMTP_Cmd.h"
#include "CommonMsg.h"
#include <memory>
class C_SMTP_Handler
{
public:
	C_SMTP_Handler();
	virtual ~C_SMTP_Handler();
	bool HandleServerRsp(const std::string strSmtpRsp);
	static IpPortCfg GetSmtpIpServerAddr(const std::string strUserEmail);
	void SaveUserLogin(const UserLoginReqMsg& reqMsg);
	void SaveSendEmail(const SendEmailReq& reqMsg);
private:
	bool HandleServer220Rsp(const C_SMTP_Server_On_Connect_Rsp& rspMsg);
	bool HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg);
	UserLoginReqMsg loginReq;
	SendEmailReq sendEmailReq;
};
using C_SMTP_Handler_PTR = std::shared_ptr<C_SMTP_Handler>;