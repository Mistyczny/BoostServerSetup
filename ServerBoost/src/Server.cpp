#include "Server.h"

Server::Server() : m_ioContext{}, m_connectionAcceptor(m_ioContext)
{
	this->setupConnectionQueueUsers();
}

Server::~Server()
{

}

void Server::setupConnectionQueueUsers()
{
	std::shared_ptr<ConnectionsQueue> connectionQueue(ConnectionsQueue::create());
	this->setupResourceMenager(connectionQueue);
	m_connectionAcceptor.assignConnectionQueue(connectionQueue);
}

void Server::setupResourceMenager(std::shared_ptr<ConnectionsQueue> queuePtr)
{
	std::thread resourceThread(resourceMenagerThread, queuePtr, std::ref(m_ioContext));
	resourceThread.detach();
}

void Server::start()
{
	m_connectionAcceptor.serviceStart();
}

void Server::run()
{
	m_ioContext.run();
}