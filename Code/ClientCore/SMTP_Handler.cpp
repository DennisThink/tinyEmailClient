#include "SMTP_Handler.h"


C_SMTP_Handler::C_SMTP_Handler()
{
}

C_SMTP_Handler::~C_SMTP_Handler()
{

}

bool C_SMTP_Handler::HandleServerRsp(const std::string strSmtpRsp)
{
	return false;
}


bool C_SMTP_Handler::HandleServer220Rsp(const C_SMTP_Server_On_Connect_Rsp& rspMsg)
{
	return false;
}

bool C_SMTP_Handler::HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg)
{
	return false;
}