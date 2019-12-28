#pragma once
#include "ServerServices/ResourceMenager/ResourceMenager.h"

void resourceMenagerThread(std::shared_ptr<ConnectionsQueue> m_connectionQueue, boost::asio::io_context& ioC);

