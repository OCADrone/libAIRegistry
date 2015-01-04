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
	 * Contains a server socket.
	 */
	class 	client
	{
	public:
		client();
		client(KSocket *);							/**< Build with existing server link. */
		client(const string &, int = 0);			/**< Build with server link. */
		void reset();								/**< Reset initial state. */
		~client();									/**< Destructor. */

		void 	set_server(KSocket *);				/**< Set server from a socket. */
		void 	set_server(const string &,
						   int = 0);				/**< Set server link. */
		void 	set_address(const string &);		/**< Set server address. */
		void 	set_port(int);						/**< Set server port. */
		void 	connect();							/**< Connect to server. */
		void 	disconnect();						/**< Close server link. */
		const string &query(enum commands,
					  const string &,
					  const string & = "");			/**< Send a command & return result. */

	private:
		void 			init();						/**< Initialize object. */

		KSocket 		*hsock;						/**< Server (Host) link. */
		bool 			selfsock;					/**< true if socket is self managed. */
		request 		creq;						/**< Last send request. */
		answer 			cans;						/**< Last received answer. */
		string 			result;
	};
}

#endif