class ARPSpoofingInterface {
public:
    const static int UNLIMITED = 0;

    virtual void buildSessions() = 0;
    virtual void startARPSpoofing(int sessionTime) = 0;
};