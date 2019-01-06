/*
Author: Peter Nwanosike
Email: dexter4life@gmail.com

Ct is free software : you can redistribute it and / or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License.


Ct is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Ct.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef SIGNAL_H
#define SIGNAL_H

#include <set>
#include <list>

#include <ctcore/ctglobal.h>
#include <CtCore/ctobject.h>

template<class mt_policy>
class has_slots;

template<class mt_policy, class ... Args>
class _connection_base_variadic
{
	static const std::size_t _sArgSize = sizeof...(Args);
public:
	virtual has_slots<mt_policy>* getdest() const = 0;
	virtual void emit(Args... args) = 0;
	virtual _connection_base_variadic<mt_policy, Args...>* clone() = 0;
	virtual _connection_base_variadic<mt_policy, Args...>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
};

template<class mt_policy>
class _signal_base : public mt_policy
{
public:
	virtual void slot_disconnect(has_slots<mt_policy>* pslot) = 0;
	virtual void slot_duplicate(const has_slots<mt_policy>* poldslot, has_slots<mt_policy>* pnewslot) = 0;
};

template<class mt_policy = DEFAULT_MULT_THREAD_POLICY>
class has_slots : public mt_policy
{
private:
	typedef std::set<_signal_base<mt_policy> *> sender_set;
	//typedef std::set::const_iterator const_iterator;
	typedef typename sender_set::const_iterator const_iterator;

public:
	has_slots(){}

	has_slots(const has_slots& hs)
		: mt_policy(hs)
	{
		lock_block<mt_policy> lock(this);
		const_iterator it = hs.m_senders.begin();
		const_iterator itEnd = hs.m_senders.end();

		while (it != itEnd)
		{
			(*it)->slot_duplicate(&hs, this);
			m_senders.insert(*it);
			++it;
		}
	}

	void signal_connect(_signal_base<mt_policy>* sender)
	{
		lock_block<mt_policy> lock(this);
		m_senders.insert(sender);
	}

	void signal_disconnect(_signal_base<mt_policy>* sender)
	{
		lock_block<mt_policy> lock(this);
		m_senders.erase(sender);
	}

	virtual ~has_slots()
	{
		disconnect_all();
	}

	void disconnect_all()
	{
		lock_block<mt_policy> lock(this);
		const_iterator it = m_senders.begin();
		const_iterator itEnd = m_senders.end();

		while (it != itEnd)
		{
			(*it)->slot_disconnect(this);
			++it;
		}

		m_senders.erase(m_senders.begin(), m_senders.end());
	}
	
	void setSender(cthandle *sender)
	{
		m_sender = sender;
	}

	cthandle sender() const
	{
		return const_cast<cthandle>(m_sender);
	}
private:
	sender_set	m_senders;

	cthandle	m_sender;
};

template<class mt_policy, class ... Args>
class _signal_base_variadic : public _signal_base<mt_policy>
{
public:
	typedef std::list<_connection_base_variadic<mt_policy, Args...> *>  connections_list;

	_signal_base_variadic()
	{
	}

	_signal_base_variadic(const _signal_base_variadic<mt_policy, Args...>& s)
		: _signal_base<mt_policy>(s)
	{
		lock_block<mt_policy> lock(this);
		connections_list::const_iterator it = s.m_connected_slots.begin();
		connections_list::const_iterator itEnd = s.m_connected_slots.end();

		while (it != itEnd)
		{
			(*it)->getdest()->signal_connect(this);
			m_connected_slots.push_back((*it)->clone());

			++it;
		}
	}

	void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget)
	{
		lock_block<mt_policy> lock(this);
		connections_list::iterator it = m_connected_slots.begin();
		connections_list::iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			if ((*it)->getdest() == oldtarget)
			{
				m_connected_slots.push_back((*it)->duplicate(newtarget));
			}

			++it;
		}
	}

	~_signal_base_variadic()
	{
		disconnect_all();
	}

	void disconnect_all()
	{
		lock_block<mt_policy> lock(this);
		connections_list::const_iterator it = m_connected_slots.begin();
		connections_list::const_iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			(*it)->getdest()->signal_disconnect(this);
			delete *it;

			++it;
		}

		m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
	}

	void disconnect(has_slots<mt_policy>* pclass)
	{
		lock_block<mt_policy> lock(this);
		connections_list::iterator it = m_connected_slots.begin();
		connections_list::iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			if ((*it)->getdest() == pclass)
			{
				delete *it;
				m_connected_slots.erase(it);
				pclass->signal_disconnect(this);
				return;
			}

			++it;
		}
	}

	void slot_disconnect(has_slots<mt_policy>* pslot)
	{
		lock_block<mt_policy> lock(this);
		connections_list::iterator it = m_connected_slots.begin();
		connections_list::iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			connections_list::iterator itNext = it;
			++itNext;

			if ((*it)->getdest() == pslot)
			{
				m_connected_slots.erase(it);
				//			delete *it;
			}

			it = itNext;
		}
	}


protected:
	connections_list m_connected_slots;
};

template<class dest_type, class mt_policy, class... Args>
class _connection_variadic : public _connection_base_variadic<mt_policy, Args...>
{
public:
	_connection_variadic()
	{
		m_pobject = NULL;
		m_pmemfun = NULL;
	}

	_connection_variadic(dest_type* pobject, void (dest_type::*pmemfun)(Args...))
	{
		m_pobject = pobject;
		m_pmemfun = pmemfun;
	}

	virtual _connection_base_variadic<mt_policy, Args...>* clone()
	{
		return new _connection_variadic<dest_type, mt_policy, Args...>(*this);
	}

	virtual _connection_base_variadic<mt_policy, Args...>* duplicate(has_slots<mt_policy>* pnewdest)
	{
		return new _connection_variadic<dest_type, mt_policy, Args...>((dest_type *)pnewdest, m_pmemfun);
	}

	virtual void emit(Args... arg)
	{
		(m_pobject->*m_pmemfun)(arg...);
	}

	virtual has_slots<mt_policy>* getdest() const
	{
		return m_pobject;
	}

private:
	dest_type* m_pobject;
	void (dest_type::* m_pmemfun)(Args...);
};

template<class mt_policy = DEFAULT_MULT_THREAD_POLICY, class... Args>
class signal_variadic : public _signal_base_variadic<mt_policy, Args...>
{
public:
	signal_variadic()
	{
	}

	signal_variadic(const signal_variadic<mt_policy, Args...>& s)
		: _signal_base_variadic<mt_policy, Args...>(s)
	{
	}

	template<class desttype>
	void connect(desttype* pclass, void (desttype::*pmemfun)(Args...))
	{
		lock_block<mt_policy> lock(this);
		_connection_variadic<desttype, mt_policy, Args...> * conn = new _connection_variadic<desttype, mt_policy, Args...>(pclass, pmemfun);
		m_connected_slots.push_back(conn);
		pclass->signal_connect(this);
	}

	void emit(Args... args)
	{
		lock_block<mt_policy> lock(this);
		connections_list::const_iterator itNext, it = m_connected_slots.begin();
		connections_list::const_iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			itNext = it;
			++itNext;

			(*it)->emit(args);

			it = itNext;
		}
	}

	void operator()(Args... args)
	{
		lock_block<mt_policy> lock(this);
		connections_list::const_iterator itNext, it = m_connected_slots.begin();
		connections_list::const_iterator itEnd = m_connected_slots.end();

		while (it != itEnd)
		{
			itNext = it;
			++itNext;

			(*it)->emit(args...);

			it = itNext;
		}
	}
};

#define _declare_signal(name,_class)\
template<class ...Args>\
class name{\
public:\
template<class desttype, class ...destArgs>\
inline void connect(desttype *slot, void (desttype::*pmemfun2)(destArgs...)) {\
	object.connect(slot, pmemfun2);}\
template<class ...destArgs>\
inline void operator()(destArgs... args) {\
	object(args...);}\
template<class desttype>\
inline void disconnect(desttype *signal){\
object.disconnect(signal);\
}\
private:\
signal_variadic<DEFAULT_MULT_THREAD_POLICY, Args ...> object;};\
public:\
template<class desttype, class ...destArgs>\
inline void _class##_##connect(desttype *slot, void (desttype::*pmemfun2)(destArgs...)){\
	slot->setSender(reinterpret_cast<cthandle*>(this));\
	_class.connect(slot, pmemfun2);}\
template<class desttype>\
inline void _class##_##disconnect(desttype *signal){\
	_class.disconnect(signal);}\
template<class ...destArgs>\
inline void emit##_##_class(destArgs ...args){\
	_class(args...);}

#define declare_signal_main(signal,name)  _declare_signal(name##_##signal,name)

#define declare_signal_cat(signal,name,...) name##_##signal##<##__VA_ARGS__##> name;
// access=public or private
//#define SIGNAL(access) access
//#ifdef SIGNAL
#define declare_signal(name,...) declare_signal_main(signal,name)\
declare_signal_cat(signal,name,__VA_ARGS__ /*arg param type*/)

//#endif

#endif // !SIGNAL_H