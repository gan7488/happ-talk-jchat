/******************************************************************************
**	Author: Svirskiy Sergey			Nickname: Happ
******************************************************************************/

#ifndef CONSTS_H
#define CONSTS_H

#include <Qt>

/*
 Application name
 */
const QString app = "Jchat";
/*
 Organization name
 */
const QString org = "Happs";
const QString url = "http://code.google.com/p/happ-talk-jchat/";

/*
 Version. Format: 0x00.00.000
 0x1000     means: 1.0.0
 0xA10CD1   means: 10.16.3281 (0xA.10.CD1)
 */
const int version = 0x1000;

inline int major(void) { return (version >> 20) & 0xFF; }
inline int minor(void) { return (version >> 12) & 0xFF; }
inline int build(void) { return version & 0xFFF; }

#endif // CONSTS_H
