#include "SMTP_Cmd.h"
#include "base64.h"
SMTP_CODE GetServerRspCode(const std::string strRsp)
{
	if (strRsp.length() > 3)
	{
		std::string strCode = strRsp.substr(0, 3);
		int nCode = std::atoi(strCode.c_str());
		switch (nCode)
		{
		case 220:
		{
			return SMTP_CODE::CODE_220;
		}break;
		case 250:
		{
			return SMTP_CODE::CODE_250;
		}break;
		case 334:
		{
			return SMTP_CODE::CODE_334;
		}break;
		case 235:
		{
			return SMTP_CODE::CODE_235;
		}break;
		case 354:
		{
			return SMTP_CODE::CODE_354;
		}break;
		case 221:
		{
			return SMTP_CODE::CODE_221;
		}break;
		default:
		{
			return SMTP_CODE::CODE_UN_KNOWN;
		}break;
		}
	}
	return SMTP_CODE::CODE_UN_KNOWN;
}


C_SMTP_CMD_BASE::C_SMTP_CMD_BASE()
{
	m_type = SMTP_CMD_TYPE::UnKnown;
}

C_SMTP_CMD_BASE::~C_SMTP_CMD_BASE()
{

}

SMTP_CMD_TYPE C_SMTP_CMD_BASE::GetCmdType()
{
	return SMTP_CMD_TYPE::UnKnown;
}

std::string C_SMTP_CMD_BASE::ToString()
{
	return "";
}

bool C_SMTP_CMD_BASE::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Server_On_Connect_Rsp::C_SMTP_Server_On_Connect_Rsp()
{

}

C_SMTP_Server_On_Connect_Rsp::~C_SMTP_Server_On_Connect_Rsp()
{

}

SMTP_CMD_TYPE C_SMTP_Server_On_Connect_Rsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_On_Connect_Rsp::ToString()
{
	return "220 dennisthink.com For TinyEmail System[20200130]\r\n";
}

bool C_SMTP_Server_On_Connect_Rsp::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 3)
	{
		if ("220" == strSmtp.substr(0, 3))
		{
			return true;
		}
	}
	return false;
}


/*
C_SMTP_CMD_BASE::C_SMTP_CMD_BASE()
{
	m_type = SMTP_CMD_TYPE::UnKnown;
}

C_SMTP_CMD_BASE::~C_SMTP_CMD_BASE()
{

}

SMTP_CMD_TYPE C_SMTP_CMD_BASE::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_CMD_BASE::ToString()
{
	return "";
}

bool C_SMTP_CMD_BASE::FromString(const std::string strSmtp)
{
	return false;
}
*/


C_SMTP_Client_HELO_CmdReq::C_SMTP_Client_HELO_CmdReq()
{
	m_type = SMTP_CMD_TYPE::C_S_HELO_REQ;
}

C_SMTP_Client_HELO_CmdReq::~C_SMTP_Client_HELO_CmdReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_HELO_CmdReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_HELO_CmdReq::ToString()
{
	return "HELO SMTP.163.com\r\n";
}

bool C_SMTP_Client_HELO_CmdReq::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "HELO")
		{
			return true;
		}
	}
	return false;
}

C_SMTP_Client_EHLO_CmdReq::C_SMTP_Client_EHLO_CmdReq()
{
	m_type = SMTP_CMD_TYPE::C_S_EHLO_REQ;
}

C_SMTP_Client_EHLO_CmdReq::~C_SMTP_Client_EHLO_CmdReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_EHLO_CmdReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_EHLO_CmdReq::ToString()
{
	return "EHLO SMTP.163.com\r\n";
}

bool C_SMTP_Client_EHLO_CmdReq::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "EHLO")
		{
			return true;
		}
	}
	return false;
}


C_SMTP_Server_250_Rsp::C_SMTP_Server_250_Rsp()
{
	m_type = SMTP_CMD_TYPE::UnKnown;
}

C_SMTP_Server_250_Rsp::~C_SMTP_Server_250_Rsp()
{

}

SMTP_CMD_TYPE C_SMTP_Server_250_Rsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_250_Rsp::ToString()
{
	return "";
}

bool C_SMTP_Server_250_Rsp::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "250-")
		{
			m_bRspFinished = false;
			return true;
		}
		else if(strSmtp.substr(0,4) == "250 ")
		{
			m_bRspFinished = true;
			return true;
		}
	}
	return false;
}

bool C_SMTP_Server_250_Rsp::IsServerRspFinished() const {
	return m_bRspFinished;
}



C_SMTP_Client_AuthLoginReq::C_SMTP_Client_AuthLoginReq()
{
	m_type = SMTP_CMD_TYPE::C_S_AUTH_LOGIN_REQ;
}

C_SMTP_Client_AuthLoginReq::~C_SMTP_Client_AuthLoginReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_AuthLoginReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_AuthLoginReq::ToString()
{
	return "AUTH LOGIN\r\n";
}

bool C_SMTP_Client_AuthLoginReq::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "235 ")
		{
			return true;
		}
	}
	return false;
}


C_SMTP_Server_UserNameReq::C_SMTP_Server_UserNameReq()
{
	m_type = SMTP_CMD_TYPE::S_C_USER_NAME_REQ;
}

C_SMTP_Server_UserNameReq::~C_SMTP_Server_UserNameReq()
{

}

SMTP_CMD_TYPE C_SMTP_Server_UserNameReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_UserNameReq::ToString()
{
	return "";
}

bool C_SMTP_Server_UserNameReq::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "334 ")
		{
			std::string strUserName = base64_decode(strSmtp.substr(4, strSmtp.length() - 4));
			return true;
		}
	}
	return false;
}


C_SMTP_Server_PassWordReq::C_SMTP_Server_PassWordReq()
{
	m_type = SMTP_CMD_TYPE::S_C_PASS_WORD_REQ;
}

C_SMTP_Server_PassWordReq::~C_SMTP_Server_PassWordReq()
{

}

SMTP_CMD_TYPE C_SMTP_Server_PassWordReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_PassWordReq::ToString()
{
	return "";
}

bool C_SMTP_Server_PassWordReq::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "334 ")
		{
			std::string strUserName = base64_decode(strSmtp.substr(4, strSmtp.length() - 6));
			return true;
		}
	}
	return false;
}
C_SMTP_Client_UserNameRsp::C_SMTP_Client_UserNameRsp(const std::string strUserName)
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
	m_strUserName = strUserName;
}

C_SMTP_Client_UserNameRsp::~C_SMTP_Client_UserNameRsp()
{

}

SMTP_CMD_TYPE C_SMTP_Client_UserNameRsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_UserNameRsp::ToString()
{
	return base64_encode(reinterpret_cast<const unsigned char *>(m_strUserName.data()),m_strUserName.length())+"\r\n";
}

bool C_SMTP_Client_UserNameRsp::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Client_PassWordRsp::C_SMTP_Client_PassWordRsp(const std::string strPassWord)
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
	m_strPassWord = strPassWord;
}

C_SMTP_Client_PassWordRsp::~C_SMTP_Client_PassWordRsp()
{

}

SMTP_CMD_TYPE C_SMTP_Client_PassWordRsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_PassWordRsp::ToString()
{
	return base64_encode(reinterpret_cast<const unsigned char *>(m_strPassWord.data()), m_strPassWord.length()) + "\r\n";
}

bool C_SMTP_Client_PassWordRsp::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Client_RecvToReq::C_SMTP_Client_RecvToReq(const std::string strRecvEmail)
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
	m_strRecvEmail = strRecvEmail;
}

C_SMTP_Client_RecvToReq::~C_SMTP_Client_RecvToReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_RecvToReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_RecvToReq::ToString()
{
	return "RCPT TO: <"+m_strRecvEmail+">\r\n";
}

bool C_SMTP_Client_RecvToReq::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Client_MailFromReq::C_SMTP_Client_MailFromReq(const std::string strUserEmail)
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
	m_strUserEmail = strUserEmail;
}

C_SMTP_Client_MailFromReq::~C_SMTP_Client_MailFromReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_MailFromReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_MailFromReq::ToString()
{
	return "MAIL FROM: <"+m_strUserEmail+">\r\n";
}

bool C_SMTP_Client_MailFromReq::FromString(const std::string strSmtp)
{
	return false;
}



C_SMTP_Server_AuthSuccessRsp::C_SMTP_Server_AuthSuccessRsp()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
}

C_SMTP_Server_AuthSuccessRsp::~C_SMTP_Server_AuthSuccessRsp()
{

}

SMTP_CMD_TYPE C_SMTP_Server_AuthSuccessRsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_AuthSuccessRsp::ToString()
{
	return "";
}

bool C_SMTP_Server_AuthSuccessRsp::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "235 ")
		{
			std::string strUserName = base64_decode(strSmtp.substr(4, strSmtp.length() - 6));
			return true;
		}
	}
	return false;
}
C_SMTP_Server_QuitRsp::C_SMTP_Server_QuitRsp()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
}

C_SMTP_Server_QuitRsp::~C_SMTP_Server_QuitRsp()
{

}

SMTP_CMD_TYPE C_SMTP_Server_QuitRsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_QuitRsp::ToString()
{
	return "";
}

bool C_SMTP_Server_QuitRsp::FromString(const std::string strSmtp)
{
	return false;
}


C_SMTP_Server_DataBeginRsp::C_SMTP_Server_DataBeginRsp()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
}

C_SMTP_Server_DataBeginRsp::~C_SMTP_Server_DataBeginRsp()
{

}

SMTP_CMD_TYPE C_SMTP_Server_DataBeginRsp::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Server_DataBeginRsp::ToString()
{
	return "";
}

bool C_SMTP_Server_DataBeginRsp::FromString(const std::string strSmtp)
{
	if (strSmtp.length() > 4)
	{
		if (strSmtp.substr(0, 4) == "354 ")
		{
			return true;
		}
	}
	return false;
}


C_SMTP_Client_DataBeginReq::C_SMTP_Client_DataBeginReq()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
}

C_SMTP_Client_DataBeginReq::~C_SMTP_Client_DataBeginReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_DataBeginReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_DataBeginReq::ToString()
{
	return "DATA\r\n";
}

bool C_SMTP_Client_DataBeginReq::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Client_DataBodyReq::C_SMTP_Client_DataBodyReq()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
}

C_SMTP_Client_DataBodyReq::~C_SMTP_Client_DataBodyReq()
{

}

SMTP_CMD_TYPE C_SMTP_Client_DataBodyReq::GetCmdType()
{
	return m_type;
}

std::string C_SMTP_Client_DataBodyReq::ToString()
{
	std::string strResult = "Subject:" + m_strSubject + "\r\n";
	strResult = strResult + "From:\"\"<" + m_strFrom + ">\r\n";
	strResult = strResult + "To:\"\"<" + m_strTo + ">\r\n";
	strResult += "\r\n\r\n";
	strResult = strResult + m_strContext;
	strResult = strResult + "\r\n.\r\n";
	return strResult;
}

bool C_SMTP_Client_DataBodyReq::FromString(const std::string strSmtp)
{
	return false;
}