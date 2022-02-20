/**
 * @brief 문자열 Widget 입니다.
 */
class String : public Widget {
public:
    String( const char * inString ) {}
    virtual ~String() {}

    void ChangeTitle() {}
private:
    std::string mString;
    TexturePtr mStringCache;
};
