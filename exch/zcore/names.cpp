// SPDX-License-Identifier: AGPL-3.0-or-later, OR GPL-2.0-or-later WITH linking exception
// SPDX-FileCopyrightText: 2020 grommunio GmbH
// This file is part of Gromox.
#include <gromox/defs.h>
#include <gromox/zcore_rpc.hpp>
#include "common_util.h"

#define EXP(s) zcore_callid::s
#define E(s) #s
static constexpr const char *zcore_rpc_names[] = {
	E(LOGON),
	E(UNLOADOBJECT),
	E(OPENENTRY),
	E(OPENSTOREENTRY),
	E(OPENABENTRY),
	E(RESOLVENAME),
	nullptr,
	E(GETPERMISSIONS),
	E(MODIFYPERMISSIONS),
	E(MODIFYRULES),
	E(GETABGAL),
	E(LOADSTORETABLE),
	E(OPENSTORE),
	E(OPENPROPFILESEC),
	E(LOADHIERARCHYTABLE),
	E(LOADCONTENTTABLE),
	E(LOADRECIPIENTTABLE),
	nullptr,
	E(LOADRULETABLE),
	E(CREATEMESSAGE),
	E(DELETEMESSAGES),
	E(COPYMESSAGES),
	E(SETREADFLAGS),
	E(CREATEFOLDER),
	E(DELETEFOLDER),
	E(EMPTYFOLDER),
	E(COPYFOLDER),
	E(GETSTOREENTRYID),
	E(ENTRYIDFROMSOURCEKEY),
	E(STOREADVISE),
	E(UNADVISE),
	E(NOTIFDEQUEUE),
	E(QUERYROWS),
	E(SETCOLUMNS),
	E(SEEKROW),
	E(SORTTABLE),
	E(GETROWCOUNT),
	E(RESTRICTTABLE),
	E(FINDROW),
	E(CREATEBOOKMARK),
	E(FREEBOOKMARK),
	E(GETRECEIVEFOLDER),
	E(MODIFYRECIPIENTS),
	E(SUBMITMESSAGE),
	E(LOADATTACHMENTTABLE),
	E(OPENATTACHMENT),
	E(CREATEATTACHMENT),
	E(DELETEATTACHMENT),
	E(SETPROPVALS),
	E(GETPROPVALS),
	E(DELETEPROPVALS),
	E(SETMESSAGEREADFLAG),
	E(OPENEMBEDDED),
	E(GETNAMEDPROPIDS),
	E(GETPROPNAMES),
	E(COPYTO),
	E(SAVECHANGES),
	E(HIERARCHYSYNC),
	E(CONTENTSYNC),
	E(CONFIGSYNC),
	E(STATESYNC),
	E(SYNCMESSAGECHANGE),
	E(SYNCFOLDERCHANGE),
	E(SYNCREADSTATECHANGES),
	E(SYNCDELETIONS),
	E(HIERARCHYIMPORT),
	E(CONTENTIMPORT),
	E(CONFIGIMPORT),
	E(STATEIMPORT),
	E(IMPORTMESSAGE),
	E(IMPORTFOLDER),
	E(IMPORTDELETION),
	E(IMPORTREADSTATES),
	E(GETSEARCHCRITERIA),
	E(SETSEARCHCRITERIA),
	E(MESSAGETORFC822),
	E(RFC822TOMESSAGE),
	E(MESSAGETOICAL),
	E(ICALTOMESSAGE),
	E(MESSAGETOVCF),
	E(VCFTOMESSAGE),
	E(UINFO),
	E(CHECKSESSION),
	E(GETUSERAVAILABILITY),
	E(SETPASSWD),
	E(LINKMESSAGE),
};
#undef E
#undef EXP

const char *zcore_rpc_idtoname(unsigned int i)
{
	static_assert(GX_ARRAY_SIZE(zcore_rpc_names) == zcore_callid::LINKMESSAGE + 1);
	const char *s = i < GX_ARRAY_SIZE(zcore_rpc_names) ? zcore_rpc_names[i] : nullptr;
	return s != nullptr ? s : "";
}
