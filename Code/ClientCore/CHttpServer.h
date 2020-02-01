/**
 * @file CHttpServer.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 用来处理HTTP请求的类
 * @version 0.1
 * @date 2019-08-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _DENNIS_THINK_C_HTTP_SERVER_H_
#define _DENNIS_THINK_C_HTTP_SERVER_H_
#include "asio_common.h"
#include <memory>
#include <map>
#include "server_http.hpp"
#include "CClientSess.h"
#include "SnowFlake.h"
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HTTP_RSP_MAP_PAIR =std::pair<std::string, std::shared_ptr < HttpServer::Response>>;
using HTTP_RSP_MAP = std::map<std::string, std::shared_ptr<HttpServer::Response>>;
namespace ClientCore {
	class CMediumServer;
	class CHttpServer : public std::enable_shared_from_this<CHttpServer>
	{
	public:
		explicit CHttpServer(asio::io_service& ioService,CMediumServer* pServer) :m_httpServer(ioService),m_pServer(pServer),m_msgIdUtil(2,2) {

		}

		void Start()
		{
			Init();
			m_httpServer.start();
		}

		void Stop()
		{
			m_httpServer.stop();
		}

		

		void On_UserLoginRsp(const UserLoginRspMsg&  msg);
		void On_SendEmailRsp(const SendEmailRsp& msg);
		void On_QueryTaskRsp(const QueryTaskRsp& msg);
		//void On_UserLogoutRsp(const )
		void On_GetEmailRsp(const GetEmailRsp& msg);
		static std::shared_ptr<spdlog::logger> ms_loger;

		std::string GenerateMsgId() {
			return std::to_string(m_msgIdUtil.nextId());
		}

		UserLoginReqMsg GetUserLoginReq(const std::string strUserName) const; 
	private:
		void Get_Version(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);


		void Post_UserLogin(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);

		void Post_SendEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);

		void Get_TaskState(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);

		void Get_UserEmail(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
		void Init();

		std::string GetHttpParamUserId(std::shared_ptr<HttpServer::Request> request);
	

		SnowFlake m_msgIdUtil;
		HttpServer m_httpServer;
		CMediumServer* m_pServer;
		std::map<CClientSess_SHARED_PTR, std::shared_ptr<HttpServer::Response>> m_clientSessResponseMap;
		HTTP_RSP_MAP m_httpRspMap;


	};
}
#endif