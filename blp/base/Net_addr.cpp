#include "Net_addr.h"

using namespace blp;

CNetAddr::CNetAddr()
{

}

CNetAddr::CNetAddr(uint32_t ip, uint16_t port)
{

}

CNetAddr::CNetAddr(const std::string& ip, uint16_t port)
{

}

const char* CNetAddr::getLocalIp(const char* ip)
{
	return NULL;
}

void CNetAddr::initAddr(uint32_t ip, uint16_t port)
{

}

uint32_t CNetAddr::getAddr() const
{
	return 0;
}

const char* CNetAddr::getHost() const
{
	return NULL;
}

uint16_t CNetAddr::getPort() const
{
	return _port;
}

CNetAddr::CNetAddr(const CNetAddr&)
{

}
/*
CNetAddr operator=(const CNetAddr&)
{

}

bool CNetAddr::opreator()(const CNetAddr& left, const CNetAddr& right) const
{
	return true;
}
bool CNetAddr::opreator==(const CNetAddr& right) const
{
	return true;
}
*/

/*
#include "c2cplatform/library/net/c2c_inet_addr.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace c2cplatform::library::net;

char CInterAddr::s_sBuffer[20];

void CInterAddr::InitAddr(uint32_t dwIpAddress, uint16_t wPort)
{
    m_dwIpAddress = dwIpAddress;
    m_wPort       = wPort;
    memset(this->m_sBuffer, 0, sizeof(m_sBuffer));

    struct in_addr in;
	in.s_addr = dwIpAddress;
	char *p = inet_ntoa(in);
	if (p != NULL)
    {
        snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", p);
    }
}


CInterAddr::CInterAddr()
{
    InitAddr(0, 0);
}

CInterAddr::CInterAddr(uint32_t dwIpAddress, uint16_t wPort)
{
    InitAddr(dwIpAddress, wPort);
}

CInterAddr::CInterAddr(const std::string& strIpAddress, uint16_t wPort)
{
    uint32_t dwIpAddress = inet_addr(strIpAddress.c_str());
    //CInterAddr(dwIpAddress, wPort);
    InitAddr(dwIpAddress, wPort);
}

uint32_t CInterAddr::getAddress() const
{
    return this->m_dwIpAddress;
}

const char *CInterAddr::getHost() const
{

    return m_sBuffer;
}

uint16_t CInterAddr::getPort() const
{
    return m_wPort;
}

CInterAddr::CInterAddr(const CInterAddr &rhs)
{
    m_dwIpAddress = rhs.getAddress();
    m_wPort       = rhs.getPort();
    snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", rhs.getHost());
}

CInterAddr CInterAddr::operator =(const CInterAddr &rhs)
{
    if (this != &rhs)
    {
        m_dwIpAddress = rhs.getAddress();
	m_wPort       = rhs.getPort();
	snprintf(m_sBuffer, sizeof(m_sBuffer), "%s", rhs.getHost());
	return *this;
    }
    return rhs;
}

//scott added this for sort criteria
bool CInterAddr::operator()(const CInterAddr& left, const CInterAddr& right) const
{
    return (*this) < right;
}

//scott added this for comparing
bool CInterAddr::operator<(const CInterAddr& right) const
{
    if((*this).getAddress() < right.getAddress())
	return true;
    if((*this).getAddress() == right.getAddress() &&
	    (*this).getPort() < right.getPort())
	return true;

    return false;
}

//scott added this for cmparing
bool CInterAddr::operator==(const CInterAddr& right) const
{
    return (*this).getAddress() == right.getAddress() &&
	(*this).getPort() == right.getPort();
}


const char* CInterAddr::GetLocalIP(const char* pszIP)
{
    int iClientSockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(iClientSockfd < 0 )
    {
        printf("Client, Create socket failed");
        return NULL;
    }
    
    struct sockaddr_in stINETAddr;
	if(pszIP)
		stINETAddr.sin_addr.s_addr = inet_addr(pszIP);
	else
		stINETAddr.sin_addr.s_addr = inet_addr("192.168.0.1");
    stINETAddr.sin_family = AF_INET;
    stINETAddr.sin_port = htons(8888);
    
    int iCurrentFlag = fcntl(iClientSockfd, F_GETFL, 0);
    fcntl(iClientSockfd, F_SETFL, iCurrentFlag | FNDELAY);
    
    connect(iClientSockfd, (struct sockaddr *)&stINETAddr, sizeof(sockaddr));
    
    struct sockaddr_in stINETAddrLocal;
    socklen_t iAddrLenLocal = sizeof(stINETAddrLocal);
    getsockname(iClientSockfd, (struct sockaddr *)&stINETAddrLocal, &iAddrLenLocal);
	memset(s_sBuffer, 0, sizeof(s_sBuffer));
	strncpy(s_sBuffer, inet_ntoa(stINETAddrLocal.sin_addr), sizeof(s_sBuffer));
    
    return s_sBuffer;
}


 */