#include "IMAP_Handler.h"
std::shared_ptr<spdlog::logger> C_IMAP_Handler::ms_loger=nullptr;
C_IMAP_Handler::C_IMAP_Handler() 
{
	m_step = IMAP_STEP::ON_SERVER_CONNECT_STEP;
}

C_IMAP_Handler::~C_IMAP_Handler()
{

}
bool C_IMAP_Handler::HandleServerRsp(const std::string strSmtpRsp)
{
	LOG_INFO(ms_loger, "IMAP RECV:{} [{} {}]", strSmtpRsp, __FILENAME__, __LINE__);
	switch (m_step)
	{
	case IMAP_STEP::ON_SERVER_CONNECT_STEP:
	{
		C_IMAP_Server_On_Connect rspMsg;
		if (rspMsg.FromString(strSmtpRsp))
		{
			HandleServerOnConnect(rspMsg);
		}
	}break;
	case IMAP_STEP::SEND_LOGIN_STEP:
	{
		C_IMAP_Server_Login_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp)) {
			HandleServerLoginRsp(rspMsg);
		}
	}break;
	case IMAP_STEP::SEND_SELECT_ALL_STEP:
	{
		C_IMAP_Server_SelectAll_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp)) {
			HandleServerSelectAll(rspMsg);
		}
	}break;
	case IMAP_STEP::SEND_FETCH_EMAIL_STEP:
	{
		C_IMAP_Server_FetchEmail_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp)) {
			HandleServerFetchEmail(rspMsg);
		}
	}break;
	case IMAP_STEP::SEND_LOGOUT_STEP:
	{
		C_IMAP_Server_Logout_Rsp rspMsg;
		if (rspMsg.FromString(strSmtpRsp)) {
			HandleServerLogoutRsp(rspMsg);
		}
	}
	default:
	{

	}break;
	}

	return false;
}
bool C_IMAP_Handler::HandleServerOnConnect(const C_IMAP_Server_On_Connect& rspMsg)
{
	auto pMsg = std::make_shared<C_IMAP_Client_Login_Req>();
	pMsg->m_LoginReq = loginReq;
	m_pNextMsg = pMsg;
	return true;
}

bool C_IMAP_Handler::HandleServerLoginRsp(const C_IMAP_Server_Login_Rsp& rspMsg)
{
	if (rspMsg.IsOK())
	{
		m_pNextMsg = std::make_shared<C_IMAP_Client_SelectAll_Req>();
	}
	return false;
}

bool C_IMAP_Handler::HandleServerFetchEmail(const C_IMAP_Server_FetchEmail_Rsp& rspMsg)
{
	if(rspMsg.IsOK())
	{
		m_pNextMsg = std::make_shared<C_IMAP_Client_Logout_Req>();
	}
	return false;
}
bool C_IMAP_Handler::HandleServerSelectAll(const C_IMAP_Server_SelectAll_Rsp& rspMsg)
{
	if (rspMsg.IsOK())
	{
		m_pNextMsg = std::make_shared<C_IMAP_Client_FetchEmail_Req>();
	}
	return false;
}

bool C_IMAP_Handler::HandleServerLogoutRsp(const C_IMAP_Server_Logout_Rsp& rspMsg)
{
	return false;
}


IpPortCfg C_IMAP_Handler::GetImapIpServerAddr(const std::string strUserEmail)
{
	IpPortCfg result;
	auto nPos = strUserEmail.find("@");
	if (nPos != std::string::npos)
	{
		const int DEFAULT_IMAP_PORT = 143;
		std::string strSmtpServer = "imap." + strUserEmail.substr(nPos + 1, strUserEmail.length() - nPos - 1);
		result.m_strServerIp = strSmtpServer;
		result.m_nPort = DEFAULT_IMAP_PORT;
	}

	return result;
}
std::shared_ptr<C_IMAP_BASE> C_IMAP_Handler::GetNextMsg()
{
	auto pResult = m_pNextMsg;
	m_pNextMsg = nullptr;
	return pResult;
}

void C_IMAP_Handler::SaveUserLogin(const UserLoginReqMsg& reqMsg)
{
	loginReq = reqMsg;
}

