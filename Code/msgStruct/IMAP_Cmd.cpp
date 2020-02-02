#include "IMAP_Cmd.h"


C_IMAP_BASE::C_IMAP_BASE() 
{

}

C_IMAP_BASE::~C_IMAP_BASE()
{

}
IMAP_TYPE C_IMAP_BASE::GetType()
{
	return m_type;
}

std::string C_IMAP_BASE::ToString()
{
	return "";
}

bool C_IMAP_BASE::FromString(const std::string strImap)
{
	return false;
}

std::string C_IMAP_BASE::GetCmdId() {
	return m_strCmdId;
}

bool C_IMAP_BASE::IsOK() {
	return m_bIsOk;
}
/*

C_IMAP_BASE::C_IMAP_BASE()
{

}

C_IMAP_BASE::~C_IMAP_BASE()
{

}
IMAP_TYPE C_IMAP_BASE::GetType()
{
	return m_type;
}

std::string C_IMAP_BASE::ToString()
{
	return "";
}

bool C_IMAP_BASE::FromString(const std::string strImap)
{
	return false;
}

*/

C_IMAP_Server_On_Connect::C_IMAP_Server_On_Connect()
{
	m_type = IMAP_TYPE::IMAP_SERVER_CONNECT;
}

C_IMAP_Server_On_Connect::~C_IMAP_Server_On_Connect()
{

}
IMAP_TYPE C_IMAP_Server_On_Connect::GetType()
{
	return m_type;
}

std::string C_IMAP_Server_On_Connect::ToString()
{
	return "* OK TinyEmail System IMap Server Ready(dennisthink[20200201])";
}

bool C_IMAP_Server_On_Connect::FromString(const std::string strImap)
{
	if (strImap.find("* OK") != std::string::npos)
	{
		return true;
	}
	return false;
}


C_IMAP_Client_Login_Req::C_IMAP_Client_Login_Req()
{
	m_type = IMAP_TYPE::IMAP_SERVER_CONNECT;
}

C_IMAP_Client_Login_Req::~C_IMAP_Client_Login_Req()
{

}
IMAP_TYPE C_IMAP_Client_Login_Req::GetType()
{
	return m_type;
}

std::string C_IMAP_Client_Login_Req::ToString()
{
	return "* OK TinyEmail System IMap Server Ready(dennisthink[20200201])";
}

bool C_IMAP_Client_Login_Req::FromString(const std::string strImap)
{
	if (strImap.find("* OK") != std::string::npos)
	{
		return true;
	}
	return false;
}

C_IMAP_Server_Login_Rsp::C_IMAP_Server_Login_Rsp()
{
	m_type = IMAP_TYPE::IMAP_SERVER_CONNECT;
}

C_IMAP_Server_Login_Rsp::~C_IMAP_Server_Login_Rsp()
{

}
IMAP_TYPE C_IMAP_Server_Login_Rsp::GetType()
{
	return m_type;
}

std::string C_IMAP_Server_Login_Rsp::ToString()
{
	return "* OK TinyEmail System IMap Server Ready(dennisthink[20200201])";
}

bool C_IMAP_Server_Login_Rsp::FromString(const std::string strImap)
{
	if (strImap.find("* OK") != std::string::npos)
	{
		return true;
	}
	return false;
}


C_IMAP_Server_SelectAll_Rsp::C_IMAP_Server_SelectAll_Rsp()
{
	m_type = IMAP_TYPE::IMAP_SERVER_CONNECT;
}

C_IMAP_Server_SelectAll_Rsp::~C_IMAP_Server_SelectAll_Rsp()
{

}
IMAP_TYPE C_IMAP_Server_SelectAll_Rsp::GetType()
{
	return m_type;
}

std::string C_IMAP_Server_SelectAll_Rsp::ToString()
{
	return "* OK TinyEmail System IMap Server Ready(dennisthink[20200201])";
}

bool C_IMAP_Server_SelectAll_Rsp::FromString(const std::string strImap)
{
	if (strImap.find("* OK") != std::string::npos)
	{
		return true;
	}
	return false;
}

C_IMAP_Server_FetchEmail_Rsp::C_IMAP_Server_FetchEmail_Rsp()
{
	m_type = IMAP_TYPE::IMAP_SERVER_CONNECT;
}

C_IMAP_Server_FetchEmail_Rsp::~C_IMAP_Server_FetchEmail_Rsp()
{

}
IMAP_TYPE C_IMAP_Server_FetchEmail_Rsp::GetType()
{
	return m_type;
}

std::string C_IMAP_Server_FetchEmail_Rsp::ToString()
{
	return "* OK TinyEmail System IMap Server Ready(dennisthink[20200201])";
}

bool C_IMAP_Server_FetchEmail_Rsp::FromString(const std::string strImap)
{
	if (strImap.find("* OK") != std::string::npos)
	{
		return true;
	}
	return false;
}

