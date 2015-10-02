/**
* \file
*
* \brief Tests for globalglob plugin
*
* \copyright BSD License (see doc/COPYING or http://www.libelektra.org)
*
*/

#include <stdlib.h>
#include <string.h>

#include <kdbconfig.h>

#include <tests_plugin.h>

static void test_basics()
{
	printf("test basics\n");
	Key *parentKey = keyNew ("user/tests/globalglob", KEY_END);
	KeySet *conf = ksNew(0, KS_END);
	PLUGIN_OPEN("globalglob");

	KeySet *ks = ksNew(0, KS_END);

	succeed_if(plugin->kdbOpen(plugin, parentKey) == 1,
			"call to kdbOpen was not successful");

	succeed_if(plugin->kdbGet(plugin, ks, parentKey) == 1,
			"call to kdbGet was not successful");

	succeed_if(plugin->kdbSet(plugin, ks, parentKey) == 1,
			"call to kdbSet was not successful");

	succeed_if(plugin->kdbError(plugin, ks, parentKey) == 1,
			"call to kdbError was not successful");

	succeed_if(plugin->kdbClose(plugin, parentKey) == 1,
			"call to kdbClose was not successful");

	keyDel(parentKey);
	ksDel(ks);
	PLUGIN_CLOSE();
}



int main(int argc, char** argv)
{
	printf ("GLOBALGLOB     TESTS\n");
	printf ("==================\n\n");

	init (argc, argv);

	test_basics();

	printf ("\ntestmod_globalglob RESULTS: %d test(s) done. %d error(s).\n",
			nbTest, nbError);

	return nbError;
}

