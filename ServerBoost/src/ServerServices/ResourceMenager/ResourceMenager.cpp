#include "ServerServices/ResourceMenager/ResourceMenager.h"



ResourceMenager::ResourceMenager(boost::asio::io_context& ioC) : m_connectionQueue(ConnectionsQueue::create()),
																 m_ioContext(ioC)
{

}

ResourceMenager::ResourceMenager(boost::asio::io_context& ioC, std::shared_ptr<ConnectionsQueue> connQueue) :	m_ioContext(ioC),
																												m_connectionQueue(connQueue)
{

}

ResourceMenager::~ResourceMenager()
{

}

std::shared_ptr<ConnectionsQueue> ResourceMenager::getConnectionQueue()
{
	return this->m_connectionQueue;
}

void ResourceMenager::createNewWorker()
{
	m_connectionWorkers.push_back(ConnectionWorker(m_connectionQueue,m_ioContext));
	m_connectionWorkers.back().startThread();
}

void ResourceMenager::monitorWorkersStatus()
{
	while (1) {
		for (auto& a : m_connectionWorkers) {
			
		}
	}
}