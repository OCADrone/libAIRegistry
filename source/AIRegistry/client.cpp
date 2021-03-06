/*
* libAIRegistry
* Copyright (C) 2015 Jean-Philippe Clipffel
* Email: jp.clipffel@gmail.com
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
* USA
*/

#include <AIRegistry/client.hh>

using namespace std;
using namespace AIRegistry;

client::client()
{
	init();
}

/**
 * @param _hsock Server socket.
 */
client::client(KSocket *_hsock)
{
	init();
	hsock    = _hsock;
	selfsock = false;
}

/**
 * @param _address Server address.
 * @param _port Server port.
 */
client::client(const string &_address, int _port)
{
	init();
	hsock    = new KSocket(KSocket::TCP4, _address, _port);
	selfsock = true;
}

void 	client::reset()
{
	try
	{
		hsock->disconnect();
	}
	catch(const KError &error)
	{}

	if (selfsock && hsock)
		delete hsock;
}

client::~client()
{
	reset();
}

/**
 * @param _hsock Server socket.
 */
void 	client::set_server(KSocket *_hsock)
{
	if (hsock && selfsock)
		reset();
	hsock = _hsock;
}

/**
 * @param _address Server address.
 * @param _port Server port.
 */
void 	client::set_server(const string &_address, int _port)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_address(_address);
	hsock->set_port(_port);
}

/**
 * @param _address Server address.
 */
void 	client::set_address(const string &_address)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_address(_address);
}

/**
 * @param _port Server port.
 */
void 	client::set_port(int _port)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_port(_port);
}

void 	client::connect()
{
	if (hsock)
	{
		hsock->connect();
		hsock->set_nagle(false);
		cans.set_sock(hsock);
		creq.set_sock(hsock);
	}
	else
		throw KError("AIRegistry::client::connect", "socket not initialized");
}

void 	client::disconnect()
{
	if (hsock)
		hsock->disconnect();
	else
		throw KError("AIRegistry::client::disconnect", "socket not initialized");
}

/**
 * @param _cmd Command to send.
 * @param _path Path to operate on.
 * @param _data Data to write / option.
 */
const string 	&client::query(enum commands _cmd, const string &_path,
							   const string &_data)
{
	if (hsock)
	{
		// Clear answer and request buffer
		cans.flush();
		creq.flush();

		try
		{
			creq.set(_cmd, _path, _data);
			creq.send();
			cans.receive();
			if (cans.get_state())
				result = cans.get_data();
			else
				result = "";
		}

		catch (const KError &error)
		{
			//error.dump();
			disconnect();
		}

	}
	else
		throw KError("Client::query()", "connection not etablished");

	return result;
}

bool 	client::get_state()
{
	return cans.get_state();
}

const string &client::get_data()
{
	return result;
}

void 	client::init()
{
	hsock    = NULL;
	selfsock = false;
}
