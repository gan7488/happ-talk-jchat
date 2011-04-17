/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPMUCMESSAGING_H
#define XMPPMUCMESSAGING_H

#include "xmppclientextension.h"
#include <gloox/mucroomhandler.h>
#include <gloox/mucroomconfighandler.h>

using namespace gloox;

/*
 This class implements MUC rooms.
 */
class XMPPMUCMessaging : public XMPPClientExtension,
                                MUCRoomHandler,
                                MUCRoomConfigHandler
{
    Q_OBJECT
public:
    /*
     Constructor
     */
    XMPPMUCMessaging();
    virtual ~XMPPMUCMessaging();

    /*
     Attach and detach
     */
    virtual void attachClient(Client *client);
    virtual void detachClient(Client *client);

signals:

public slots:
protected:
    /*
     Overrides of gloox::MUCRoomHandler
     */
    virtual void handleMUCParticipantPresence (MUCRoom *room, const MUCRoomParticipant participant, const Presence &presence);
    virtual void handleMUCMessage (MUCRoom *room, const Message &msg, bool priv);
    virtual bool handleMUCRoomCreation (MUCRoom *room);
    virtual void handleMUCSubject (MUCRoom *room, const std::string &nick, const std::string &subject);
    virtual void handleMUCInviteDecline (MUCRoom *room, const JID &invitee, const std::string &reason);
    virtual void handleMUCError (MUCRoom *room, StanzaError error);
    virtual void handleMUCInfo (MUCRoom *room, int features, const std::string &name, const DataForm *infoForm);
    virtual void handleMUCItems (MUCRoom *room, const Disco::ItemList &items);

    /*
     Override of gloox::MUCRoomConfigHandler
     */
    virtual void handleMUCConfigList (MUCRoom *room, const MUCListItemList &items, MUCOperation operation);
    virtual void handleMUCConfigForm (MUCRoom *room, const DataForm &form);
    virtual void handleMUCConfigResult (MUCRoom *room, bool success, MUCOperation operation);
    virtual void handleMUCRequest (MUCRoom *room, const DataForm &form);

private:
    /*
     Private fields
     */
    Client  *m_client;
};

#endif // XMPPMUCMESSAGING_H
