#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <stdio.h>

int
main() {
        struct ifaddrs* ifap;
        getifaddrs(&ifap);

        printf("{\n");
        int first;
        for(first = 1; ifap != NULL; ifap = ifap->ifa_next) {   
                struct if_data* s = ifap->ifa_data;
                if(s != NULL) {
                        if(!first) {
                                printf(",\n");
                        } else {
                                first = 0;
                        }
                        printf("  \"%s\": {\n    \"bytesIn\": %d,\n    \"bytesOut\": %d\n  }",
                                ifap->ifa_name, s->ifi_ibytes, s->ifi_obytes);
                }
        }
        freeifaddrs(ifap);

        printf("\n}\n");
}
