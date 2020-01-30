/**
 * @file CMediumServer.cpp
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 
 * @version 0.1
 * @date 2019-09-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CMediumServer.h"
#include "json11.hpp"
#include "DaemonSvcApp.h"
#include "Msg.h"
#include "UiMsg.h"
#include "IUProtocolData.h"
namespace ClientCore
{
std::shared_ptr<spdlog::logger> CMediumServer::ms_loger;

/**
 * @brief 加载配置文件
 * 
 * @param cfg 配置文件的json
 * @param ec 发生的异常
 */
void CMediumServer::loadConfig(const json11::Json &cfg, std::error_code& ec) 
{
	auto serverCfg = cfg["server"];
	LOG_INFO(ms_loger,"loadConfig");
    ec.clear();
    m_serverCfg.m_strServerIp=serverCfg["ip"].string_value();
    m_serverCfg.m_nPort=(uint16_t)serverCfg["port"].int_value();
    LOG_INFO(ms_loger,"ServerIp: {}",m_serverCfg.to_string());
    if(!m_serverCfg.Valid())
	{
		LOG_ERR(ms_loger,"Config Error {}",m_serverCfg.to_string());
        return;
    }

	{
		auto clientsCfg = cfg["clients"];
		if (!clientsCfg.is_array())
		{
			LOG_ERR(ms_loger, "Clients Config Error {}", cfg.string_value());
			return;
		}
		for (auto item : clientsCfg.array_items())
		{
			IpPortCfg clientCfg;
			clientCfg.m_strServerIp = item["ip"].string_value();
			clientCfg.m_nPort = item["port"].int_value();
			LOG_INFO(ms_loger, "Client Config: {}", clientCfg.to_string());
			m_clientCfgVec.push_back(clientCfg);
		}
	}

	{
		{
			auto clientsCfg = cfg["clientsBin"];
			if (!clientsCfg.is_array())
			{
				LOG_ERR(ms_loger, "Clients Config Error {}", cfg.string_value());
				return;
			}
			for (auto item : clientsCfg.array_items())
			{
				IpPortCfg clientCfg;
				clientCfg.m_strServerIp = item["ip"].string_value();
				clientCfg.m_nPort = item["port"].int_value();
				LOG_INFO(ms_loger, "Client Config: {}", clientCfg.to_string());
				m_clientBinCfgVec.push_back(clientCfg);
			}
		}
	}
}


/**
 * @brief 启动服务
 * 
 * @param callback 
 */
void CMediumServer::start(const std::function<void(const std::error_code &)> &callback)
{
	if (!m_serverCfg.Valid())
	{
		LOG_ERR(ms_loger, "ServerConfig Is Error {}", m_serverCfg.to_string());
		return;
	}
	LOG_INFO(ms_loger, "Server Start Service");
	std::error_code ec;
	asio::ip::tcp::endpoint endpoint;
	if (m_serverCfg.m_strServerIp.length() > 0)
	{
		endpoint = asio::ip::tcp::endpoint(
			asio::ip::address::from_string(m_serverCfg.m_strServerIp),
			m_serverCfg.m_nPort);
	}
	else
	{
		endpoint =
			asio::ip::tcp::endpoint(asio::ip::tcp::v4(), m_serverCfg.m_nPort);
	}
	LOG_WARN(ms_loger, "Before Open [ {} {} ]",__FILENAME__,__LINE__);
	m_acceptor.open(endpoint.protocol());
	LOG_WARN(ms_loger, "Before Set Option [ {} {} ]", __FILENAME__, __LINE__);
	m_acceptor.set_option(asio::socket_base::reuse_address(true));
	LOG_WARN(ms_loger, "Before Bind [ {} {} ]", __FILENAME__, __LINE__);
	m_acceptor.bind(endpoint, ec);
	LOG_WARN(ms_loger, "Before Listen [ {} {} ]", __FILENAME__, __LINE__);
	if (!ec)
	{
		LOG_WARN(ms_loger, "Bind To {} Succeed [{} {}]", m_serverCfg.to_string(),__FILENAME__,__LINE__);
		m_acceptor.listen(asio::socket_base::max_connections, ec);
		if (!ec)
		{
			LOG_WARN(ms_loger, "Listen To {} Succeed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
		}
		else
		{
			LOG_WARN(ms_loger, "Listen To {} Failed, Reason:{} {} [{} {}]",
				m_serverCfg.to_string(), ec.value(), ec.message(), __FILENAME__, __LINE__);
		}
		SetTimer(5);
		do_accept();
		m_httpServer->Start();

		m_freeClientSess = std::make_shared<CClientSess>(m_ioService,
			m_clientCfgVec[0].m_strServerIp,
			m_clientCfgVec[0].m_nPort, this);

		m_freeClientSess->StartConnect();
		/*{
			for (auto item : m_clientCfgVec)
			{
				if (item.Valid())
				{
					auto pQueue = std::make_shared<CClientSessManager>(item);
					m_queueVec.push_back(pQueue);
					std::error_code ec;
					pQueue->Start(this, m_ioService, ec);
					LOG_INFO(ms_loger, "ConnectTo: {}", item.to_string());
				}
			}
		}*/
	}
	else
	{
		LOG_WARN(ms_loger, "Bind To {} Failed [{} {}]", m_serverCfg.to_string(), __FILENAME__, __LINE__);
		callback(ec);
#ifndef WIN32
		exit(BIND_FAILED_EXIT);
#endif
	}
}
/**
 * @brief 检查所有的socket连接
 * 
 */
void CMediumServer::CheckAllConnect()
{
	for (auto& item : m_userClientSessMap)
	{
		item.second->StartConnect();
	}
}

/**
 * @brief 接受来自客户端的连接
 * 
 */
void CMediumServer::do_accept() 
{
		//LOG_INFO(ms_loger,"CMediumServer do_accept [{} {}]", __FILENAME__, __LINE__);
  //      m_acceptor.async_accept(m_socket, [this](std::error_code ec) {
  //          if (!ec)
		//	{
		//	   LOG_INFO(ms_loger,"Server accept Successed [{} {}]",__FILENAME__, __LINE__);
  //             

		//	   if (!m_clientCfgVec.empty() && !m_clientBinCfgVec.empty())
		//	   {
		//		   //
		//		   auto clientSess = std::make_shared<CClientSess>(m_ioService, 
		//			                                               m_clientCfgVec[0].m_strServerIp, 
		//			                                               m_clientCfgVec[0].m_nPort, this);

		//		   clientSess->StartConnect();


		//		   //
		//		   auto serverSess = std::make_shared<CServerSess>(std::move(m_socket), this);
		//		   serverSess->Start();


		//		   //
		//		   m_ForwardSessMap.insert(std::pair<CServerSess_SHARED_PTR, CClientSess_SHARED_PTR>(serverSess, clientSess));
		//		   m_BackSessMap.insert(std::pair<CClientSess_SHARED_PTR,CServerSess_SHARED_PTR>(clientSess, serverSess));

		//	   }
		//	}
  //          do_accept();
  //      });
}

/**
 * @brief 根据用户ID或用户名获取客户端会话连接
 * 
 * @param strUserName 用户名或者用户ID
 * @return CClientSess_SHARED_PTR 
 */
CClientSess_SHARED_PTR CMediumServer::GetClientSess(const std::string strUserName) {
	auto item = m_userClientSessMap.find(strUserName);
	if (item != m_userClientSessMap.end())
	{
		return item->second;
	}
	else
	{
		auto pReturn = m_freeClientSess;
		m_freeClientSess = std::make_shared<CClientSess>(m_ioService,
			m_clientCfgVec[0].m_strServerIp,
			m_clientCfgVec[0].m_nPort, this);

		m_freeClientSess->StartConnect();
		m_userClientSessMap.insert(std::pair<std::string, CClientSess_SHARED_PTR>(strUserName, pReturn));
		return pReturn;
	}	
}

CClientSess_SHARED_PTR CMediumServer::GetClientSess(const IpPortCfg& smtpCfg)
{
	auto pSess = std::make_shared<CClientSess>(m_ioService,
		smtpCfg.m_strServerIp,
		smtpCfg.m_nPort, this);
	return pSess;
}

/**
 * @brief 响应定时器的任务，一些需要定时处理的任务，可以写成一个函数，在此函数中调用
 * 
 */
void CMediumServer::OnTimer()
{
	CheckAllConnect();
}

/**
 * @brief 设置定时器，单位秒
 * 
 * @param nSeconds 定时的秒数
 */
void CMediumServer::SetTimer(int nSeconds)
{
	if(m_timer)
	{
		m_timer->expires_from_now(std::chrono::seconds(nSeconds));
		auto self = shared_from_this();
		m_timer->async_wait([this,nSeconds,self](const std::error_code& ec){
			if(!ec)
			{
				LOG_INFO(this->ms_loger,"On Timer at MediumServer [{} {}]",__FILENAME__, __LINE__);
				this->OnTimer();
				this->SetTimer(nSeconds);
			}
			else
			{
				LOG_WARN(this->ms_loger,"On Timer at MediumServer {} [{} {}]",ec.message(),__FILENAME__, __LINE__);
			}
		});
	}
}

/**
 * @brief 获取Listen的服务器的IP和端口
 * 
 * @return std::string 
 */
std::string CMediumServer::getServerIpPort()
{
	return m_serverCfg.to_string();
}

/**
 * @brief 处理从ClientSess中，回传的消息
 * 
 * @param msg 消息
 */
void CMediumServer::SendBack(const std::shared_ptr<CClientSess>& pClientSess,const TransBaseMsg_t& msg)
{
	auto pMsg = std::make_shared<TransBaseMsg_t>(msg.GetType(), msg.to_string());
	/*auto item = m_BackSessMap.find(pClientSess);
	
	if (item != m_BackSessMap.end())
	{
		item->second->SendMsg(pMsg);
	}
	else*/
	/*{
		if (msg.GetType() == MessageType::UserLoginRsp_Type)
		{
			UserLoginRspMsg rspMsg;
			rspMsg.FromString(msg.to_string());
			if (rspMsg.m_eErrCode == ERROR_CODE_TYPE::E_CODE_SUCCEED)
			{
				pClientSess->SetUserId(rspMsg.m_strUserId);
				pClientSess->SetUserName(rspMsg.m_strUserName);
				m_userStateMap.erase(rspMsg.m_strUserId);
				m_userStateMap.insert({ rspMsg.m_strUserId,CLIENT_SESS_STATE::SESS_LOGIN_FINISHED });
			}
			if (!m_fileUtil.IsFolder(rspMsg.m_strUserName))
			{
				m_fileUtil.CreateFolder(rspMsg.m_strUserName);
			}
		}
		if (msg.GetType() == MessageType::UserLogoutRsp_Type)
		{
			UserLogoutRspMsg rspMsg;
			if (rspMsg.FromString(msg.to_string())) {
				if (rspMsg.m_eErrCode == ERROR_CODE_TYPE::E_CODE_SUCCEED) {
					m_userClientSessMap.erase(rspMsg.m_strUserName);
					m_userStateMap.erase(pClientSess->UserId());
					m_userStateMap.insert({ pClientSess->UserId(),CLIENT_SESS_STATE::SESS_UN_LOGIN });
				}
			}
		}
		if (msg.GetType() == MessageType::NetFailedReport_Type)
		{
			auto item = m_userStateMap.find(pClientSess->UserId());
			if (item != m_userStateMap.end())
			{
				if (item->second == CLIENT_SESS_STATE::SESS_LOGIN_FINISHED)
				{
					m_userStateMap.erase(pClientSess->UserId());
					m_userStateMap.insert({ pClientSess->UserId(),CLIENT_SESS_STATE::SESS_LOGIN_SEND });
				}
			}
			m_userClientSessMap.erase(pClientSess->UserName());
			
			auto pSess = GetClientSess(pClientSess->UserName());
			pSess->SetUserId(pClientSess->UserId());
			pSess->SetUserName(pClientSess->UserName());
		}
		if (msg.GetType() == MessageType::NetRecoverReport_Type)
		{
			auto loginReq = m_httpServer->GetUserLoginReq(pClientSess->UserName());
			auto item = m_userStateMap.find(pClientSess->UserId());
			if (item != m_userStateMap.end())
			{
				if (item->second == CLIENT_SESS_STATE::SESS_LOGIN_SEND)
				{
					auto pSendMsg = std::make_shared<TransBaseMsg_t>(loginReq.GetMsgType(), loginReq.ToString());
					pClientSess->SendMsg(pSendMsg);
				}
			}
		}
		OnHttpRsp(pMsg);
	}*/
}


void CMediumServer::HandleSendEmailReq(const SendEmailReq& reqMsg)
{
	SendEmailRsp rspMsg;
	rspMsg.m_strMsgId = reqMsg.m_strMsgId;
	auto item = m_userLoginMsgMap.find(reqMsg.m_strUserName);
	if (item != m_userLoginMsgMap.end())
	{
		IpPortCfg cfg = C_SMTP_Handler::GetSmtpIpServerAddr(reqMsg.m_strUserName);
		auto pSess = GetClientSess(cfg);
		auto pHandler = std::make_shared<C_SMTP_Handler>();

		m_clientSessHandlerMap.insert({ pSess,pHandler });
		rspMsg.m_strTaskId = m_httpServer->GenerateMsgId();
		m_TaskIdHandlerMap.insert({ rspMsg.m_strTaskId,pHandler });
		pSess->StartConnect();
	}
	else
	{
		rspMsg.m_strTaskId = "";
	}

	
	if (m_httpServer)
	{
		m_httpServer->On_SendEmailRsp(rspMsg);
	}
}

void CMediumServer::HandleUserLoginReq(const UserLoginReqMsg& reqMsg)
{
	m_userLoginMsgMap.erase(reqMsg.m_strUserName);
	m_userLoginMsgMap.insert({ reqMsg.m_strUserName,reqMsg });
	UserLoginRspMsg rspMsg;
	rspMsg.m_strMsgId = reqMsg.m_strMsgId;
	rspMsg.m_strUserName = reqMsg.m_strUserName;
	m_httpServer->On_UserLoginRsp(rspMsg);
}

void CMediumServer::HandleGetTaskReq(const QueryTaskReq& reqMsg)
{

}
void CMediumServer::SendBack(const std::shared_ptr<CClientSess>& pClientSess, const std::string msg)
{
	auto pSmtp = GetSmtpHandler(pClientSess);
	if (pSmtp)
	{
		pSmtp->HandleServerRsp(msg);
		auto pMsg = pSmtp->GetNextMsg();
		if (pMsg)
		{
			pClientSess->SendMsg(pMsg->ToString());
		}
	}
}
C_SMTP_Handler_PTR CMediumServer::GetSmtpHandler(const std::shared_ptr<CClientSess>& pClientSess)
{
	auto item = m_clientSessHandlerMap.find(pClientSess);
	if (item != m_clientSessHandlerMap.end())
	{
		return item->second;
	}
	else
	{
		return nullptr;
	}
}
/**
 * @brief 将TCP的回复消息变为HTTP消息
 * 
 * @param pMsg TCP的回复消息
 */
void CMediumServer::OnHttpRsp(std::shared_ptr<TransBaseMsg_t> pMsg)
{
}


/**
 * @brief 将消息转发到远端的服务器
 * 
 * @param pServerSess 连接客户端的会话
 * @param msg 消息
 */
void CMediumServer::SendFoward(const std::shared_ptr<CServerSess>& pServerSess,const TransBaseMsg_t& msg)
{
	//对于原始消息，原封不动的转发
	auto item = m_ForwardSessMap.find(pServerSess);
	if (item != m_ForwardSessMap.end())
	{
		auto pMsg = std::make_shared<TransBaseMsg_t>(msg.GetType(), msg.to_string());
		item->second->SendMsg(pMsg);
	}
}

}