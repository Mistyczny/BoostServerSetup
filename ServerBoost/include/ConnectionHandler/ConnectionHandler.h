#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <array>
#include <future>
#include <deque>
#include <boost/bind.hpp>

class ConnectionHandler : public std::enable_shared_from_this<ConnectionHandler>
{
	private:
		ConnectionHandler(boost::asio::io_context&,int&);
		int& m_connectionID;
		boost::asio::io_context::strand m_writeStrand;
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::streambuf m_inputPacket;
		std::deque<std::string> m_packetToSendQueue;
	public:
		static std::shared_ptr<ConnectionHandler> create(boost::asio::io_context&, int&);
		~ConnectionHandler();
		boost::asio::ip::tcp::socket& getSocket() { return m_socket; }

		void start();
		void readPacket();
		void readPacketDone(boost::system::error_code const& err, std::size_t bytes);

		void queueMessage(std::string);
		void pushMessageToQueue(std::string);
		void startPacketSending();
		void packetSendDone(boost::system::error_code const& error);
};

