/**
 * @file CommonMsg.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 定义交互消息的头文件，包括了序列化和反序列化
 * @version 0.1
 * @date 2019-07-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _COMMON_MSG_H_
#define _COMMON_MSG_H_
#include "json11.hpp"
#include "CommonDef.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief 消息体的头部
 * 
 */
struct Header
{
	//消息类型
	int32_t   m_type;//消息类型
	//消息长度
	int32_t    m_length;//消息长度
};



/**
 * @brief 用来传输消息的类型，将消息先转化为字符串，然后放入这个类型中，在实际的代码中使用std::shared_ptr来保存
 * 
 */
struct TransBaseMsg_t
{
public:
	/**
	 * @brief 获取消息类型
	 * 
	 * @return E_MsgType 
	 */
	E_MsgType GetType() const;

	/**
	 * @brief 获取消息体的长度
	 * 
	 * @return std::size_t 
	 */
	std::size_t GetSize() const;

	/**
	 * @brief 获取消息的字符串内容
	 * 
	 * @return std::string 
	 */
	std::string to_string() const;

	/**
	 * @brief 获取消息的实际数据
	 * 
	 * @return const char* 
	 */
	const char * GetData() const;

	/**
	 * @brief 使用消息类型和字符串构造传输的消息,发送消息的时候使用
	 *
	 * @param type 消息类型
	 * @param strMsg  消息字符串
	 */
	explicit TransBaseMsg_t(const E_MsgType& type, const std::string& strMsg);
	/**
	 * @brief 从内存直接构造消息，接收消息的时候使用
	 * 
	 * @param data 消息接收端的内存
	 */
	explicit TransBaseMsg_t(const char * data);

	virtual ~TransBaseMsg_t();
protected:
	//数据块内容
	char *   m_data;
	//是否自己保存了数据
	bool m_selfData = false;
};

using TransBaseMsg_S_PTR=std::shared_ptr<TransBaseMsg_t>;
/**
 * @brief Ip端口配置类
 * 
 */
struct IpPortCfg
{
	std::string m_strServerIp;
	int 		m_nPort;
	/**
	 * @brief 获取配置的字符串表示，类似于 127.0.0.1:80
	 * 
	 * @return std::string 
	 */
	std::string to_string();

	/**
	 * @brief 检查配置是否有效
	 * 
	 * @return true 配置有效
	 * @return false 配置无效
	 */
	bool Valid();
};

struct MySqlCfg
{
public:
	std::string m_strDbIp;//数据库IP地址
	int         m_nDbPort;//数据库端口
	std::string m_strUserName;//数据库用户名
	std::string m_strPassword;//数据库的密码
	std::string m_strDbName;//数据库名称
};
/**
 * @brief 基础消息类型，所有的消息从该类型继承
 * 
 */
struct BaseMsg
{
protected:
	E_MsgType m_type;
public:
	/**
	 * @brief 获取消息类型
	 * 
	 * @return E_MsgType 
	 */
	E_MsgType GetMsgType() const 
	{
		return m_type;
	}

	explicit BaseMsg()
	{
		m_type=E_MsgType::Base_Type;
	}
	
	/**
	 * @brief 消息序列化,需要子类继承
	 * 
	 * @return std::string 序列化以后的字符串
	 */
	virtual std::string ToString() const
	{
		return "";
	}

	/**
	 * @brief 消息反序列化，需要子类继承
	 * 
	 * @param strJson 待反序列化的子串
	 * @return true 反序列化成功
	 * @return false 反序列化失败
	 */
    virtual bool FromString(const std::string& strJson)
	{
		if(strJson.empty())
		{
			return false;
		}
		return true;
	}

	virtual bool Valid() const {
		return false;
	}

	virtual std::string ToPrintString() const {
		return ToString();
	}
};


/**
 * @brief 心跳请求消息
 * 
 */
struct KeepAliveReqMsg final:public BaseMsg
{
public:
	std::string m_strClientId;//客户端标识，用来标识是哪个客户端的发送的心跳请求
public:
	explicit KeepAliveReqMsg();

	explicit KeepAliveReqMsg(const std::string& clientId);

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};

/**
 * @brief 心跳回复消息
 * 
 */
class KeepAliveRspMsg final:public BaseMsg
{
public:
	std::string m_strClientId;//心跳请求中携带的客户端标识
public:
	explicit KeepAliveRspMsg();

	explicit KeepAliveRspMsg(const std::string& clientId);

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;
};


/**
 * @brief 登录请求消息
 *
 */
class UserLoginReqMsg final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserName;//用户名
	std::string m_strPassword;//密码
	CLIENT_OS_TYPE m_eOsType;//操作系统类型
	CLIENT_NET_TYPE m_eNetType;//网络类型
	CLIENT_ONLINE_TYPE m_eOnlineType;//在线类型
public:
	explicit UserLoginReqMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};


/**
 * @brief 用户登录回复消息
 *
 */
class UserLoginRspMsg final :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg; //错误信息
	std::string m_strMsgId;//消息ID
	std::string m_strUserId;//用户ID
	std::string m_strUserName; //用户名
	
public:
	explicit UserLoginRspMsg();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class SendEmailReq final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserName;//用户名
	std::string m_strRecvName;//密码
	std::string m_strSubject;//邮件主题
	std::string m_strEmailContext;//邮件内容
public:
	explicit SendEmailReq();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class SendEmailRsp final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strTaskId;//任务ID
public:
	explicit SendEmailRsp();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class QueryTaskReq final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strTaskId;//任务ID
public:
	explicit QueryTaskReq();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class QueryTaskRsp final :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg; //错误信息
	std::string m_strMsgId;//消息ID
	std::string m_strTaskId;//用户ID
public:
	explicit QueryTaskRsp();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class GetEmailReq final :public BaseMsg
{
public:
	std::string m_strMsgId;//消息ID
	std::string m_strUserEmail;//用户ID
public:
	explicit GetEmailReq();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};

class GetEmailRsp final :public BaseMsg
{
public:
	ERROR_CODE_TYPE m_eErrCode; //错误代码
	std::string m_strErrMsg; //错误信息
	std::string m_strMsgId;//消息ID
	std::string m_strUserName;//用户名
	std::string m_strRecvName;//密码
	std::string m_strSubject;//邮件主题
	std::string m_strEmailContext;//邮件内容
public:
	explicit GetEmailRsp();

	virtual std::string ToString() const override;

	virtual bool FromString(const std::string& strJson) override;

	virtual bool Valid() const override;
};
/**
 * @brief 服务器配置
 * 
 */
class CServerConfig
{
public:
	std::vector<IpPortCfg> m_clientCfgVec;
	IpPortCfg              m_serverCfg;
	explicit CServerConfig()
	{
		m_serverCfg.m_strServerIp = "127.0.0.1";
		m_serverCfg.m_nPort = 9000;

		m_clientCfgVec.push_back({"127.0.0.1",8000});
	}
};

#endif
