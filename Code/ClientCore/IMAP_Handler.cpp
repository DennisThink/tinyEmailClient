#include "IMAP_Handler.h"
std::shared_ptr<spdlog::logger> C_IMAP_Handler::ms_loger=nullptr;
C_IMAP_Handler::C_IMAP_Handler() 
{

}

C_IMAP_Handler::~C_IMAP_Handler()
{

}
bool C_IMAP_Handler::HandleServerRsp(const std::string strSmtpRsp)
{
	LOG_INFO(ms_loger, "IMAP RECV:{} [{} {}]", strSmtpRsp, __FILENAME__, __LINE__);
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

