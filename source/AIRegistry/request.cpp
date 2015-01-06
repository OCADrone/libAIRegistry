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

#include <AIRegistry/request.hh>

using namespace std;
using namespace KNM;
using namespace AIRegistry;

request::request()
{
	command = CTRL;
	sock 	= NULL;
}

/**
 * @param _ref Reference to copy from.
 */
request::request(const request &_ref)
{
	if (&_ref != this)
	{
		*this = _ref;
	}
}

/**
 * @param _ref Reference to copy from.
 */
request	&request::operator=(const request &_ref)
{
	if (&_ref != this)
	{
		reset();
		this->sock 		= _ref.sock;
		this->command = _ref.command;
		this->path 		= _ref.path;
		this->data 		= _ref.data;
	}
	return *(this);
}

/**
 * @param _sock Socket to use.
 */
request::request(KSocket *_sock)
{
	command = CTRL;
	sock 	= _sock;
}

void 	request::reset()
{
	if (sock){sock->close();}
	command = CTRL;
	path 	= "";
	data 	= "";
}

request::~request()
{
	if (sock){sock->close();}
}

/**
 * @param _sock Socket to use.
 */
void 	request::set_sock(KSocket *_sock)
{
	sock = _sock;
}

void 			request::flush()
{
	path    = "";
	data    = "";
	command = CTRL;
}

/**
 * @param _cmd Command to perform.
 * @param _path To to access or create.
 * @param _data Data to insert.
 */
void 	request::set(enum commands _cmd, const string &_path, const string &_data)
{
	command = _cmd;
	path 	  = _path;
	data 	  = _data;
}

bool 	request::send()
{
	if (sock)
	{
		try
		{
			sock->send((int)command);
			sock->send(path.size());
			sock->send(data.size());
			if (path.size() > 0) {sock->send(path);}
			if (data.size() > 0) {sock->send(data);}
		}
		catch (const KError &error)
		{
			//error.dump();
			return false;
		}
		return true;
	}
	return false;
}

bool 	request::receive()
{
	size_t 	path_len = 0;
	size_t 	data_len = 0;
	char 	*buffer  = NULL;

	if (sock)
	{
		try
		{
			sock->receive((int*)&command);
			sock->receive((int*)&path_len);
			sock->receive((int*)&data_len);

			if (path_len > 0)
			{
				buffer = new char[path_len + 1];
				memset(buffer, 0, path_len + 1);
				sock->receive(buffer, path_len);
				path.assign(buffer);
				delete[] buffer;
			}

			if (data_len > 0)
			{
				buffer = new char[data_len + 1];
				memset(buffer, 0, data_len + 1);
				sock->receive(buffer, data_len);
				data.assign(buffer);
				delete[] buffer;
			}
		}
		catch (const KError &error)
		{
			//error.dump();
			return false;
		}
		return true;
	}
	return false;
}

enum commands 	request::get_command()
{
	return command;
}

const string 	&request::get_path()
{
	return path;
}

const string 	&request::get_data()
{
	return data;
}
