#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include "ConnectionHandler/ConnectionHandler.h"
#include "ServerServices/Resources/ConnectionWorker.h"
#include "ServerServices/Resources/ConnectionsQueue.h"

class ResourceMenager
{
	private:
		std::shared_ptr<ConnectionsQueue> m_connectionQueue;
		boost::asio::io_context& m_ioContext;
		std::deque<ConnectionWorker> m_connectionWorkers;
	public:
		ResourceMenager(boost::asio::io_context&);
		ResourceMenager(boost::asio::io_context&, std::shared_ptr<ConnectionsQueue>);
		~ResourceMenager();

		std::shared_ptr<ConnectionsQueue> getConnectionQueue();
		void createNewWorker();
		void monitorWorkersStatus();
};

