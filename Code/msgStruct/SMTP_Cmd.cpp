#include "SMTP_Cmd.h"
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
	return false;
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
	return "";
}

bool C_SMTP_Client_AuthLoginReq::FromString(const std::string strSmtp)
{
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
	return false;
}
C_SMTP_Client_UserNameRsp::C_SMTP_Client_UserNameRsp()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
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
	return "";
}

bool C_SMTP_Client_UserNameRsp::FromString(const std::string strSmtp)
{
	return false;
}

C_SMTP_Client_PassWordRsp::C_SMTP_Client_PassWordRsp()
{
	m_type = SMTP_CMD_TYPE::S_C_SERVER_QUIT_RSP;
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
	return "";
}

bool C_SMTP_Client_PassWordRsp::FromString(const std::string strSmtp)
{
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