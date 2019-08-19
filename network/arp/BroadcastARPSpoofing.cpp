#pragma once

#include "ARPSpoofingManager.cpp"

class BroadcastARPSpoofing: public ARPSpoofingManager {
public:
    explicit BroadcastARPSpoofing(char *networkInterface): ARPSpoofingManager(networkInterface) {}

    void buildSessions() override {
    }

    void startARPSpoofing(int sessionTime) override {

    }
};
