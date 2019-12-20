#include "crobotlogicframe.h"
#include "GameLogic.h"
#include "czhuangmanager.h"

/// ���캯��
CRobotLogicFrame::CRobotLogicFrame() :m_g_myself(NULL), m_g_myselfRoom(NULL)
{
    m_isAddZhuang = false;
    m_curZhuang=-1;
}

/// ��������
CRobotLogicFrame::~CRobotLogicFrame()
{

}

/// ���ڴ����û�׼�������Ϣ
void CRobotLogicFrame::OnProcessPlayerReadyMes(int playerId)
{
	assert(m_g_myself != NULL);
	if(m_g_myself == NULL) return;
}

/// ���ڴ����û���ʼ��Ϸ��ʼ��Ϣ
void CRobotLogicFrame::OnProcessPlayerGameStartMes()
{

}

/// ���ڴ����û�������Ϸ��Ϣ
void CRobotLogicFrame::OnProcessPlayerGameOverMes(void)
{

}

/// ���ڴ����û�������Ϸ��������Ϣ
void CRobotLogicFrame::OnProcessPlayerRoomMes(Json::Value &mes)
{
	assert(m_g_myself != NULL);
	if(m_g_myself == NULL) return;

	switch(mes["MsgSubId"].asInt())
	{
	case IDD_MESSAGE_ROOM_FAPAI:
		{

		}
		break;
	case IDD_MESSAGE_ROOM_STARTXIAZHU:
		{
			//int pstate = mes->read16();
			//std::string pjvhao = mes->readString().c_str();
			m_curZhuang = mes["curZhuang"].asInt();

			if(m_curZhuang != m_g_myself->GetChairIndex())
				m_g_myself->StartTimer(IDD_TIMER_GAME_XIAZHU,rand()%6+2);
		}
		break;
	case IDD_MESSAGE_ROOM_XIAZHU:
		{

		}
		break;
	case IDD_MESSAGE_ROOM_GAMEEND:
		{
			if(rand()%100 < 10)
			{
				if(!m_isAddZhuang && m_curZhuang != m_g_myself->GetChairIndex())
				{
					if(m_g_myself->GetMoney() > CZhuangManager::getSingleton().getMinShangZhuangMoney())
					{
                        Json::Value out;
                        out["MsgId"] = IDD_MESSAGE_ROOM;
                        out["MsgSubId"] = IDD_MESSAGE_ROOM_SHANGZHUANG;
						m_g_myself->SendGameMsg(out);

						m_isAddZhuang=true;
					}
				}
				else
				{
                    Json::Value out;
                    out["MsgId"] = IDD_MESSAGE_ROOM;
                    out["MsgSubId"] = IDD_MESSAGE_ROOM_XIAZHUANG;
					m_g_myself->SendGameMsg(out);

					m_isAddZhuang=false;
				}
			}
		}
		break;
	default:
		break;
	}
}

/// �����û����뷿����Ϣ
void CRobotLogicFrame::OnProcessEnterRoomMsg(int playerId)
{
	assert(m_g_myself != NULL);
	if(m_g_myself == NULL) return;

}

/// �����û��뿪������Ϣ
void CRobotLogicFrame::OnProcessLeaveRoomMsg(int playerId)
{

}

/// �����û�������Ϣ
void CRobotLogicFrame::OnProcessOfflineRoomMes(int playerId)
{

}

/// �����û�����������Ϣ
void CRobotLogicFrame::OnProcessReEnterRoomMes(int playerId)
{

}

/// �����û���ʱ����Ϣ
void CRobotLogicFrame::OnProcessTimerMsg(int timerId,int curTimer)
{
	assert(m_g_myself != NULL);
	if(m_g_myself == NULL) return;

	if(timerId == IDD_TIMER_GAME_XIAZHU)
	{
		if(curTimer <= 0)
		{
			m_g_myself->StopTimer(IDD_TIMER_GAME_XIAZHU);
		}
		else
		{
			if(rand()%100 > 10)
			{
				YaZhuType pYaZhuType = (YaZhuType)(rand()%4);
				int64 pChouMa[] = {100,500,1000,5000,10000000};
				int64 pMoney = pChouMa[rand()%4];

				if(m_g_myself->GetMoney() > pMoney)
				{
                    Json::Value out;
                    out["MsgId"] = IDD_MESSAGE_ROOM;
                    out["MsgSubId"] = IDD_MESSAGE_ROOM_XIAZHU;
                    out["YaZhuType"] = pYaZhuType;
                    out["Money"] = (Json::Int64)pMoney;
					m_g_myself->SendGameMsg(out);
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////