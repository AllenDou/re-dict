#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include "zmalloc.h"
#include "dict.h"
#include "sds.h"

int dictSdsKeyCompare(void *privdata, const void *key1,
				const void *key2)
{
		int l1,l2;
		DICT_NOTUSED(privdata);

		l1 = sdslen((sds)key1);
		l2 = sdslen((sds)key2);
		if (l1 != l2) return 0;
		return memcmp(key1, key2, l1) == 0;
}

unsigned int dictSdsHash(const void *key) {
		return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
}

dictType keyptrDictType = {
		dictSdsHash,               /* hash function */
		NULL,                      /* key dup */
		NULL,                      /* val dup */
		dictSdsKeyCompare,         /* key compare */
		NULL,                      /* key destructor */
		NULL                       /* val destructor */
};

int main(int argc, char** argv)
{
		fprintf(stdout,"%s\'pid: %d\r\n",argv[0],getpid());
		dict *d = dictCreate(&keyptrDictType,NULL);
		int retval = dictAdd(d,sdsnew("key"),"val");
		dictEntry *de = dictFind(d,sdsnew("key"));
		(void)de;
		(void)retval;
		return 0;
}

