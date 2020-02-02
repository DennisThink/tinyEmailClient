#ifndef _DENNIS_THINK_IMAP_CMD_H_
#define _DENNIS_THINK_IMAP_CMD_H_
#include <string>
#include "CommonMsg.h"
enum class IMAP_TYPE
{
	IMAP_UNKNOWN,
	IMAP_SERVER_CONNECT,
	IMAP_LOGIN_REQ,
	IMAP_LOGIN_RSP,
	IMAP_FETCH_REQ,
	IMAP_FETCH_RSP,
	IMAP_LOGOUT_REP,
	IMAP_LOGOUT_RSP,
	IMAP_NOOP_REQ,
	IMAP_NOOP_RSP,
};

enum class IMAP_STEP
{
	ON_SERVER_CONNECT_STEP,
	SEND_LOGIN_STEP,
	ON_SERVER_LOGIN_STEP,
	SEND_SELECT_ALL_STEP,
	ON_SERVER_SELECT_ALL_STEP,
	SEND_FETCH_EMAIL_STEP,
	ON_SERVER_FETCH_EMAIL_STEP,
	SEND_LOGOUT_STEP,
	ON_SERVER_LOGOUT_STEP,
};

class C_IMAP_BASE
{
public:
	C_IMAP_BASE();
	virtual ~C_IMAP_BASE();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
	std::string GetCmdId();
	bool IsOK() const;
protected:
	bool m_bIsOk;
	IMAP_TYPE m_type;
	std::string m_strCmdId;
};

class C_IMAP_Server_On_Connect:public C_IMAP_BASE
{
public:
	C_IMAP_Server_On_Connect();
	virtual ~C_IMAP_Server_On_Connect();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);

};

class C_IMAP_Client_Noop_Req : public C_IMAP_BASE
{
public:
	C_IMAP_Client_Noop_Req();
	virtual ~C_IMAP_Client_Noop_Req();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);

};

class C_IMAP_Server_Noop_Rsp:public C_IMAP_BASE
{
public:
	C_IMAP_Server_Noop_Rsp();
	virtual ~C_IMAP_Server_Noop_Rsp();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);

};

class C_IMAP_Client_Login_Req : public C_IMAP_BASE
{
public:
	C_IMAP_Client_Login_Req();
	virtual ~C_IMAP_Client_Login_Req();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
public:
	UserLoginReqMsg m_LoginReq;
};

class C_IMAP_Server_Login_Rsp :public C_IMAP_BASE
{
public:
	C_IMAP_Server_Login_Rsp();
	virtual ~C_IMAP_Server_Login_Rsp();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);

};

class C_IMAP_Client_Logout_Req : public C_IMAP_BASE
{
public:
	C_IMAP_Client_Logout_Req();
	virtual ~C_IMAP_Client_Logout_Req();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);

};

class C_IMAP_Server_Logout_Rsp :public C_IMAP_BASE
{
public:
	C_IMAP_Server_Logout_Rsp();
	virtual ~C_IMAP_Server_Logout_Rsp();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
};

class C_IMAP_Client_SelectAll_Req : public C_IMAP_BASE
{
public:
	C_IMAP_Client_SelectAll_Req();
	virtual ~C_IMAP_Client_SelectAll_Req();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
};

class C_IMAP_Server_SelectAll_Rsp :public C_IMAP_BASE
{
public:
	C_IMAP_Server_SelectAll_Rsp();
	virtual ~C_IMAP_Server_SelectAll_Rsp();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
};
class C_IMAP_Client_FetchEmail_Req : public C_IMAP_BASE
{
public:
	C_IMAP_Client_FetchEmail_Req();
	virtual ~C_IMAP_Client_FetchEmail_Req();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
};

class C_IMAP_Server_FetchEmail_Rsp :public C_IMAP_BASE
{
public:
	C_IMAP_Server_FetchEmail_Rsp();
	virtual ~C_IMAP_Server_FetchEmail_Rsp();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
};
#endif