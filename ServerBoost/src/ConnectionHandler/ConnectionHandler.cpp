#include "ConnectionHandler/ConnectionHandler.h"

std::shared_ptr<ConnectionHandler> ConnectionHandler::create(boost::asio::io_context& io_context,int& liveConnections)
{
	std::shared_ptr<ConnectionHandler> new_(new ConnectionHandler(io_context, liveConnections));
	return new_;
}

ConnectionHandler::ConnectionHandler(boost::asio::io_context& io_context,int& liveConnections) :	m_writeStrand(io_context),
																									m_socket(io_context),
																									m_connectionID(liveConnections)
{
	std::cout << "CREATE HANDLER" << std::endl;
}

ConnectionHandler::~ConnectionHandler()
{
	std::cout << "END" << std::endl;
	--m_connectionID;
}

void ConnectionHandler::start()
{
	this->readPacket();
}

void ConnectionHandler::readPacket()
{
	m_inputPacket.consume(m_inputPacket.size());
	boost::asio::async_read_until(m_socket, m_inputPacket, '\n', [this, me = shared_from_this()]
	(boost::system::error_code const& err, std::size_t bytes){me->readPacketDone(err, bytes); });
}

void ConnectionHandler::readPacketDone(boost::system::error_code const& err, std::size_t bytes)
{
	if (err) { return; }

	std::istream stream(&m_inputPacket);
	std::string packetString;
	stream >> packetString;
	std::cout << packetString << std::endl;
	this->readPacket();
}

void ConnectionHandler::queueMessage(std::string message)
{
	bool writeProcessing = !m_packetToSendQueue.empty();
	this->pushMessageToQueue(message);
	if (!writeProcessing) {
		startPacketSending();
	}
}

void ConnectionHandler::pushMessageToQueue(std::string message)
{
	m_packetToSendQueue.push_back(std::move(message));
}

void ConnectionHandler::startPacketSending()
{
	m_packetToSendQueue.front() += "\n";
	boost::asio::async_write(m_socket, boost::asio::buffer(m_packetToSendQueue.front()),
		m_writeStrand.wrap([me = shared_from_this()](boost::system::error_code const& er, std::size_t){
		me->packetSendDone(er);
	}));
}

void ConnectionHandler::packetSendDone(boost::system::error_code const& error)
{
	if (!error) {
		m_packetToSendQueue.pop_front();
		if (!m_packetToSendQueue.empty()) {
			this->startPacketSending();
		}
	}
}