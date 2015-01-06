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

#include <KNM/base.hh>
#include <KNM/net.hh>
#include <KNM/data/KTree.hpp>

namespace AIRegistry
{
	class 	server
	{
	public:
		server();									/**< Constructor. */
		void init();							/**< Initialize. */
		void reset();							/**< Reset initial state. */
		~server();								/**< Destructor. */

	private:
		KTree<string>	regtree;		/**< Database. */
		KSocket 			lsock;			/**< Locket (server) socket. */
		KSocket 			*csock;			/**< Clients socket. */

	};
}

#endif
