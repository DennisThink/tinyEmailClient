#include "SMTP_Handler.h"
#include "asio_common.h"

std::shared_ptr<spdlog::logger> C_SMTP_Handler::ms_loger = nullptr;
C_SMTP_Handler::C_SMTP_Handler()
{
}

C_SMTP_Handler::~C_SMTP_Handler()
{

}

bool C_SMTP_Handler::HandleServerRsp(const std::string strSmtpRsp)
{
	LOG_INFO(ms_loger, "SMTP Recv:{} [{} {}]", strSmtpRsp, __FILENAME__, __LINE__);
	auto nCode = GetServerRspCode(strSmtpRsp);
	switch (nCode)
	{
	case SMTP_CODE::CODE_220:
	{
		C_SMTP_Server_On_Connect_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServer220Rsp(rspMsg);
		}
	}break;
	case SMTP_CODE::CODE_250:
	{
		C_SMTP_Server_250_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServer250Rsp(rspMsg);
		}
	}break;
	case SMTP_CODE::CODE_334:
	{
		{
			C_SMTP_Server_UserNameReq rspMsg;
			if (rspMsg.FromString(strSmtpRsp))
			{
				HandleServerUserNameReq(rspMsg);
			}
		}

		{
			C_SMTP_Server_PassWordReq rspMsg;
			if (rspMsg.FromString(strSmtpRsp))
			{
				HandleServerPasswordReq(rspMsg);
			}
		}
	}break;
	case SMTP_CODE::CODE_221:
	{
		C_SMTP_Server_QuitRsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServerQuitRsp(rspMsg);
		}
	}break;
	case SMTP_CODE::CODE_354:
	{

	}break;
	default:
	{

	}break;
	}
	return false;
}
std::shared_ptr<C_SMTP_CMD_BASE> C_SMTP_Handler::GetNextMsg()
{
	auto pResult = m_pNextMsg;
	m_pNextMsg = nullptr;
	return pResult;
}

bool C_SMTP_Handler::HandleServer220Rsp(const C_SMTP_Server_On_Connect_Rsp& rspMsg)
{
	m_step = SMTP_STEP::ON_CONNECT_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_HELO_CmdReq>();
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_250_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_AuthLoginReq>();
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServerUserNameReq(const C_SMTP_Server_UserNameReq& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_USER_NAME_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_UserNameRsp>();
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServerPasswordReq(const C_SMTP_Server_PassWordReq& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_PASS_WORD_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_PassWordRsp>();
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServerQuitRsp(const C_SMTP_Server_QuitRsp& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_QUIT_STEP;
	return true;
}

bool C_SMTP_Handler::HandleServerDataBeginRsp(const C_SMTP_Server_DataBeginRsp& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_SEND_DATA_BEGIN_RSP;
	return true;
}



IpPortCfg C_SMTP_Handler::GetSmtpIpServerAddr(const std::string strUserEmail)
{
	IpPortCfg result;
	auto nPos = strUserEmail.find("@");
	if (nPos != std::string::npos)
	{
		const int DEFAULT_SMTP_PORT = 25;
		std::string strSmtpServer = "smtp." + strUserEmail.substr(nPos+1, strUserEmail.length() - nPos-1);
		result.m_strServerIp = strSmtpServer;
		result.m_nPort = DEFAULT_SMTP_PORT;
		//asio::io_context context;
		//asio::ip::tcp::resolver rlv(context);
		//asio::ip::tcp::resolver::query query(strSmtpServer);
		//
		//asio::ip::tcp::resolver::iterator end;
		//for (auto item = rlv.resolve(query); item != end; item++)
		//{
		//	IpPortCfg cfg;
		//	cfg.m_strServerIp = item->endpoint().address().to_string();
		//	cfg.m_nPort = DEFAULT_SMTP_PORT;
		//	result = cfg;
		//	break;
		//}
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