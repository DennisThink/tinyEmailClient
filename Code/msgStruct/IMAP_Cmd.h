#ifndef _DENNIS_THINK_IMAP_CMD_H_
#define _DENNIS_THINK_IMAP_CMD_H_
#include <string>
enum class IMAP_TYPE
{
	IMAP_UNKNOWN,
	IMAP_SERVER_CONNECT,
};

enum class IMAP_STEP
{
	ON_SERVER_CONNECT_STEP,

};

class C_IMAP_BASE
{
public:
	C_IMAP_BASE();
	virtual ~C_IMAP_BASE();
	virtual IMAP_TYPE GetType();
	virtual std::string ToString();
	virtual bool FromString(const std::string strImap);
protected:
	IMAP_TYPE m_type;
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

#endif