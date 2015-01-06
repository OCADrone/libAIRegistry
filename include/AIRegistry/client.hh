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
