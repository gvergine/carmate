#include "syncer.h"
//#include <stdio.h>
#include <unistd.h>

void loop_syncer()
{
	int fd_to_sync = -1;

	while(true) {
    	uint32_t datatype;
    	uint8_t data;
		queue_pop(&queue_syncer, &datatype, &data);

		if (datatype == 1) {
			if (fd_to_sync > 0) {
				fdatasync(fd_to_sync);
				//printf("syncer: sync %d!\n",fd_to_sync);
				fd_to_sync = -1;
			}
		} else if (datatype == 3) {
			fd_to_sync = data;
			//printf("recv sync req %d\n",fd_to_sync);
		}
    }
}
