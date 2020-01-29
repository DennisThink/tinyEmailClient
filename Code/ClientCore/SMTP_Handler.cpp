#include "SMTP_Handler.h"
#include "asio_common.h"

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

IpPortCfg C_SMTP_Handler::GetSmtpIpServerAddr(const std::string strUserEmail)
{
	IpPortCfg result;
	auto nPos = strUserEmail.find("@");
	if (nPos != std::string::npos)
	{
		const int DEFAULT_SMTP_PORT = 25;
		std::string strSmtpServer = "smtp." + strUserEmail.substr(nPos, strUserEmail.length() - nPos);
		asio::io_context context;
		asio::ip::tcp::resolver rlv(context);
		asio::ip::tcp::resolver::query query(strSmtpServer);
		
		asio::ip::tcp::resolver::iterator end;
		for (auto item = rlv.resolve(query); item != end; item++)
		{
			IpPortCfg cfg;
			cfg.m_strServerIp = item->endpoint().address().to_string();
			cfg.m_nPort = DEFAULT_SMTP_PORT;
			result = cfg;
			break;
		}
	}

	return result;
}

void C_SMTP_Handler::SaveUserLogin(const UserLoginReqMsg& reqMsg)
{
	loginReq = reqMsg;
}

void C_SMTP_Handler::SaveSendEmail(const SendEmailReq& reqMsg)
{
	sendEmailReq = reqMsg;
}