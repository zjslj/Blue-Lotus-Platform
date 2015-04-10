#ifndef BLP_BASE_NET_ADDR_H
#define BLP_BASE_NET_ADDR_H

#include <string>
#include <stdint.h>

namespace blp
{
class CNetAddr
{
public:
	CNetAddr();
	CNetAddr(uint32_t ip, uint16_t port);
	CNetAddr(const std::string& ip, uint16_t port);

	static const char* getLocalIp(const char* ip = NULL);
public:
	void initAddr(uint32_t ip, uint16_t port);
	uint32_t getAddr() const;
	const char* getHost() const;
	uint16_t getPort() const;

	CNetAddr(const CNetAddr&);
	//CNetAddr operator =(const CNetAddr&);
	//bool operator()(const CNetAddr& left, const CNetAddr& right) const;
	//bool operator==(const CNetAddr& right) const;
private:
	char _buff[20];
	uint32_t _ip;
	uint16_t _port;
	static char _buffer[20];
};
}
#endif