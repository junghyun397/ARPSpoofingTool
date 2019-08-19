#include <sys/types.h>

class BaseTrigger {
public:
    virtual void editIPV4Packet(u_char* packet) = 0;
};