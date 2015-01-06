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

#ifndef LIBAIREGISTRY_REQUEST_HH
#define LIBAIREGISTRY_REQUEST_HH

#include <string>
#include <AIRegistry/commands.hh>
#include <KNM/base/KError.hh>
#include <KNM/net/KSocket.hh>
#include <KNM/net/KSocket_pool.hh>

using namespace std;
using namespace KNM;

namespace AIRegistry
{
	/**
	 * Registry request packet.
	 * Wrap client <-> server requests.
	 */
	class request
	{
	public:
		request();														/**< Default constructor. */
		request(const request &);							/**< Copy constructor. */
		request &operator=(const request &);	/**< Assignment operator. */
		request(KSocket *);										/**< Construct with a socket. */
		void reset();													/**< Reset to initial state. */
		~request();														/**< Destructor. */

		// Configuration
		void 	set_sock(KSocket *);						/**< Set socket. */
		void 	flush();												/**< Clear buffer. */

		// Packet handling
		void 	set(enum commands,
					const string &,
					const string & = "");						/**< Set request content. */
		bool 	send();													/**< Send a request. */
		bool 	receive();											/**< Receive a request. */

		// Result handling
		enum commands get_command();					/**< Return command. */
		const string 	&get_path();						/**< Return path to access. */
		const string 	&get_data();						/**< Return data to use. */

	private:
		KSocket 				*sock;								/**< Socket. */
		enum commands 	command;							/**< Request type. */
		string 					path;									/**< Path to access / create. */
		string 					data;									/**< Data to insert / update. */
	};
}

#endif
