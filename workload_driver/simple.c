#include <stdio.h>
#include <stdint.h>
#include <libpmemobj.h>
#include <unistd.h>
#include "pmrace_interface.h"
//#include "layout.h"

#define LAYOUT_NAME "lala"
struct a{
    uint64_t x;
    uint64_t y;
    uint64_t z;
};

static inline int
file_exists(char const *file)
{
	return access(file, F_OK);
}

int main(const int argc, const char** argv){
    PMEMobjpool *pop;
    const char* path = argv[1];
    //int c=0;
    if (file_exists(path) != 0) {
		if ((pop = pmemobj_create(path, LAYOUT_NAME,
			PMEMOBJ_MIN_POOL, 0666)) == NULL) {
			perror("failed to create pool\n");
			return 1;
		}
	} else {
		if ((pop = pmemobj_open(path, LAYOUT_NAME)) == NULL) {
			perror("failed to open pool\n");
			return 1;
		}
	}
    fprintf(stderr, "startops\n");
    PMEMoid root = pmemobj_root(pop, sizeof(struct a));
    struct a *rootp = pmemobj_direct(root);
    //PMRace_addCommitVar(&rootp->y, sizeof(rootp->y));
    //printf("x:%p", &rootp->x);
	//rootp->y++;
    //pmemobj_persist(pop, &rootp->y, sizeof(rootp->y));
    PMRace_addCommitVar(&rootp->y, sizeof(rootp->y));
    fprintf(stdout, "@@@@@@&z=%p\n", &(rootp->z));
    //rootp->x++;
    // Start the TX
    PMRace_RoIBegin(TRACING, PRE_FAILURE|POST_FAILURE);
    rootp->y++;
    pmemobj_persist(pop, &rootp->y, sizeof(rootp->y));
    rootp->x++;
    pmemobj_persist(pop, &rootp->x, sizeof(rootp->x));

    rootp->z=rootp->x;

    pmemobj_persist(pop, &rootp->y, sizeof(rootp->z));
    /*
    TX_BEGIN(pop){
        pmemobj_tx_add_range_direct(&rootp->z, sizeof(uint64_t));
        rootp->z++;
        //rootp->x++;
        PMRace_addFailurePoint(PRE_FAILURE|POST_FAILURE);
    }TX_END
    */
    PMRace_RoIEnd(TRACING, PRE_FAILURE|POST_FAILURE);
    pmemobj_close(pop);
    PMRace_complete(TRACING, PRE_FAILURE|POST_FAILURE);
    return 0;
}
