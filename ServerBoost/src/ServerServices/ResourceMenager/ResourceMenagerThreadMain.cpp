#include "ServerServices/ResourceMenager/ResourceMenagerThreadMain.h"

void resourceMenagerThread(std::shared_ptr<ConnectionsQueue> m_connectionQueue, boost::asio::io_context& ioC)
{
	ResourceMenager m_resourceMenager(ioC, m_connectionQueue);
	m_resourceMenager.createNewWorker();
}