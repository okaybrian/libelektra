/**
* \file
*
* \brief Header for globalglob plugin
*
* \copyright BSD License (see doc/COPYING or http://www.libelektra.org)
*
*/

#ifndef ELEKTRA_PLUGIN_GLOBALGLOB_H
#define ELEKTRA_PLUGIN_GLOBALGLOB_H

#include <kdbplugin.h>


int elektraGlobalglobOpen(Plugin *handle, Key *errorKey);
int elektraGlobalglobClose(Plugin *handle, Key *errorKey);
int elektraGlobalglobGet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraGlobalglobSet(Plugin *handle, KeySet *ks, Key *parentKey);
int elektraGlobalglobError(Plugin *handle, KeySet *ks, Key *parentKey);

Plugin *ELEKTRA_PLUGIN_EXPORT(globalglob);

#endif
