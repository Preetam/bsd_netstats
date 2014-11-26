#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int
main() {
	struct ifaddrs* ifap;
	int err = getifaddrs(&ifap);
	if(err) {
		exit(1);
	}

	printf("{\n");

	int first;
	for(first = 1; ifap != NULL; ifap = ifap->ifa_next) {   
		struct if_data* s = ifap->ifa_data;
		if(s != NULL) {
			first ? first = 0 : printf(",\n");

			printf("  \"%s\": {\n    \"bytesIn\": %llu,\n    \"bytesOut\": %llu\n  }",
				ifap->ifa_name, s->ifi_ibytes, s->ifi_obytes);
		}
	}

	freeifaddrs(ifap);
	printf("\n}\n");

	exit(0);
}
