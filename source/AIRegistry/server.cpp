#include <iostream>
#include <AIRegistry/server.hh>

using namespace std;
using namespace AIRegistry;

server::server()
{
	init();
}

server::server(KSocket *_csock)
{
	init();
	csock = _csock;
}

server::server(KTree<string> *_regtree, KMutex *_reglock)
{
	init();
	regtree = _regtree;
	reglock = _reglock;
}

server::server(KSocket *_csock,
			   KTree<string> *_regtree, KMutex *_reglock)
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

void 	server::set_client(KSocket *_csock)
{
	csock = _csock;
}

void 	server::set_regtree(KTree<string> *_regtree)
{
	regtree = _regtree;
}

void 	server::set_reglock(KMutex *_reglock)
{
	reglock = _reglock;
}

void 	*server::tmain(void __attribute__((unused))*_args)
{
	if (!csock || !regtree || !reglock)
		return NULL;

	try
	{
		csock->set_nagle(false);
		creq.set_sock(csock);
		cans.set_sock(csock);

		while (1)
		{
			if (!creq.receive() ) {break;}
			handle();
			if (!cans.send() ) {break;}
		}
	}
	catch(const KError &error)
	{
		//error->dump();
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

	switch (creq.get_command())
	{
		case CTRL:
			cans.set(true, "");
			break;
		case READ:
			reglock->lock();
			try
			{
				cans.set(true, *(regtree->find( creq.get_path() ) ) );
			}
			catch (const KError &error)
			{
				cans.set(false, "key not found");
			}
			reglock->unlock();
			break;
		case WRITE:
			reglock->lock();
			regtree->insert(creq.get_path(), /**(new string(*/creq.get_data()/*))*/);
			reglock->unlock();
			cans.set(true, "");
			break;
		case MKNODE:
			reglock->lock();
			regtree->mknode(creq.get_path());
			cans.set(true, "");
			reglock->unlock();
			break;
		case CHECK:
			cans.set(true, "");
			break;
		default:
			cans.set(false, "No such command");
	}
}
