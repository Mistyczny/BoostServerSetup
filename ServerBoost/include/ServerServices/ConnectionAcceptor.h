#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <queue>
#include "ConnectionHandler/ConnectionHandler.h"
#include "ServerServices/Resources/ConnectionsQueue.h"
using namespace std::chrono_literals;

class ConnectionAcceptor
{
	private:
		boost::asio::io_context& m_ioContext;
		boost::asio::ip::tcp::acceptor m_acceptor;
		std::shared_ptr<ConnectionsQueue> m_connectionsQueue;
	public:
		ConnectionAcceptor(boost::asio::io_context&, std::shared_ptr<ConnectionsQueue> connectionQueuePtr);
		ConnectionAcceptor(boost::asio::io_context&);
		~ConnectionAcceptor();

		void serviceStart();
		void listen();
		void connectionEstablished(boost::system::error_code const& error);
		void assignConnectionQueue(std::shared_ptr<ConnectionsQueue>);
};

