#include <AIRegistry/client.hh>

using namespace std;
using namespace AIRegistry;

client::client()
{
	init();
}

client::client(KSocket *_hsock)
{
	init();
	hsock    = _hsock;
	selfsock = false;
}

client::client(const string &_address, int _port)
{
	init();
	hsock    = new KSocket(KSocket::TCP4, _address, _port);
	selfsock = true;
}

void 	client::reset()
{
	try
	{
		hsock->disconnect();
	}
	catch(const KError &error)
	{}

	if (selfsock && hsock)
		delete hsock;
}

client::~client()
{
	reset();
}

void 	client::set_server(KSocket *_hsock)
{
	if (hsock && selfsock)
		reset();
	hsock = _hsock;
}

void 	client::set_server(const string &_address, int _port)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_address(_address);
	hsock->set_port(_port);
}

void 	client::set_address(const string &_address)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_address(_address);
}

void 	client::set_port(int _port)
{
	if (!hsock)
		hsock = new KSocket(KSocket::TCP4);

	hsock->set_port(_port);
}

void 	client::connect()
{
	if (hsock)
	{
		hsock->connect();
		hsock->set_nagle(false);
		cans.set_sock(hsock);
		creq.set_sock(hsock);
	}
	else
		throw KError("AIRegistry::client::connect", "socket not initialized");
}

void 	client::disconnect()
{
	if (hsock)
		hsock->disconnect();
	else
		throw KError("AIRegistry::client::disconnect", "socket not initialized");
}

const string 	&client::query(enum commands _cmd, const string &_path,
							   const string &_data)
{
	if (hsock)
	{
		try
		{
			creq.set(_cmd, _path, _data);
			creq.send();
			cans.receive();
			if (cans.get_state())
				result = cans.get_data();
			else
				result = "";
		}

		catch (const KError &error)
		{
			//error->dump();
			disconnect();
		}

	}
	else
		throw KError("Client::query()", "connection is not configured");

	cans.flush();
	creq.flush();
	return result;
}

void 	client::init()
{
	hsock    = NULL;
	selfsock = false;
}
