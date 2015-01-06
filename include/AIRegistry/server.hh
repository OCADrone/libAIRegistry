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

#ifndef LIBAIREGISTRY_SERVER_HH
#define LIBAIREGISTRY_SERVER_HH

#include <KNM/sync/KThread.hpp>
#include <KNM/sync/KMutex.hh>
#include <KNM/data/KTree.hpp>
#include <KNM/net.hh>
#include <AIRegistry/request.hh>
#include <AIRegistry/answer.hh>

using namespace KNM;

namespace AIRegistry
{
	/**
	 * Dialog with a ::client.
	 * Network bridge between a registry client and
	 * an registry tree.
	 */
	class 	server: public KThread
	{
	public:
		server();
		server(KSocket *);												/**< Construct with socket. */
		server(KTree<string> *, KMutex * = NULL);	/**< Construct with a DB link. */
		server(KSocket*, KTree<string> *,
			   	 KMutex * = NULL); 									/**< Construct with sock & DB. */
		void reset();															/**< Reset initial state. */
		~server();																/**< Destructor. */

		void 	set_client(KSocket *);							/**< Set client socket. */
		void 	set_regtree(KTree<string> *);				/**< Set DB link. */
		void 	set_reglock(KMutex *);							/**< Set DB mutex. */

	private:
		void 			init();													/**< Initialize object. */
		void 			*tmain(void * = NULL);					/**< Start thread. */
		void 			*tend();												/**< Stop thread. */
		void  		handle();												/**< Process last request. */

		KSocket 			*csock;											/**< Client socket. */
		KTree<string>	*regtree;										/**< DB link. */
		KMutex 				*reglock;										/**< DB mutex. */
		request 			creq;												/**< Client last request. */
		answer				cans;												/**< Last answer to send. */
	};
}

#endif
