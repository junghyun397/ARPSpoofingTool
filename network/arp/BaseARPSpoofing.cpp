#pragma once

#include <optional>
#include <ctime>
#include <pcap/pcap.h>
#include "../NetFuncs.cpp"

class BaseARPSpoofing {
private:
    long endTime = 0;
protected:
    NetFuncs* netFuncs;
    pcap_t* pcapHandle;

    void setUpTimer(int sessionTime) {
        if (sessionTime != SESSION_TIME_UNLIMITED) this->endTime = std::time(nullptr) + sessionTime;
    }

    bool isAlive() {
        return this->endTime > std::time(nullptr)
                 or this->endTime == BaseARPSpoofing::SESSION_TIME_UNLIMITED;
    }
public:
    explicit BaseARPSpoofing(char* networkInterface): netFuncs(new NetFuncs(networkInterface)) {
        char errBuf[PCAP_ERRBUF_SIZE];
        this->pcapHandle = pcap_open_live(this->netFuncs->getNetworkInterface(), BUFSIZ, 1, 1000, errBuf);
    }

    static const int SESSION_TIME_UNLIMITED = -1;
    static const int SESSION_TIME_1M        = 60;
    static const int SESSION_TIME_10M       = 600;
    static const int SESSION_TIME_1H        = 3600;

    virtual void startARPSpoofing(int sessionTime) = 0;
};