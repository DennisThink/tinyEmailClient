#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "SnowFlake/SnowFlake.h"
#include "CommonMsg.h"
#include "../include/thirdparty/httpServer/client_http.hpp"

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

std::string g_strUserOne = "TestUser1";
std::string g_strUserTwo = "TestUser2";
std::string g_strGroupOne = "TestGroup1";
static SnowFlake msgIdUtil(4,4);
void Do_UserLogin(HttpClient& client) {
	UserLoginRspMsg rspMsg;
	try {
		UserLoginReqMsg reqMsg;
		reqMsg.m_strMsgId = std::to_string(msgIdUtil.nextId());
		reqMsg.m_strUserName = "dennismi@163.com";
		reqMsg.m_strPassword = "";
		auto rsp = client.request("POST", "/user_login", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void UserLogin(HttpClient& client,std::string strUser) {
	Do_UserLogin(client);
}

void Do_SendEmail(HttpClient& client) {
	SendEmailRsp rspMsg;
	try {
		SendEmailReq reqMsg;
		reqMsg.m_strMsgId = std::to_string(msgIdUtil.nextId());
		reqMsg.m_strUserName = "dennismi@163.com";
		reqMsg.m_strRecvName = "2475027682@qq.com";
		reqMsg.m_strSubject = "TinyIM Compile Problem";
		{
			reqMsg.m_strEmailContext = R"(Vice4 President Johnson, Mr. Speaker, Mr. Chief Justice, President Eisenhower, Vice President Nixon, President Truman, Reverend Clergy5, fellow citizens:
			We observe today not a victory of party, but a celebration of freedom -- symbolizing6 an end, as well as a beginning -- signifying renewal7, as well as change.For I have sworn before you and Almighty8 God the same solemn oath our forebears prescribed nearly a century and three - quarters ago.
			The world is very different now.For man holds in his mortal hands the power to abolish all forms of human poverty and all forms of human life.And yet the same revolutionary beliefs for which our forebears fought are still at issue around the globe -- the belief that the rights of man come not from the generosity9 of the state, but from the hand of God.
			We dare not forget today that we are the heirs of that first revolution.Let the word go forth10 from this time and place, to friend and foe11 alike, that the torch has been passed to a new generation of Americans -- born in this century, tempered by war, disciplined by a hard and bitter peace, proud of our ancient heritage, and unwilling12 to witness or permit the slow undoing14 of those human rights to which this nation has always been committed, and to which we are committed today at home and around the world.
			Let every nation know, whether it wishes us well or ill, that we shall pay any price, bear any burden, meet any hardship, support any friend, oppose any foe, to assure the survival and the success of liberty.
			This much we pledge-- and more.
			To those old allies whose cultural and spiritual origins we share, we pledge the loyalty15 of faithful friends.United there is little we cannot do in a host of cooperative ventures.Divided there is little we can do -- for we dare not meet a powerful challenge at odds16 and split asunder17.
			To those new states whom we welcome to the ranks of the free, we pledge our word that one form of colonial control shall not have passed away merely to be replaced by a far more iron tyranny.We shall not always expect to find them supporting our view.But we shall always hope to find them strongly supporting their own freedom-- and to remember that, in the past, those who foolishly sought power by riding the back of the tiger ended up inside.)";
		}
		auto rsp = client.request("POST", "/send_email", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void SendEmail(HttpClient& client) {
	Do_SendEmail(client);
}


void Do_QueryTask(HttpClient& client) {
	QueryTaskRsp rspMsg;
	try {
		QueryTaskReq reqMsg;
		reqMsg.m_strMsgId = std::to_string(msgIdUtil.nextId());
		reqMsg.m_strTaskId = "dennismi@163.com";

		auto rsp = client.request("POST", "/query_task", reqMsg.ToString());
		std::string strRsp = rsp->content.string();
		std::cout << strRsp << std::endl;
		CHECK(rspMsg.FromString(strRsp));

	}
	catch (const SimpleWeb::system_error& e) {
		std::cerr << "Client Req Error " << e.what() << std::endl;
	}
}

void QueryTask(HttpClient& client) {
	Do_QueryTask(client);
}




TEST_CASE("HTTP_UserRegisterReqPro") {
	HttpClient client("127.0.0.1:8000");
	//Register
	UserLogin(client, g_strUserOne);
	SendEmail(client);
	QueryTask(client);
}
