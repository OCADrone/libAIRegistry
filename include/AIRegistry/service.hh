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
		server();
		void init();
		void reset();
		~server();

	private:
		KTree<string>	regtree;
		KSocket 		lsock;
		KSocket 		*csock;

	};
}

#endif