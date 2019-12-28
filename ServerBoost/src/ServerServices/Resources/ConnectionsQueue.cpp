#include "ServerServices/Resources/ConnectionsQueue.h"

std::shared_ptr<ConnectionsQueue> ConnectionsQueue::create()
{
	std::shared_ptr<ConnectionsQueue> new_(new ConnectionsQueue());
	return new_;
}

ConnectionsQueue::ConnectionsQueue()
{
	std::cout << "CREATED MUTEX" << std::endl;
}

ConnectionsQueue::~ConnectionsQueue()
{
	std::cout << "MUTEX DIED" << std::endl;
}

void ConnectionsQueue::pushNewConnection(std::shared_ptr<ConnectionHandler> connection)
{
	std::scoped_lock locker(m_queueLocker);
	m_connectionsQueue.push(connection);
}

void ConnectionsQueue::removeEstablishedConnection()
{
	std::scoped_lock locker(m_queueLocker);
	if (!m_connectionsQueue.empty()) {
		m_connectionsQueue.pop();
	}
}

std::shared_ptr<ConnectionHandler> ConnectionsQueue::getConnection()
{
	std::scoped_lock locker(m_queueLocker);
	if (m_connectionsQueue.empty()) return nullptr;
	return m_connectionsQueue.front();
}

bool ConnectionsQueue::queueEmpty()
{
	return m_connectionsQueue.empty();
}