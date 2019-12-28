#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <queue>
#include "ConnectionHandler/ConnectionHandler.h"

class ConnectionsQueue
{
	private:
		std::queue<std::shared_ptr<ConnectionHandler>> m_connectionsQueue;
		std::mutex m_queueLocker;
	public:
		static std::shared_ptr<ConnectionsQueue> create();
		ConnectionsQueue();
		~ConnectionsQueue();

		void pushNewConnection(std::shared_ptr<ConnectionHandler>);
		void removeEstablishedConnection();
		std::shared_ptr<ConnectionHandler> getConnection();
		bool queueEmpty();
};

