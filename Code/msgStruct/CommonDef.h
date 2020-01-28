#ifndef _COMMON_DEF_H_
#define _COMMON_DEF_H_
#include <string.h>
#include <string>
/**
 * @brief 定义消息的类型，
 *        如果您需要定义新的消息，可以直接在后面添加
 *
 */
enum class E_MsgType :uint32_t
{
	Base_Type,
	//心跳请求消息
	KeepAliveReq_Type,
	//心跳回复消息
	KeepAliveRsp_Type,


	//登录请求
	UserLoginReq_Type,
	//登录回复
	UserLoginRsp_Type,

	//登出请求
	UserLogoutReq_Type,
	//登出回复
	UserLogoutRsp_Type,

	//注册请求
	UserRegisterReq_Type,
	//注册回复
	UserRegisterRsp_Type,

	//注销请求
UserUnRegisterReq_Type,

//注销回复
UserUnRegisterRsp_Type,

SendEmailReq_Type,
SendEmailRsp_Type,

QueryTaskReq_Type,
QueryTaskRsp_Type,


};

//客户端会话状态
enum class CLIENT_SESS_STATE
{
	SESS_UN_LOGIN,//用户未登陆
	SESS_LOGIN_SEND,//用户已经发起登陆请求
	SESS_LOGIN_FINISHED,//用户登录完成
	SESS_LOGOUT_SEND,//用户已经发起退出登录请求
	SESS_LOGOUT,//用户已经登出
	SESS_IDLE_STATE,//处于空闲状态
	SESS_RELATION_SEND_RECV, //关系消息收发状态
	SESS_RELATION_FINISH,
	SESS_WAIT_RECV_MSG_RSP,
	SESS_RECV_MSG_FINISHED,
	SESS_FRIEND_MSG_SEND_RECV_STATE,//好友信息收发状态
	SESS_FRIEND_FINISH,
	SESS_GROUP_MSG_SEND_RECV_STATE,//群组消息收发状态
	SESS_GROUP_FINISH,
};
//操作系统类型
enum class CLIENT_OS_TYPE {
	//未知类型
	OS_TYPE_UNKNOWN,
	
	//Windows
	OS_TYPE_WINDOWS,
	
	//Linux
	OS_TYPE_LINUX,

	//苹果电脑系统
	OS_TYPE_MAC,

	//安卓手机
	OS_TYPE_ANDROID,
	
	//Iphone手机
	OS_TYPE_IOS,
};

//网络类型
enum class CLIENT_NET_TYPE {
	C_NET_TYPE_UNKNOWN,
	C_NET_TYPE_WIFI,//WIFI网络
	C_NET_TYPE_3G,//3G网络
	C_NET_TYPE_4G,//4G网络
	C_NET_TYPE_5G,//5G网络
};

//在线类型
enum class CLIENT_ONLINE_TYPE {
	//未知
	C_ONLINE_TYPE_UNKNOWN,
	
	//在线
	C_ONLINE_TYPE_ONLINE,
	
	//离线
	C_ONLINE_TYPE_OFFLINE,
	
	//隐身
	C_ONLINE_TYPE_INVISIBLE,
};

enum class FILE_TRANS_TYPE {
	TCP_OFFLINE_MODE,//TCP服务器保存模式
	TCP_ONLINE_MODE,//TCP的服务器中继模式
	UDP_ONLINE_MEDIUM_MODE,//UDP的中继传递模式,UDP的P2P失败的时候使用
	UDP_ONLINE_P2P_MODE,//UDP的P2P模式
	UDP_OFFLINE_MODE,//UDP的服务器保存模式，
};
enum class FILE_TYPE {
	FILE_TYPE_FILE,//文件
	FILE_TYPE_IMAGE,//图片
};
//操作返回的错误代码
enum class ERROR_CODE_TYPE {
	E_CODE_SUCCEED = 0,//成功

	//通用错误
	E_CODE_CONNECT_FAILED,//网络已经断开

	//用户注册错误码
	E_CODE_USER_HAS_EXIST, //用户已存在
	//
	E_CODE_LOGIN_FAILED,//登录失败
	E_CODE_NO_SUCH_USER,//没有此用户
	E_CODE_USER_NAME_PASS_WORD_NOT_MATCH, //用户名密码不匹配
	E_CODE_VERIFY_CODE_NOT_MATCH,         //验证码不匹配
	E_CODE_USER_OFF_LINE,//用户不在线
	E_CODE_EMPTY_GROUP_NAME,//群组名称为空

	E_CODE_ADD_SELF_AS_FRIEND,//添加自己为好友
	E_CODE_EMPTY_USER_ID,//用户ID为空
	E_CODE_EMPTY_GROUP_ID,//群组ID为空
	E_CODE_EMPTY_USER_NAME,//用户名为空
	E_CODE_EMPTY_PASS_WORD,//用户密码为空
	E_CODE_NOT_GROUP_MEMBER,//不是群组成员
	E_CODE_NOT_FRIEND_RELATION,//不是好友关系
	E_CODE_ERROR_PARAM,//参数错误
	E_CODE_BAD_REQUEST_FORMAT,//请求格式错误
	E_CODE_USER_NOT_LOGIN,//用户未登录
	E_CODE_NO_SUCH_FILE,//没有此文件
	E_CODE_FILE_TRANSING,//文件正在传输
	E_CODE_FILE_HAS_EXIST,//文件已存在
	E_CODE_FILE_SEND_FAILED,//文件传输失败

};

//好友关系类型
enum class E_FRIEND_RELATION {
	E_FRIEND_TYPE,//好友
	E_BLACK_TYPE,  //黑名单
	E_STRANGER_TYPE, //陌生人
};

//添加朋友选择
enum class E_FRIEND_OPTION {
	E_UN_KNOWN, //未知
	E_AGREE_ADD,//同意添加
	E_REFUSE_ADD,//拒绝添加
};

//添加好友的状态
enum class E_ADD_FRIEND_STATUS {
	E_UN_KNOWN, //未知
	E_UN_READ,//未通知接收方
	E_READ_UN_NOTIFY, //已通知接收方，未通知发送方
	E_NOTIFY,//已通知发送方
};

//群组成员的角色
enum class E_GROUP_MEMBER_ROLE {
	E_ROLE_CREATER, //群主
	E_ROLE_MANAGER, //管理员
	E_ROLE_MEMBER,  //群成员
	E_ROLE_UNKNOWN, //未知错误
};

enum class CHAT_MSG_TYPE
{
	E_CHAT_UNKNOWN_TYPE,//未知类型
	E_CHAT_TEXT_TYPE,//文本消息
	E_CHAT_FILE_TYPE,//文件消息
	E_CHAT_EMOJI_TYPE,//表情消息
	E_CHAT_IMAGE_TYPE,//图片消息
};

//文件传输方向，是发送还是接收
enum class FILE_TRANS_DIRECTION
{
	E_SEND_FILE,
	E_RECV_FILE,
};

//消息记录的方向
enum class HISTORY_DIRECTION
{
	E_FIRST_MSG,//第一条消息
	E_PREV_MSG,//上一条消息
	E_NEXT_MSG,//下一条消息
	E_LAST_MSG,//最后一条消息
};

//数据接收者类型
enum class DATA_RECIVER_TYPE
{
	E_GROUP_DATA,//群组数据
	E_FRIEND_DATA,//好友数据
};

std::string FriendOption(const E_FRIEND_OPTION& option);
E_FRIEND_OPTION FriendOption(const std::string strOption);

std::string FriendStatus(const E_ADD_FRIEND_STATUS relation);
E_ADD_FRIEND_STATUS FriendStatus(const std::string strStatus);

E_GROUP_MEMBER_ROLE MemberRole(const std::string strRole);
std::string MemberRole(const E_GROUP_MEMBER_ROLE role);

std::string MsgType(const E_MsgType& msgType);


std::string   ChatType(const CHAT_MSG_TYPE& chatType);
CHAT_MSG_TYPE ChatType(const std::string strType);



std::string StringToHex(const std::string& strInput);
std::string HexToString(const std::string& strInput);

std::string OnLineType(const CLIENT_ONLINE_TYPE onlineType);
CLIENT_ONLINE_TYPE OnLineType(const std::string strOnlineType);

std::string FriendRelation(const E_FRIEND_RELATION& relation);
E_FRIEND_RELATION FriendRelation(const std::string& strRelation);

std::string ErrMsg(const ERROR_CODE_TYPE errType);
#endif