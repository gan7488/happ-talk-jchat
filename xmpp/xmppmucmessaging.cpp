/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#include "xmppmucmessaging.h"

/*
 Ctors
 */
XMPPMUCMessaging::XMPPMUCMessaging() :
    XMPPClientExtension(), m_client(0)
{
}

XMPPMUCMessaging::~XMPPMUCMessaging()
{
    detachClient(m_client);
}

/*
 Attach & detach
 */
void XMPPMUCMessaging::attachClient(Client *client)
{
    if (!client) return;
    m_client = client;
}

void XMPPMUCMessaging::detachClient(Client *client)
{
    if (m_client == client && client)
    {
        m_client = 0;
    }
}

/*
 MUCRoomHandler methods goes here
 */
void XMPPMUCMessaging::handleMUCParticipantPresence
        (MUCRoom *room, const MUCRoomParticipant participant, const Presence &presence)
{ }

void XMPPMUCMessaging::handleMUCMessage
        (MUCRoom *room, const Message &msg, bool priv)
{ }

bool XMPPMUCMessaging::handleMUCRoomCreation (MUCRoom *room)
{ }

void XMPPMUCMessaging::handleMUCSubject
        (MUCRoom *room, const std::string &nick, const std::string &subject)
{ }

void XMPPMUCMessaging::handleMUCInviteDecline
        (MUCRoom *room, const JID &invitee, const std::string &reason)
{ }

void XMPPMUCMessaging::handleMUCError
        (MUCRoom *room, StanzaError error)
{ }

void XMPPMUCMessaging::handleMUCInfo
        (MUCRoom *room, int features, const std::string &name, const DataForm *infoForm)
{ }

void XMPPMUCMessaging::handleMUCItems
        (MUCRoom *room, const Disco::ItemList &items)
{ }

/*
 MUCRoomConfigHandler goes here
 */
void XMPPMUCMessaging::handleMUCConfigList
        (MUCRoom *room, const MUCListItemList &items, MUCOperation operation)
{ }

void XMPPMUCMessaging::handleMUCConfigForm
        (MUCRoom *room, const DataForm &form)
{ }

void XMPPMUCMessaging::handleMUCConfigResult
        (MUCRoom *room, bool success, MUCOperation operation)
{ }

void XMPPMUCMessaging::handleMUCRequest
        (MUCRoom *room, const DataForm &form)
{ }
