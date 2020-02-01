#include "CommonMsg.h"



E_MsgType TransBaseMsg_t::GetType() const 
{
    Header* head = reinterpret_cast<Header*>(m_data);
    return static_cast<E_MsgType>(head->m_type);
}

std::size_t TransBaseMsg_t::GetSize() const
{
    Header* head = reinterpret_cast<Header*>(m_data);
    return head->m_length;
}

const char * TransBaseMsg_t::GetData() const 
{
    return m_data;
}

TransBaseMsg_t::TransBaseMsg_t(const E_MsgType& type, const std::string& strMsg)
{
    std::size_t strLen = strMsg.length();
    Header head;
    head.m_type = static_cast<uint32_t>(type);
    head.m_length = static_cast<uint32_t>(strLen + sizeof(head));
    m_data = new char[head.m_length];
    memset(m_data, 0, head.m_length);
    memcpy(m_data, &head, sizeof(head));
    memcpy(m_data + sizeof(head), strMsg.c_str(), strLen);
    m_selfData = true;
}

TransBaseMsg_t::TransBaseMsg_t(const char * data)
{
    m_data = const_cast<char*>(data);
    m_selfData = false;
}

TransBaseMsg_t::~TransBaseMsg_t()
{
    if(m_selfData)
    {
        if(nullptr != m_data)
        {
            delete m_data;
            m_data = nullptr;
        }
    }
}


std::string IpPortCfg::to_string()
{
    return m_strServerIp+":"+std::to_string(m_nPort);
}

bool IpPortCfg::Valid()
{
    if(m_strServerIp.empty())
    {
        return false;
    }		
    if(m_nPort<1024)
    {
        return false;
    }
    return true;
}



/**
 * @brief 获取消息的字符串内容
 * 
 * @return std::string 
 */
std::string TransBaseMsg_t::to_string() const
{ 
    Header* head = reinterpret_cast<Header*>(m_data);
    if (head->m_length <= 0)
    {
        return "";
    }
    else
    {
        return std::string((const char*)(m_data + sizeof(Header)), GetSize() - sizeof(Header));
    }
}



KeepAliveReqMsg::KeepAliveReqMsg()
{
    m_type = E_MsgType::KeepAliveReq_Type;
    m_strClientId= "";
}

KeepAliveReqMsg::KeepAliveReqMsg(const std::string& clientId)
{
    m_type = E_MsgType::KeepAliveReq_Type;
    m_strClientId=clientId;
}

std::string KeepAliveReqMsg::ToString() const
{
    using namespace json11;
    json11::Json clientObj = json11::Json::object(
    {
        {"ClientID", m_strClientId}
    });
    return clientObj.dump();
}

bool KeepAliveReqMsg::FromString(const std::string &strJson)
{
    std::string err;
    using namespace json11;
    json11::Json json = json11::Json::parse(strJson, err);
    if (!err.empty())
    {
        return false;
    }

    if (json["ClientID"].is_string())
    {
        m_strClientId = json["ClientID"].string_value();
    }
    else
    {
        return false;
    }
    if (m_strClientId.empty())
    {
        return false;
    }
    return true;
}


KeepAliveRspMsg::KeepAliveRspMsg()
{
    m_type = E_MsgType::KeepAliveRsp_Type;
    m_strClientId="";
}

KeepAliveRspMsg::KeepAliveRspMsg(const std::string& clientId)
{
    m_type = E_MsgType::KeepAliveRsp_Type;
    m_strClientId=clientId;
}


std::string KeepAliveRspMsg::ToString() const
{
    using namespace json11;
    json11::Json clientObj = json11::Json::object(
    {
        {"ClientID", m_strClientId}
    });
    return clientObj.dump();
}

bool KeepAliveRspMsg::FromString(const std::string &strJson)
{
    std::string err;
    using namespace json11;
    json11::Json json = json11::Json::parse(strJson, err);
    if (!err.empty())
    {
        return false;
    }

    if (json["ClientID"].is_string())
    {
        m_strClientId = json["ClientID"].string_value();
    }
    else
    {
        return false;
    }
    if (m_strClientId.empty())
    {
        return false;
    }
    return true;
}




UserLoginReqMsg::UserLoginReqMsg()
{
    m_type = E_MsgType::UserLoginReq_Type;
    m_strUserName.clear();
    m_strPassword.clear();
    m_eOsType = CLIENT_OS_TYPE::OS_TYPE_UNKNOWN;
    m_eOnlineType = CLIENT_ONLINE_TYPE::C_ONLINE_TYPE_OFFLINE;
    m_eNetType = CLIENT_NET_TYPE::C_NET_TYPE_UNKNOWN;
}

std::string UserLoginReqMsg::ToString() const
{
    using namespace json11;
    json11::Json clientObj = json11::Json::object(
    {
        {"UserName", m_strUserName},
        {"Password", m_strPassword},
        {"MsgId", m_strMsgId},
        {"OsType", static_cast<int>(m_eOsType)},
        {"NetType", static_cast<int>(m_eNetType)},
        {"OnlineType", static_cast<int>(m_eOnlineType)},
    });

    return clientObj.dump();
}

bool UserLoginReqMsg::FromString(const std::string &strJson)
{
    std::string err;
    using namespace json11;
    json11::Json json = json11::Json::parse(strJson, err);
    if (!err.empty())
    {
        return false;
    }

    if (json["UserName"].is_string())
    {
        m_strUserName = json["UserName"].string_value();
    }
    else
    {
        return false;
    }

    if (json["Password"].is_string())
    {
        m_strPassword = json["Password"].string_value();
    }
    else
    {
        return false;
    }

    if (json["MsgId"].is_string())
    {
        m_strMsgId = json["MsgId"].string_value();
    }
    else
    {
        return false;
    }

    if (json["OsType"].is_number())
    {
        m_eOsType = static_cast<CLIENT_OS_TYPE>(json["OsType"].int_value());
    }
    else
    {
        return false;
    }

    if (json["NetType"].is_number())
    {
        m_eNetType = static_cast<CLIENT_NET_TYPE>(json["NetType"].int_value());
    }
    else
    {
        return false;
    }

    if (json["OnlineType"].is_number())
    {
        m_eOnlineType = static_cast<CLIENT_ONLINE_TYPE>(json["OnlineType"].int_value());
    }
    else
    {
        return false;
    }

    return true;
}

bool UserLoginReqMsg::Valid() const
{
    if (m_strUserName.empty())
    {
        return false;
    }

    if (m_strPassword.empty())
    {
        return false;
    }

    if (m_strMsgId.empty())
    {
        return false;
    }

    return true;
}


UserLoginRspMsg::UserLoginRspMsg()
{
    m_eErrCode = ERROR_CODE_TYPE::E_CODE_LOGIN_FAILED;
    m_type = E_MsgType::UserLoginRsp_Type;
}

std::string UserLoginRspMsg::ToString() const
{
    using namespace json11;

    json11::Json clientObj = json11::Json::object(
    {
        {"UserId", m_strUserId},
        {"UserName", m_strUserName},
        {"code", static_cast<int>(m_eErrCode)},
        {"message", m_strErrMsg},
        {"MsgId", m_strMsgId},
    });

    return clientObj.dump();
}

bool UserLoginRspMsg::FromString(const std::string &strJson)
{
    std::string err;
    using namespace json11;
    auto json = Json::parse(strJson, err);
    if (!err.empty())
    {
        return false;
    }

    if (json["UserId"].is_string())
    {
        m_strUserId = json["UserId"].string_value();
    }
    else
    {
        return false;
    }

    if (json["UserName"].is_string())
    {
        m_strUserName = json["UserName"].string_value();
    }
    else
    {
        return false;
    }


    if (json["code"].is_number())
    {
        m_eErrCode = static_cast<ERROR_CODE_TYPE>(json["code"].int_value());
    }
    else
    {
        return false;
    }

    if (json["message"].is_string())
    {
        m_strErrMsg = json["message"].string_value();
    }
    else
    {
        return false;
    }

    if (json["MsgId"].is_string())
    {
        m_strMsgId = json["MsgId"].string_value();
    }
    else
    {
        return false;
    }

    

    return true;
}

bool UserLoginRspMsg::Valid() const
{
    if (m_strUserId.empty())
    {
        return false;
    }

    if (m_strUserName.empty())
    {
        return false;
    }
    return true;
}



SendEmailReq::SendEmailReq()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string SendEmailReq::ToString() const
{
	using namespace json11;
	json11::Json clientObj = json11::Json::object(
		{
			{"MsgId", m_strMsgId},
			{"UserName", m_strUserName},
			{"RecvName", m_strRecvName},
			{"Subject", m_strSubject},
			{"Context", m_strEmailContext},
		});

	return clientObj.dump();
}

bool SendEmailReq::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}

	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}
	if (json["UserName"].is_string())
	{
		m_strUserName = json["UserName"].string_value();
	}
	else
	{
		return false;
	}

	if (json["RecvName"].is_string())
	{
		m_strRecvName = json["RecvName"].string_value();
	}
	else
	{
		return false;
	}

	if (json["Subject"].is_string())
	{
		m_strSubject = json["Subject"].string_value();
	}
	else
	{
		return false;
	}

	if (json["Context"].is_string())
	{
		m_strEmailContext = json["Context"].string_value();
	}
	else
	{
		return false;
	}

	return true;
}

bool SendEmailReq::Valid() const
{
	if (m_strUserName.empty())
	{
		return false;
	}
	return true;
}


SendEmailRsp::SendEmailRsp()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string SendEmailRsp::ToString() const
{
	using namespace json11;

	json11::Json clientObj = json11::Json::object(
		{
			{"MsgId", m_strMsgId},
			{"TaskId",m_strTaskId},
		});

	return clientObj.dump();
}

bool SendEmailRsp::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}


	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["TaskId"].is_string())
	{
		m_strTaskId = json["TaskId"].string_value();
	}
	else
	{
		return false;
	}


	return true;
}

bool SendEmailRsp::Valid() const {
	return true;
}
QueryTaskReq::QueryTaskReq()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string QueryTaskReq::ToString() const
{
	using namespace json11;

	json11::Json clientObj = json11::Json::object(
		{
			{"MsgId", m_strMsgId},
			{"TaskId",m_strTaskId},
		});

	return clientObj.dump();
}

bool QueryTaskReq::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}


	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["TaskId"].is_string())
	{
		m_strTaskId = json["TaskId"].string_value();
	}
	else
	{
		return false;
	}


	return true;
}


bool QueryTaskReq::Valid() const
{
	return true;
}


QueryTaskRsp::QueryTaskRsp()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string QueryTaskRsp::ToString() const
{
	using namespace json11;
	json11::Json clientObj = json11::Json::object(
		{
			{"MsgId", m_strMsgId},
			{"TaskId",m_strTaskId},
			{"Code",static_cast<int>(m_eErrCode)},
			{"Msg",m_strErrMsg},
		});

	return clientObj.dump();
}

bool QueryTaskRsp::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}


	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["TaskId"].is_string())
	{
		m_strTaskId = json["TaskId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["Code"].is_number())
	{
		m_eErrCode = static_cast<ERROR_CODE_TYPE>(json["Code"].int_value());
	}
	else
	{
		return false;
	}

	if (json["Msg"].is_string())
	{
		m_strErrMsg = json["Msg"].string_value();
	}
	else
	{
		return false;
	}


	return true;
}


bool QueryTaskRsp::Valid() const
{
	return true;
}



GetEmailReq::GetEmailReq()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string GetEmailReq::ToString() const
{
	using namespace json11;
	json11::Json clientObj = json11::Json::object(
		{
			{"MsgId", m_strMsgId},
			{"UserName",m_strUserEmail},
		});

	return clientObj.dump();
}

bool GetEmailReq::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}


	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["UserName"].is_string())
	{
		m_strUserEmail = json["UserName"].string_value();
	}
	else
	{
		return false;
	}


	return true;
}


bool GetEmailReq::Valid() const
{
	return true;
}

GetEmailRsp::GetEmailRsp()
{
	m_type = E_MsgType::UserLoginRsp_Type;
}

std::string GetEmailRsp::ToString() const
{
	using namespace json11;
	json11::Json clientObj = json11::Json::object(
		{
			{"Code",static_cast<int>(m_eErrCode)},
			{"Msg",m_strErrMsg},
			{"MsgId", m_strMsgId},
			{"UserName",m_strUserName},
			{"RecvName",m_strRecvName},
			{"Subject",m_strSubject},
			{"Context",m_strEmailContext},
		});

	return clientObj.dump();
}

bool GetEmailRsp::FromString(const std::string &strJson)
{
	std::string err;
	using namespace json11;
	auto json = Json::parse(strJson, err);
	if (!err.empty())
	{
		return false;
	}

	if (json["Code"].is_number())
	{
		m_eErrCode = static_cast<ERROR_CODE_TYPE>(json["Code"].int_value());
	}
	else
	{
		return false;
	}

	if (json["Msg"].is_string())
	{
		m_strErrMsg = json["Msg"].string_value();
	}
	else
	{
		return false;
	}

	if (json["MsgId"].is_string())
	{
		m_strMsgId = json["MsgId"].string_value();
	}
	else
	{
		return false;
	}

	if (json["UserName"].is_string())
	{
		m_strUserName = json["UserName"].string_value();
	}
	else
	{
		return false;
	}

	if (json["RecvName"].is_string())
	{
		m_strRecvName = json["RecvName"].string_value();
	}
	else
	{
		return false;
	}

	if (json["Subject"].is_string())
	{
		m_strSubject = json["Subject"].string_value();
	}
	else
	{
		return false;
	}

	if (json["Context"].is_string())
	{
		m_strEmailContext = json["Context"].string_value();
	}
	else
	{
		return false;
	}

	return true;
}


bool GetEmailRsp::Valid() const
{
	return true;
}