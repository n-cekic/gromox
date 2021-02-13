// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2020 grammm GmbH
// This file is part of Gromox.
#define DECLARE_API_STATIC
#include <cstdio>
#include <gromox/localemap.hpp>
#include <gromox/svc_common.h>
#include <gromox/common_types.hpp>

static BOOL svc_localeplug(int reason, void **apidata)
{
	if (reason == PLUGIN_FREE)
		return TRUE;
	if (reason != PLUGIN_INIT)
		return false;
	LINK_API(apidata);
	using namespace gromox;
	localemap_init(get_data_path());
	if (!register_service("verify_cpid", reinterpret_cast<void *>(verify_cpid)) ||
	    !register_service("cpid_to_charset", reinterpret_cast<void *>(cpid_to_cset)) ||
	    !register_service("charset_to_cpid", reinterpret_cast<void *>(cset_to_cpid)) ||
	    !register_service("ltag_to_lcid", reinterpret_cast<void *>(ltag_to_lcid)) ||
	    !register_service("lcid_to_ltag", reinterpret_cast<void *>(lcid_to_ltag))) {
		fprintf(stderr, "[localemap]: failed to register services\n");
		return FALSE;
	}
	return TRUE;
}
SVC_ENTRY(svc_localeplug);
