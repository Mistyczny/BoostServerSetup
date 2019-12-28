#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include "ConnectionHandler/ConnectionHandler.h"
#include "ServerServices/Resources/ConnectionsQueue.h"

using namespace std::chrono_literals;

class ConnectionWorker
{
	private:
		bool m_working;
		int m_liveConnections;
		std::shared_ptr<ConnectionsQueue> m_connectionQueue;
		boost::asio::io_context& m_ioContext;
	public:
		ConnectionWorker(std::shared_ptr<ConnectionsQueue>, boost::asio::io_context&);
		~ConnectionWorker();

		void startThread();
		int getLiveConnectionNumber();
};

