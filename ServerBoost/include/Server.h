#pragma once
#include <boost/asio.hpp>
#include "ServerServices/ConnectionAcceptor.h"
#include "ServerServices/ResourceMenager/ResourceMenagerThreadMain.h"
#include "ServerServicesStatus.h"

class Server
{
	private:
		boost::asio::io_context m_ioContext;
		ConnectionAcceptor m_connectionAcceptor;
	public:
		Server();
		~Server();

		void setupConnectionQueueUsers();
		void setupResourceMenager(std::shared_ptr<ConnectionsQueue> queuePtr);
		void start();
		void run();
};

