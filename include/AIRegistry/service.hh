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
