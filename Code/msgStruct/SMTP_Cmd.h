#ifndef _DENNIS_THINK_SMTP_CMD_H_
#define _DENNIS_THINK_SMTP_CMD_H_
#include <string>
enum class SMTP_CMD_TYPE
{
	S_C_220_RSP,//Server 220回复

};

//SMTP服务器的消息的返回码
enum class SMTP_CODE
{
	CODE_220,
	CODE_250,
	CODE_334,
	CODE_235,
};
class C_SMTP_CMD_BASE
{
public:
	C_SMTP_CMD_BASE();
	virtual ~C_SMTP_CMD_BASE();
	virtual SMTP_CMD_TYPE GetCmdType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strSmtp);
};

class C_SMTP_Server_On_Connect_Rsp final:public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Server_On_Connect_Rsp();
	virtual ~C_SMTP_Server_On_Connect_Rsp();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_HELO_CmdReq final:public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_HELO_CmdReq();
	virtual ~C_SMTP_Client_HELO_CmdReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Server_250_Rsp :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Server_250_Rsp();
	virtual ~C_SMTP_Server_250_Rsp();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_AuthLoginReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_AuthLoginReq();
	virtual ~C_SMTP_Client_AuthLoginReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Server_UserNameReq:public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Server_UserNameReq();
	virtual ~C_SMTP_Server_UserNameReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Server_PassWordReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Server_PassWordReq();
	virtual ~C_SMTP_Server_PassWordReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_PassWordRsp :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_PassWordRsp();
	virtual ~C_SMTP_Client_PassWordRsp();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_UserNameRsp :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_UserNameRsp();
	virtual ~C_SMTP_Client_UserNameRsp();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Server_AuthSuccessRsp :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Server_AuthSuccessRsp();
	virtual ~C_SMTP_Server_AuthSuccessRsp();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_MailFromReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_MailFromReq();
	virtual ~C_SMTP_Client_MailFromReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_RecvToReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_RecvToReq();
	virtual ~C_SMTP_Client_RecvToReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_DataBeginReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_DataBeginReq();
	virtual ~C_SMTP_Client_DataBeginReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_DataBodyReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_DataBodyReq();
	virtual ~C_SMTP_Client_DataBodyReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_DataEndReq :public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_DataEndReq();
	virtual ~C_SMTP_Client_DataEndReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

class C_SMTP_Client_QuitReq:public C_SMTP_CMD_BASE
{
public:
	C_SMTP_Client_QuitReq();
	virtual ~C_SMTP_Client_QuitReq();
	virtual SMTP_CMD_TYPE GetCmdType() override;
	virtual std::string ToString() override;
	virtual bool FromString(const std::string strSmtp) override;
};

#endif