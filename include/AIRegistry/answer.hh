#ifndef LIBAIREGISTRY_ANSWER_HH
#define LIBAIREGISTRY_ANSWER_HH

#include <string>
#include <AIRegistry/commands.hh>
#include <KNM/base/KError.hh>
#include <KNM/net/KSocket.hh>

using namespace KNM;

namespace AIRegistry
{
	/**
	 * Registry answer packet.
	 * Wrap client <-> server answers.
	 */
	class answer
	{
	public:
		answer();								/**< Default constructor. */
		answer(const answer &);					/**< Copy constructor. */
		answer &operator=(const answer &);		/**< Assignment operator. */
		answer(KSocket *);						/**< Construct with a connection. */
		void reset();							/**< Reset obect to its initial state. */
		~answer();								/**< Destructor. */

		// Configuration
		void 	set_sock(KSocket *);			/**< Set socket. */
		void 	flush();						/**< Clear buffers. */

		// Packet handling
		void 	set(bool state,
					const string & = "");		/**< Set request content. */
		bool 	send();							/**< Send a request. */
		bool 	receive();						/**< Receive a request. */

		// Result handling
		bool 			get_state();			/**< Return last command state. */
		const string 	&get_data();			/**< Return last command data. */

	private:
		KSocket 	*sock;						/**< Socket. */
		bool 		state;						/**< Command execution state. */
		string 		data;						/**< Answer data / failure message. */
	};
}

#endif
