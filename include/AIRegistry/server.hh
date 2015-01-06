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
