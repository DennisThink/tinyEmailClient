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
		if(SMTP_STEP::ON_SERVER_250_STEP == m_step)
		{
			C_SMTP_Server_UserNameReq rspMsg;
			if (rspMsg.FromString(strSmtpRsp))
			{
				HandleServerUserNameReq(rspMsg);
			}
		}
		else if(SMTP_STEP::ON_SERVER_USER_NAME_STEP == m_step)
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
	case SMTP_CODE::CODE_235:
	{
		C_SMTP_Server_AuthSuccessRsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServerAuthSuccessRsp(rspMsg);
		}
	}break;
	case SMTP_CODE::CODE_354:
	{
		C_SMTP_Server_DataBeginRsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServerDataBeginRsp(rspMsg);
		}
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
	auto pNextMsg = std::make_shared<C_SMTP_Client_EHLO_CmdReq>();
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServer250Rsp(const C_SMTP_Server_250_Rsp& rspMsg)
{
	if (SMTP_STEP::ON_CONNECT_STEP == m_step)
	{
		if (rspMsg.IsServerRspFinished())
		{
			auto pNextMsg = std::make_shared<C_SMTP_Client_AuthLoginReq>();
			m_pNextMsg = pNextMsg;
			m_step = SMTP_STEP::ON_SERVER_250_STEP;
		}
	}
	else if (SMTP_STEP::ON_SERVER_AUTH_SUCCEED_STEP == m_step)
	{
		m_step = SMTP_STEP::ON_SERVER_MAIL_FROM_STEP;
		if (rspMsg.IsServerRspFinished())
		{
			auto pNextMsg = std::make_shared<C_SMTP_Client_MailFromReq>(sendEmailReq.m_strUserName);
			m_pNextMsg = pNextMsg;
		}
	}
	else if (SMTP_STEP::SEND_MAIL_FROM_STEP == m_step)
	{
		//m_step = SMTP_STEP::ON_SERVER_SEND_DATA_BEGIN_RSP;
		if (rspMsg.IsServerRspFinished())
		{
			auto pNextMsg = std::make_shared<C_SMTP_Client_RecvToReq>(sendEmailReq.m_strRecvName);
			m_pNextMsg = pNextMsg;
			m_step = SMTP_STEP::SEND_RCPT_TO_STEP;
		}
	}
	else if (SMTP_STEP::SEND_RCPT_TO_STEP == m_step)
	{
		if (rspMsg.IsServerRspFinished())
		{
			auto pNextMsg = std::make_shared<C_SMTP_Client_DataBeginReq>();
			m_pNextMsg = pNextMsg;
			m_step = SMTP_STEP::SEND_DATA_BEGIN_STEP;
		}
	}

	return true;
}

bool C_SMTP_Handler::HandleServerUserNameReq(const C_SMTP_Server_UserNameReq& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_USER_NAME_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_UserNameRsp>(loginReq.m_strUserName);
	m_pNextMsg = pNextMsg;
	return true;
}

bool C_SMTP_Handler::HandleServerPasswordReq(const C_SMTP_Server_PassWordReq& rspMsg)
{
	m_step = SMTP_STEP::ON_SERVER_PASS_WORD_STEP;
	auto pNextMsg = std::make_shared<C_SMTP_Client_PassWordRsp>(loginReq.m_strPassword);
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
	auto pMsg = std::make_shared<C_SMTP_Client_DataBodyReq>();
	pMsg->m_strFrom = sendEmailReq.m_strUserName;
	pMsg->m_strTo = sendEmailReq.m_strRecvName;
	pMsg->m_strSubject = sendEmailReq.m_strSubject;
	pMsg->m_strContext = sendEmailReq.m_strEmailContext;
	m_pNextMsg = pMsg;
	return true;
}

bool C_SMTP_Handler::HandleServerAuthSuccessRsp(const C_SMTP_Server_AuthSuccessRsp& rspMsg)
{
	m_pNextMsg = std::make_shared<C_SMTP_Client_MailFromReq>(sendEmailReq.m_strUserName);
	m_step = SMTP_STEP::SEND_MAIL_FROM_STEP;
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