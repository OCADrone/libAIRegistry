#include <iostream>
#include <AIRegistry/server.hh>

using namespace std;
using namespace AIRegistry;

server::server()
{
	init();
}

/**
 * @param _csock Client socket to use.
 */
server::server(KSocket *_csock)
{
	init();
	csock = _csock;
}

/**
 * @param _regtree Tree database to use.
 * @param _reglock Tree mutex.
 */
server::server(KTree<string> *_regtree,
							 KMutex *_reglock)
{
	init();
	regtree = _regtree;
	reglock = _reglock;
}

/**
 * @param _csock Client socket to use.
 * @param _regtree Tree database to use.
 * @param _reglock Tree mutex.
 */
server::server(KSocket *_csock,
			   			 KTree<string> *_regtree,
							 KMutex *_reglock)
{
	init();
	csock   = _csock;
	regtree = _regtree;
	reglock = _reglock;
}

server::~server()
{
	if (csock){csock->disconnect();}
}

/**
 * @param _csock Client socket to use.
 */
void 	server::set_client(KSocket *_csock)
{
	csock = _csock;
}

/**
 * @param _regtree Tree database to use.
 */
void 	server::set_regtree(KTree<string> *_regtree)
{
	regtree = _regtree;
}

/**
 * @param _reglock Tree mutex.
 */
void 	server::set_reglock(KMutex *_reglock)
{
	reglock = _reglock;
}

/**
 * @param _args Thread arguments.
 */
void 	*server::tmain(void __attribute__((unused))*_args)
{
	if (!csock || !regtree || !reglock)
		return NULL;

	try
	{
		csock->set_nagle(false);	// Disable TCP nagle (nagle buffer is slow)
		creq.set_sock(csock);			// Set request object socket
		cans.set_sock(csock);			// Set answer object socket

		// Loop: receive request, compute, send answer.
		while (1)
		{
			if (!creq.receive() ) {break;}
			handle();
			if (!cans.send() ) {break;}
		}
	}
	catch(const KError &error)
	{
		// Process is autonomous, if error happens, thread stop.
		// There is no need to throw an error from here.
		//error.dump();
	}

	return NULL;
}

void 	*server::tend()
{
	return NULL;
}

void 	server::init()
{
	csock   = NULL;
	regtree = NULL;
	reglock = NULL;
}

void 	server::handle()
{
	string 	buffer;
	size_t 	leafs;
	size_t 	nodes;

	switch (creq.get_command())
	{
		/**
		 * CONTROL
		 * -------
		 */
		case CTRL:
			cans.set(true, "");
			break;

		/**
		 * READ KEY
		 * --------
		 */
		case READ:
			//reglock->lock();
			try
			{
				cans.set(true, *(regtree->find( creq.get_path() ) ) );
			}
			catch (const KError &error)
			{
				cans.set(false);
			}
			//reglock->unlock();
			break;

		/**
		 * UPDATE KEY VALUE
		 * ----------------
		 */
		case WRITE:
			//reglock->lock();
			regtree->insert(creq.get_path(), creq.get_data());
			//reglock->unlock();
			cans.set(true);
			break;

		/**
		 * CREATE NODE
		 * -----------
		 */
		case MKNODE:
			//reglock->lock();
			try
			{
				regtree->mknode(creq.get_path());
				cans.set(true);
			}
			catch(const KError &error)
			{
				cans.set(false, error.what());
			}
			//reglock->unlock();
			break;

		/**
		 * CREATE LEAF
		 * -----------
		 */
		case MKLEAF:
			try
			{
				regtree->mkleaf(creq.get_path());
				cans.set(true);
			}
			catch(const KError &error)
			{
				cans.set(false, error.what());
			}
			break;


		/**
		 * CHECK IF NODE EXISTS
		 * --------------------
		 */
		case ISNODE:
			if (regtree->is_node(creq.get_path()))
				cans.set(true);
			else
				cans.set(false);
			break;

		/**
		 * CHECK IF LEAF EXISTS
		 * --------------------
		 */
		case ISLEAF:
			if (regtree->is_leaf(creq.get_path()))
				cans.set(true);
			else
				cans.set(false);
			break;

		/**
		 * SIZE
		 * ----
		 */
		case SIZE:
			if (regtree->is_node(creq.get_path()))
			{
				tie(nodes, leafs) = regtree->size(creq.get_path());
				cans.set(true, *KUtils::to_string((int)nodes) + ", " + *KUtils::to_string((int)leafs));
			}
			else
			{
				cans.set(false);
			}
			break;

		/**
		 * UNKNOWN COMMAND
		 * ---------------
		 */
		default:
			cans.set(false);
	}
}
