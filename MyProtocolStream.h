#ifndef MY_PROTOCOL_STREAM_H
#define MY_PROTOCOL_STREAM_H
#include <string>

namespace net {
    class Endl{};
    extern Endl endll;
    enum Protocol{
        PACKET_LENGTH = 4,
        CHECKSUM_LENGTH = 2,
        PACKET_LENGTH_MAX = 0xffff
    };

    enum ProtocolType {
        PROTOCOL_ROW = 0,
        PROTOCOL_PACK
    };

class MyProtocolStream {
public:
    MyProtocolStream(std::string& str, ProtocolType type = PROTOCOL_ROW);
    ~MyProtocolStream() = default;
public:    
    bool loadCString(const char* cstr, int len);
    bool loadString(const std::string& str);
    bool loadFloat(float f, bool reverse = false);
    bool loadDouble(double d, bool reverse = false);
    bool loadInt64(int64_t i, bool reverse = false);
    bool loadInt32(int32_t i, bool reverse = false);
    bool loadShort(short s, bool reverse = false);
    bool loadChar(char c, bool reverse = false);
    bool loadBool(bool c, bool reverse = false);
	MyProtocolStream& operator<<(const std::string &str);
    MyProtocolStream& operator<<(const char* str);
	MyProtocolStream& operator<<(float f);
    MyProtocolStream& operator<<(double d);
    MyProtocolStream& operator<<(int64_t i);
    MyProtocolStream& operator<<(int32_t i);
    MyProtocolStream& operator<<(short s);
    MyProtocolStream& operator<<(char c);
    MyProtocolStream& operator<<(bool c);
    MyProtocolStream& operator<<(Endl endll);
    //TODO:CString
public:
    bool getCString(char* cstr, int &len, int maxLen = PACKET_LENGTH_MAX);
    bool getString(std::string& str, int maxLen = PACKET_LENGTH_MAX);
    bool getFloat(float& f);
    bool getDouble(double& d);
    bool getInt64(int64_t& i);
    bool getInt32(int32_t& i);
    bool getShort(short& s);
    bool getChar(char& c);
	bool getBool(bool& c);
    MyProtocolStream& operator>>(std::string &str);
    MyProtocolStream& operator>>(float& f);
    MyProtocolStream& operator>>(double& d);
    MyProtocolStream& operator>>(int64_t& i);
    MyProtocolStream& operator>>(int32_t& i);
    MyProtocolStream& operator>>(short& s);
    MyProtocolStream& operator>>(char& c);
    MyProtocolStream& operator>>(bool& c);
    size_t getAll(char* szBuffer, size_t iLen) const;
    const char* getData() const;
public:
    inline const char* currentPos() const { return &m_str[m_pos]; }
    inline int currentIndex() const { return m_pos; }
    bool empty() const;
    int size() const;
    bool isEnd() const;
    bool readLength(size_t& len);
    void flush();
    void clear();
    void setPos(int pos = 0);
    void trucate(int pos);
private:
    MyProtocolStream(const MyProtocolStream&) = delete;
    MyProtocolStream& operator=(const MyProtocolStream&) = delete;
    bool readLengthWithoutOffset(size_t& headlen, size_t& outlen);
    
    std::string &m_str;
    int m_pos;
};// end of class MyProtocolStream

    //计算校验和
    unsigned short checksum(const unsigned short* buffer, int size);
    //将一个4字节的整型数值压缩成1~5个字节
    void write7BitEncoded(uint32_t value, std::string& buf);
    //将一个8字节的整型值编码成1~10个字节
    void write7BitEncoded(uint64_t value, std::string& buf);
    //将一个1~5个字节的字符数组值还原成4字节的整型值
    void read7BitEncoded(const char* buf, uint32_t len, uint32_t& value);
    //将一个1~10个字节的值还原成8字节的整型值
    void read7BitEncoded(const char* buf, uint32_t len, uint64_t& value);
    
    uint64_t htonll(uint64_t num);
    uint64_t ntohll(uint64_t num);
} //end of namespace net

#endif
