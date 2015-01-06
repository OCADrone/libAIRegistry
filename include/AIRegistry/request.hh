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
