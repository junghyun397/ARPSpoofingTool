#include "IBaseTrigger.cpp"

class DNSSpoofingTrigger: public IBaseTrigger {
private:
    char* targetDNSServer{};
public:
    explicit DNSSpoofingTrigger(char* targetDNSServer): targetDNSServer(targetDNSServer) {}

    void editIPV4Packet(u_char* packet) override {

    }
};
