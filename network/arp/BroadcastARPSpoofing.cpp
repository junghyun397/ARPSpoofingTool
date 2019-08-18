#include "../NetFuncs.cpp"
#include "ARPSpoofingInterface.cpp"

class BroadcastARPSpoofing: ARPSpoofingInterface {
private:
    NetFuncs* netFuncs;
public:
    explicit BroadcastARPSpoofing(char* netInterface): netFuncs(new NetFuncs(netInterface)) {}

    void buildSessions() override {

    }

    void startARPSpoofing(int sessionTime) override {

    }
};
