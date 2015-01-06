/*
* @Author        : Jean-Philippe Clipffel
* @Creation date : 2014-06-08 10:26:52
* @Last update   : 2014-06-12 23:44:20
*/

#include <AIRegistry/answer.hh>

using namespace std;
using namespace KNM;
using namespace AIRegistry;

answer::answer()
{
	sock  = NULL;
	state = false;
}

/**
 * @param _ref Reference to copy from.
 */
answer::answer(const answer &_ref)
{
	if (&_ref != this)
		*this = _ref;
}

/**
 * @param _ref Reference to copy from.
 */
answer 	&answer::operator=(const answer &_ref)
{
	if (&_ref != this)
	{
		sock  = _ref.sock;
		state = _ref.state;
		data  = _ref.data;
	}
	return (*this);
}

/**
 * @param _sock Socket to use.
 */
answer::answer(KSocket *_sock)
{
	sock  = _sock;
	state = false;
}

void 	answer::reset()
{
	if (sock){sock->close();}
	state = false;
}

answer::~answer()
{
	if (sock){sock->close();}
}

/**
 * @param _sock Socket to use.
 */
void 	answer::set_sock(KSocket *_sock)
{
	sock = _sock;
}

void 	answer::flush()
{
	state = false;
	data  = "";
}

/**
 * @param _state Set answer state.
 * @param _data Set answer data.
 */
void 	answer::set(bool _state, const string &_data)
{
	state = _state;
	data  = _data;
}

bool 	answer::send()
{
	if (sock)
	{
		try
		{
			sock->send((int)state);
			sock->send((int)data.size());
			if (data.size() > 0) {sock->send(data);}
		}
		catch (const KError &error)
		{
			//error.dump();
			return false;
		}
		return true;
	}
	return false;
}

bool 	answer::receive()
{
	int 	data_len = 0;
	char 	*buffer  = NULL;

	if (sock)
	{
		try
		{
			sock->receive((int*)&state);
			sock->receive((int*)&data_len);

			if (data_len > 0)
			{
				buffer = new char[data_len + 1];
				memset(buffer, 0, data_len + 1);
				sock->receive(buffer, data_len);
				data.assign(buffer);
				delete[] buffer;
			}
		}
		catch (const KError &error)
		{
			//error.dump();
			return false;
		}
		return true;
	}
	return false;
}

bool 	answer::get_state()
{
	return state;
}

const string 	&answer::get_data()
{
	return data;
}
