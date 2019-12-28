#include "ServerServices/ConnectionAcceptor.h"

ConnectionAcceptor::ConnectionAcceptor(boost::asio::io_context& ioC, std::shared_ptr<ConnectionsQueue> connectionQueuePtr) : m_ioContext(ioC),
																															 m_acceptor(m_ioContext),
																															 m_connectionsQueue(connectionQueuePtr)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 8001);
	m_acceptor.open(ep.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(ep);
}

ConnectionAcceptor::ConnectionAcceptor(boost::asio::io_context& ioC) :	m_ioContext(ioC),
																		m_acceptor(m_ioContext)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 8001);
	m_acceptor.open(ep.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(ep);
}

ConnectionAcceptor::~ConnectionAcceptor()
{

}

void ConnectionAcceptor::serviceStart()
{
	m_acceptor.listen();
	this->listen();
}

void ConnectionAcceptor::listen()
{
	if (!m_connectionsQueue->queueEmpty()) {
		m_acceptor.async_accept(m_connectionsQueue->getConnection()->getSocket(), [=](auto errorCode) {
			connectionEstablished(errorCode);
			});
	}
	else {
		std::this_thread::sleep_for(1s);
		this->listen();
	}
}

void ConnectionAcceptor::connectionEstablished(boost::system::error_code const& error)
{
	if (error) { return; }
	m_connectionsQueue->getConnection()->start();
	m_connectionsQueue->removeEstablishedConnection();
	this->listen();
}

void ConnectionAcceptor::assignConnectionQueue(std::shared_ptr<ConnectionsQueue> queue)
{
	this->m_connectionsQueue = queue;
}