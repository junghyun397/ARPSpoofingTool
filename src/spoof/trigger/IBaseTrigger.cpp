#pragma once

#include <sys/types.h>

class IBaseTrigger {
public:
    virtual void editIPV4Packet(u_char* packet) = 0;
};