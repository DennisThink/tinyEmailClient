#include "SMTP_Cmd.h"
#include <memory>
class C_SMTP_Handler
{
public:
	C_SMTP_Handler();
	virtual ~C_SMTP_Handler();
	bool HandleServerRsp(const std::string strSmtpRsp);

private:
	bool HandleServer220Rsp(const C_SMTP_Server_On_Connect_Rsp& rspMsg);
	bool HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg);
};
using C_SMTP_Handler_PTR = std::shared_ptr<C_SMTP_Handler>;