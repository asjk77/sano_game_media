
class LogListener : public external::LogListener {
public:
    LogListener() {}
    virtual ~LogListener() {}

    virtual void Logged(const std::string& inLogString) override;
private:
};
