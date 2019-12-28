#include "ServerServices/Resources/ConnectionWorker.h"

void workerMain(bool& working,int& liveConnections,boost::asio::io_context& ioC,std::shared_ptr<ConnectionsQueue> connectionQueue)
{
	while (1) {
		if (liveConnections <= 50) {
			std::shared_ptr<ConnectionHandler> newHandler = ConnectionHandler::create(ioC,liveConnections);
			connectionQueue->pushNewConnection(newHandler);
			++liveConnections;
		}
	}
}

ConnectionWorker::ConnectionWorker(std::shared_ptr<ConnectionsQueue> connectionQueuePtr, boost::asio::io_context& ioC) :	m_liveConnections{0},
																															m_connectionQueue(connectionQueuePtr), 
																															m_working(true),
																															m_ioContext(ioC)
{

}

ConnectionWorker::~ConnectionWorker()
{
	m_liveConnections--;
}

void ConnectionWorker::startThread()
{
	std::thread workingThread(workerMain,std::ref(m_working),std::ref(m_liveConnections), std::ref(m_ioContext), m_connectionQueue);
	workingThread.detach();
}
