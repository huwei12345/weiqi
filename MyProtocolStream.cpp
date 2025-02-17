#include "MyProtocolStream.h"
#include "MyProtocolStream.h"
#include <string.h>
#include <cmath>
#include <iostream>
#include <QtEndian>
namespace net
{
    Endl endll;


	unsigned int CRC_16_TABLE[256] = {
	0x3f,0x10,0x0e,0x21,0x32,0x1d,0x03,0x2c,0x25,0x0a,0x14,0x3b,0x28,0x07,0x19,0x36,
	0x0b,0x24,0x3a,0x15,0x06,0x29,0x37,0x18,0x11,0x3e,0x20,0x0f,0x1c,0x33,0x2d,0x02,
	0x38,0x17,0x09,0x26,0x35,0x1a,0x04,0x2b,0x22,0x0d,0x13,0x3c,0x2f,0x00,0x1e,0x31,
	0x0c,0x23,0x3d,0x12,0x01,0x2e,0x30,0x1f,0x16,0x39,0x27,0x08,0x1b,0x34,0x2a,0x05,
	0x31,0x1e,0x00,0x2f,0x3c,0x13,0x0d,0x22,0x2b,0x04,0x1a,0x35,0x26,0x09,0x17,0x38,
	0x05,0x2a,0x34,0x1b,0x08,0x27,0x39,0x16,0x1f,0x30,0x2e,0x01,0x12,0x3d,0x23,0x0c,
	0x36,0x19,0x07,0x28,0x3b,0x14,0x0a,0x25,0x2c,0x03,0x1d,0x32,0x21,0x0e,0x10,0x3f,
	0x02,0x2d,0x33,0x1c,0x0f,0x20,0x3e,0x11,0x18,0x37,0x29,0x06,0x15,0x3a,0x24,0x0b,
	0x23,0x0c,0x12,0x3d,0x2e,0x01,0x1f,0x30,0x39,0x16,0x08,0x27,0x34,0x1b,0x05,0x2a,
	0x17,0x38,0x26,0x09,0x1a,0x35,0x2b,0x04,0x0d,0x22,0x3c,0x13,0x00,0x2f,0x31,0x1e,
	0x24,0x0b,0x15,0x3a,0x29,0x06,0x18,0x37,0x3e,0x11,0x0f,0x20,0x33,0x1c,0x02,0x2d,
	0x10,0x3f,0x21,0x0e,0x1d,0x32,0x2c,0x03,0x0a,0x25,0x3b,0x14,0x07,0x28,0x36,0x19,
	0x2d,0x02,0x1c,0x33,0x20,0x0f,0x11,0x3e,0x37,0x18,0x06,0x29,0x3a,0x15,0x0b,0x24,
	0x19,0x36,0x28,0x07,0x14,0x3b,0x25,0x0a,0x03,0x2c,0x32,0x1d,0x0e,0x21,0x3f,0x10,
	0x2a,0x05,0x1b,0x34,0x27,0x08,0x16,0x39,0x30,0x1f,0x01,0x2e,0x3d,0x12,0x0c,0x23,
	0x1e,0x31,0x2f,0x00,0x13,0x3c,0x22,0x0d,0x04,0x2b,0x35,0x1a,0x09,0x26,0x38,0x17
	};
    
    uint64_t htonll(uint64_t num)
    {
        uint64_t result = 0;
        char *x = (char *)&result;
        char *y = (char *)&num;
        for (int i = 0; i < 8; i++)
        {
            x[i] = y[8 - i - 1];
        }
        return result;
    }
    uint64_t ntohll(uint64_t num)
    {
        return htonll(num);
    }

	unsigned short checksum(unsigned char *src ,int len)
	{
		unsigned char *ptr = src;
		unsigned short crc = 0;
		unsigned char* remainder = (unsigned char*)&crc;
		int r= 0xFFFF;
		while(len > 0){
			r = (r << 8) ^ CRC_16_TABLE[((r >> 8) ^ *ptr) & 0xFF];
			len --;
			ptr++;
		}
		remainder[1] = (r >> 8) & 0xFF;
		remainder[0] = r & 0xFF;
		return crc;
	}

    // 将一个4字节的整型数值压缩成1~5个字节
    void write7BitEncoded(uint32_t value, std::string &buf)
    {
        do
        {
            unsigned char c = (unsigned char)(value & 0x7F);
            value >>= 7;
            if (value)
                c |= 0x80;

            buf.append(1, c);
        } while (value);
    }

    // 将一个8字节的整型值编码成1~10个字节
    void write7BitEncoded(uint64_t value, std::string &buf)
    {
        do
        {
            unsigned char c = (unsigned char)(value & 0x7F);
            value >>= 7;
            if (value)
                c |= 0x80;

            buf.append(1, c);
        } while (value);
    }

    // 将一个1~5个字节的字符数组值还原成4字节的整型值
    void read7BitEncoded(const char *buf, uint32_t len, uint32_t &value)
    {
        char c;
        value = 0;
        int bitCount = 0;
        int index = 0;
        do
        {
            c = buf[index];
            uint32_t x = (c & 0x7F);
            x <<= bitCount;
            value += x;
            bitCount += 7;
            ++index;
        } while (c & 0x80);
    }

    // 将一个1~10个字节的值还原成4字节的整型值
    void read7BitEncoded(const char *buf, uint32_t len, uint64_t &value)
    {
        char c;
        value = 0;
        int bitCount = 0;
        int index = 0;
        do
        {
            c = buf[index];
            uint64_t x = (c & 0x7F);
            x <<= bitCount;
            value += x;
            bitCount += 7;
            ++index;
        } while (c & 0x80);
    }

    MyProtocolStream::MyProtocolStream(std::string &str, ProtocolType type) : m_str(str)
    {
        if (type == PROTOCOL_PACK) {
            m_str.append(PACKET_LENGTH + CHECKSUM_LENGTH, 0);
            m_pos = PACKET_LENGTH + CHECKSUM_LENGTH;
        }
        else {
            m_pos = 0;
        }
    }

    bool MyProtocolStream::loadCString(const char *cstr, int len)
    {
        std::string buf;
        write7BitEncoded((uint32_t)len, buf);
        m_str.append(buf);

        m_str.append(cstr, len);
        return false;
    }

    bool MyProtocolStream::loadString(const std::string &str)
    {
        return loadCString(str.c_str(), str.length());
    }

    bool MyProtocolStream::loadFloat(float f, bool reverse)
    {
        char doublestr[128];
        if (reverse == false)
        {
            sprintf(doublestr, "%f", f);
            loadCString(doublestr, strlen(doublestr));
        }
        else
            loadCString(doublestr, 0);
        return true;
    }

    bool MyProtocolStream::loadDouble(double d, bool reverse)
    {
        char doublestr[128];
        if (reverse == false)
        {
            sprintf(doublestr, "%lf", d);
            loadCString(doublestr, strlen(doublestr));
        }
        else
            loadCString(doublestr, 0);
        return true;
    }

    bool MyProtocolStream::loadInt64(int64_t i, bool reverse)
    {
        char *p = &m_str[0];
        if (reverse == false)
        {
            int64_t ii = htonll(i);
            m_str.append((char *)&ii, sizeof(ii));
        }
        else
            m_str.append((char *)&i, sizeof(i));
        return true;
    }

    bool MyProtocolStream::loadInt32(int32_t i, bool reverse)
    {
        char *p = &m_str[0];
        if (reverse == false)
        {
            int32_t ii = qbswap((int)i);
            //int32_t ii = htonl(i);
            m_str.append((char *)&ii, sizeof(ii));
        }
        else
            m_str.append((char *)&i, sizeof(i));
        return true;
    }

    bool MyProtocolStream::loadShort(short s, bool reverse)
    {
        char *p = &m_str[0];
        if (reverse == false)
        {
            short ss = qbswap(s);
            //short ss = htons(s);
            m_str.append((char *)&ss, sizeof(ss));
        }
        else
            m_str.append((char *)&s, sizeof(s));
        return true;
    }

    bool MyProtocolStream::loadChar(char c, bool reverse)
    {
        m_str += c;
        return true;
    }
	
	
    bool MyProtocolStream::loadBool(bool c, bool reverse)
    {
		char x = c ? 1 : 0;
        m_str += x;
        return true;
    }

    bool MyProtocolStream::getCString(char *cstr, int &outlen, int maxLen)
    {
        size_t headlen;
        size_t fieldlen; // 该字符串的长度
        if (!readLengthWithoutOffset(headlen, fieldlen))
        {
            return false;
        }
        // user buffer is not enough
        if (maxLen != 0 && fieldlen > maxLen)
        {
            return false;
        }
        m_pos += headlen;
        char *cur = &m_str[m_pos];
        if (m_pos + fieldlen > m_str.length())
        {
            outlen = 0;
            return false;
        }
        outlen = fieldlen;
        memcpy(cstr, cur, outlen);
        m_pos += fieldlen;
        return true;
    }

    bool MyProtocolStream::getString(std::string &str, int maxLen)
    {
        size_t headlen;
        size_t fieldlen;
        if (!readLengthWithoutOffset(headlen, fieldlen))
        {
            return false;
        }
        // user buffer is not enough
        if (maxLen != 0 && fieldlen > maxLen)
        {
            return false;
        }
        char *cur = &m_str[m_pos];
        cur += headlen;
        m_pos += headlen;
        if (m_pos + fieldlen > m_str.length())
        {
            return false;
        }
        str.assign(cur, fieldlen);
        m_pos += fieldlen;
        return true;
    }

    bool MyProtocolStream::getFloat(float &f)
    {
        size_t headlen;
        size_t fieldlen;
        if (!readLengthWithoutOffset(headlen, fieldlen))
        {
            return false;
        }
        // user buffer is not enough
        char *cur = &m_str[m_pos];
        m_pos += headlen;
        cur += headlen;
        if (m_pos + fieldlen > m_str.length())
        {
            return false;
        }
        char tmp[128];
        memcpy(tmp, cur, fieldlen);
        tmp[fieldlen] = '\0';
        f = atof(tmp);
        m_pos += fieldlen;
        return true;
    }

    bool MyProtocolStream::getDouble(double &d)
    {
        size_t headlen;
        size_t fieldlen;
        if (!readLengthWithoutOffset(headlen, fieldlen))
        {
            return false;
        }
        // user buffer is not enough
        char *cur = &m_str[m_pos];
        cur += headlen;
        m_pos += headlen;
        if (m_pos + fieldlen > m_str.length())
        {
            return false;
        }
        char tmp[128];
        memcpy(tmp, cur, fieldlen);
        tmp[fieldlen] = '\0';
        d = atof(tmp);
        m_pos += fieldlen;
        return true;
    }

    // 读取一个数，通过7bit压缩算法
    //@handlen 该数的长度
    //@outlen 该数值
    bool MyProtocolStream::readLengthWithoutOffset(size_t &headlen, size_t &outlen)
    {
        headlen = 0;
        const char *temp = &m_str[m_pos];
        char buf[5];
        memcpy(buf, temp, sizeof(buf));
        for (size_t i = 0; i < sizeof(buf); i++)
        {
            headlen++;
            if ((buf[i] & 0x80) == 0x00)
                break;
        }
        if (m_pos + headlen > m_str.length())
            return false;

        unsigned int value;
        read7BitEncoded(buf, headlen, value);
        outlen = value;
        return true;
    }

    bool MyProtocolStream::readLength(size_t &outlen)
    {
        size_t headlen;
        if (!readLengthWithoutOffset(headlen, outlen))
        {
            return false;
        }
        m_pos += headlen;
        return true;
    }

    bool MyProtocolStream::getInt64(int64_t &i)
    {
        if (m_pos + sizeof(int64_t) > m_str.length())
            return false;
        char *p = &m_str[m_pos];
        memcpy(&i, p, sizeof(int64_t));
        i = ntohll(i);
        m_pos += sizeof(int64_t);
        return true;
    }

    bool MyProtocolStream::getInt32(int32_t &i)
    {
        if (m_pos + sizeof(int32_t) > m_str.length())
            return false;
        char *p = &m_str[m_pos];
        memcpy(&i, p, sizeof(int32_t));
        i = qbswap((int)i);
        //i = ntohl(i);
        m_pos += sizeof(int32_t);
        return true;
    }

    bool MyProtocolStream::getShort(short &s)
    {
        if (m_pos + sizeof(short) > m_str.length())
            return false;
        char *p = &m_str[m_pos];
        memcpy(&s, p, sizeof(short));
        s = qbswap(s);
        //s = ntohs(s);
        m_pos += sizeof(short);
        return true;
    }

    bool MyProtocolStream::getChar(char &c)
    {
        if (m_pos + sizeof(char) > m_str.length())
            return false;
        c = m_str[m_pos];
        m_pos += sizeof(char);
        return true;
    }

	
    bool MyProtocolStream::getBool(bool &c)
    {
        if (m_pos + sizeof(bool) > m_str.length())
            return false;
        char x = 0;
		x = m_str[m_pos];
		c = x == 1 ? true : false;
        m_pos += sizeof(bool);
        return true;
	}

    size_t MyProtocolStream::getAll(char *szBuffer, size_t iLen) const
    {
        size_t iRealLen = std::min(iLen, m_str.length());
        memcpy(szBuffer, m_str.c_str(), iRealLen);
        return iRealLen;
    }

    const char *MyProtocolStream::getData() const
    {
        return &m_str[0];
    }

    void MyProtocolStream::flush()
    {
        char *ptr = &m_str[0];
        int ulen = qbswap((int)m_str.length());
        //unsigned int ulen = htonl(m_str.length());
        memcpy(ptr, &ulen, sizeof(ulen));
		if (m_str.length() > 6) {
			unsigned char* s = (unsigned char*)m_str.c_str() + 6;
			unsigned short crc = checksum(s, m_str.length() - 6);
			memcpy(ptr + 4, &crc, sizeof(crc));
		}
    }

    void MyProtocolStream::clear()
    {
        m_str.clear();
        m_str.append(PACKET_LENGTH + CHECKSUM_LENGTH, 0);
        m_pos = PACKET_LENGTH + CHECKSUM_LENGTH;
    }

    int MyProtocolStream::size() const
    {
        return m_str.length();
    }
    // 是否该流没有
    bool MyProtocolStream::empty() const
    {
        return m_str.length() <= PACKET_LENGTH + CHECKSUM_LENGTH;
    }
    // 是否解析完
    bool MyProtocolStream::isEnd() const
    {
        return m_pos >= m_str.length();
    }
    // 返回到某个之前的解析位置
    void MyProtocolStream::setPos(int pos)
    {
        m_pos = pos + PACKET_LENGTH + CHECKSUM_LENGTH;
    }
    // 截断
    void MyProtocolStream::trucate(int pos)
    {
        m_str.erase(pos + PACKET_LENGTH + CHECKSUM_LENGTH);
        if (m_pos > m_str.length())
        {
            m_pos = 0;
        }
    }

    MyProtocolStream& MyProtocolStream::operator<<(const std::string &str) {
        loadString(str);
        return *this;
    }
	
    MyProtocolStream& MyProtocolStream::operator<<(const char* str) {
        std::string c = str;
		loadString(str);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(float f) {
        loadFloat(f);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(double d) {
        loadDouble(d);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(int64_t i) {
        loadInt64(i);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(int32_t i) {
        loadInt32(i);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(short s) {
        loadShort(s);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator<<(char c) {
        loadChar(c);
        return *this;
    }
    MyProtocolStream &MyProtocolStream::operator<<(bool c)
    {
        loadBool(c);
        return *this;
    }
    MyProtocolStream &MyProtocolStream::operator<<(Endl endl)
    {
        flush();
        return *this;
    }
    MyProtocolStream &MyProtocolStream::operator>>(std::string &str)
    {
        getString(str);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(float& f) {
        getFloat(f);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(double& d) {
        getDouble(d);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(int64_t& i) {
        getInt64(i);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(int32_t& i) {
        getInt32(i);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(short& s) {
        getShort(s);
        return *this;
    }
    MyProtocolStream& MyProtocolStream::operator>>(char& c) {
        getChar(c);
        return *this;
    }
    MyProtocolStream &MyProtocolStream::operator>>(bool &c)
    {
        getBool(c);
        return *this;
    }

} // end of namespace net
