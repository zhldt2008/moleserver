#ifndef _DB_OPERATOR_H_INCLUDE_
#define _DB_OPERATOR_H_INCLUDE_

#include "../../include/molnet/Network.h"
#include "../gameserver_common.h"

#include <string>

using namespace network;

class CPlayer;

/**
 * ����û���Ϣ
 */
struct UserDataStru
{
	UserDataStru():UserId(0),Money(0),BankMoney(0),Revenue(0),TotalResult(0),
		Level(0),Experience(0),TotalBureau(0),SBureau(0),FailBureau(0),RunawayBureau(0),
		SuccessRate(0),RunawayRate(0),sex(0),gType(0)
	{
		memset(realName,0,sizeof(realName));
	}

	int UserId;                   // ���ID
	int64 Money;                // ��ҽ�Ǯ
	int64 BankMoney;            // ���н�Ǯ
	int64 Revenue;               // ˰��
	int64 TotalResult;           // �������Ӯ
	int Level;                    // ��ҵȼ�
	int Experience;               // ��Ҿ���ֵ
	int TotalBureau;              // ����ܵľ���
	int SBureau;                  // ���ʤ������
	int FailBureau;               // ���ʧ�ܾ���
	int RunawayBureau;            // ���ܴ���
	float SuccessRate;            // ���ʤ������
	float RunawayRate;            // ������ܸ���

	int sex;                      // ����Ա�
	int gType;                    // �������
	char realName[256];           // ����ǳ�
	char UserName[256];           // ����û���
	char UserIP[256];             // ���IP
};

/**
 * ��Ϸ����ṹ
 */
struct tagGameRoom
{
    int gameid;
    int serverport;
    char serverip[256];
    char processname[256];
    char servername[256];
    int tablecount;
    int tableplayercount;
    int gamingtype;
    int64 lastmoney;
    int64 pielement;
    uint32 roomrevenue;
    int state;                     // 0-������
};

/**
 * �����������Ϸ�����е����ݿ����
 */
class DBOperator : public Singleton<DBOperator>
{
public:
	/// ���캯��
	DBOperator();
	/// ��������
	~DBOperator();

	/// ��ʼ���ݿ�
	bool Initilize(std::string host,std::string user,std::string pass,std::string db,int port);
	/// �ر����ݿ�����
	void Shutdown(void);
	/// ����ά����ǰ���ݿ�����
	void Update(void);

	/// ���õ�ǰ�����Ϸ״̬
	bool SetPlayerGameState(CPlayer *pPlayer);
	/// ����һ����Ϸ��¼�����ݿ���
	bool InsertPlayerGameRecord(uint32 UserId,int64 Score,int64 Revenue,uint32 gameId,uint32 ServerID,
		std::string RoomName,int tableid,int chairid,int64 lastmoney,std::string gametip="",int64 pAgentmoney=0,int64 pcurJetton=0);
    /// ���������Ϣ
    bool UpdateUserData(Player *pPlayer);
    /// ����ָ����ҵ����Ͻ������
    bool UpdateUserMoney(CPlayer *pPlayer);
    /// ���ָ������Ƿ�����Ϸ��
    bool IsExistUserGaming(uint32 UserId,uint32 *serverid,int32 *roomid,int32 *chairid,uint32 *gametype);
    /// �����û�ID�õ��û�����Ϸ����
    bool GetUserData(unsigned int UserId,UserDataStru &UserData);
    /// ����������ƺ��������������Ƿ����
    uint32 IsExistUser(std::string name,std::string password);
    /// �õ���Ϸ������Ϣ
    bool GetGameRoomInfo(uint32 pRoomId,tagGameRoom *ptagGameRoom);
    /// ������Ϸ������������
    bool UpdateGameRoomOnlinePlayerCount(uint32 pRoomId,int currealplayercount,int currobotplayercount);

private:
	DataProvider *m_DataProvider;                               /**< ���ڷ��ʱ������ݿ� */
};

#define ServerDBOperator DBOperator::getSingleton()

#endif