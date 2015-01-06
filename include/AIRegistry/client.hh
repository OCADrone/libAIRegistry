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

#ifndef LIBAIREGISTRY_CLIENT_HH
#define LIBAIREGISTRY_CLIENT_HH

#include <string>
#include <KNM/base.hh>
#include <KNM/sync.hh>
#include <KNM/net.hh>
#include <KNM/data/KTree.hpp>
#include <AIRegistry/request.hh>
#include <AIRegistry/answer.hh>

using namespace std;
using namespace KNM;

namespace AIRegistry
{
	/**
	 * Connect to a registry server.
	 * Contains necessary objects (request, answer, socket, ...) to
	 * handle conection by itself.
	 */
	class 	client
	{
	public:
		client();
		client(KSocket *);										/**< Build with existing socket. */
		client(const string &, int = 0);			/**< Build with socket parameters. */
		void reset();													/**< Reset initial state. */
		~client();														/**< Destructor. */

		// Setting
		void 	set_server(KSocket *);					/**< Set server from a socket. */
		void 	set_server(const string &,
						   			 int = 0);						/**< Set server connection. */
		void 	set_address(const string &);		/**< Set server address. */
		void 	set_port(int);									/**< Set server port. */

		// Connection
		void 	connect();														/**< Connect to server. */
		void 	disconnect();													/**< Close server link. */
		const string &query(enum commands,
					  						const string &,
					  						const string & = "");		/**< Send a command. */
		bool 				 get_state();										/**< Return last query state. */
		const string &get_data();										/**< Return last query result. */

	private:
		void 			init();						/**< Initialize object. */

		KSocket 		*hsock;					/**< Server (Host) link. */
		bool 				selfsock;				/**< true if socket is self managed. */
		request 		creq;						/**< Last send request. */
		answer 			cans;						/**< Last received answer. */
		string 			result;					/**< Recived result. */
	};
}

#endif
