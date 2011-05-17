/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef XMPPMUCMESSAGING_H
#define XMPPMUCMESSAGING_H

#include "xmppclientextension.h"
#include <gloox/mucroomhandler.h>
#include <gloox/mucroomconfighandler.h>

using namespace gloox;

/**
 * @brief This class implements MUC rooms.
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

    /**
     * @brief Register handlers, and etc.
     */
    virtual void attachClient(Client *client);
    /**
     * @brief Unregister handlers, and some other functionality.
     */
    virtual void detachClient(Client *client);

protected:
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCParticipantPresence (MUCRoom *room, const MUCRoomParticipant participant, const Presence &presence);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCMessage (MUCRoom *room, const Message &msg, bool priv);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual bool handleMUCRoomCreation (MUCRoom *room);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCSubject (MUCRoom *room, const std::string &nick, const std::string &subject);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCInviteDecline (MUCRoom *room, const JID &invitee, const std::string &reason);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCError (MUCRoom *room, StanzaError error);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCInfo (MUCRoom *room, int features, const std::string &name, const DataForm *infoForm);
    /**
     * @brief Overrides of gloox::MUCRoomHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCItems (MUCRoom *room, const Disco::ItemList &items);

    /**
     * @brief Overrides of gloox::MUCRoomConfigHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCConfigList (MUCRoom *room, const MUCListItemList &items, MUCOperation operation);
    /**
     * @brief Overrides of gloox::MUCRoomConfigHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCConfigForm (MUCRoom *room, const DataForm &form);
    /**
     * @brief Overrides of gloox::MUCRoomConfigHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCConfigResult (MUCRoom *room, bool success, MUCOperation operation);
    /**
     * @brief Overrides of gloox::MUCRoomConfigHandler
     * Go to the gloox documentation: http://camaya.net/api/gloox-1.0/index.html
     */
    virtual void handleMUCRequest (MUCRoom *room, const DataForm &form);

private:
    /*
     Private fields
     */
    Client  *m_client;
};

#endif // XMPPMUCMESSAGING_H
