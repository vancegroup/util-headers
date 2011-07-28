/**	@file	LockFreeBuffer.h
	@brief	A lock-free bounded buffer for haptics

	@date
	2009-2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2009-2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_LockFreeBuffer_h_GUID_04578a7b_6d47_4faa_848d_269963fdef2f
#define INCLUDED_LockFreeBuffer_h_GUID_04578a7b_6d47_4faa_848d_269963fdef2f


// Local includes
// - none

// Library includes
// - none

// Standard includes
// - none

#ifdef LOCKFREEBUFFER_NEEDVOLATILE
#define LFB_VOL volatile
#else
#define LFB_VOL
#endif

namespace util {

/// @addtogroup DataStructures Data Structures
/// @{

	/** @brief A buffer with one producer and one consumer, and no OS locks.
	*/
	template<class T>
	class LockFreeBuffer {
		public:
			LockFreeBuffer() :
				_sent(0),
				_received(0) { }
			~LockFreeBuffer() {}

			typedef T value_type;

			bool send(value_type const& item) {
				if (_sent == _received) {
					_val = item;
					_sent = ~_received; // let sent be bitwise-NOT of received
					return true;
				} else {
#ifdef VERBOSE
					std::cout << __FUNCTION__ << ": skipping because last update not received" << std::endl;
#endif
					return false;
				}
			}

			bool receive(value_type & out) {
				if (_sent != _received) {
					out = _val;
					_received = _sent;
					return true;
				} else {
#ifdef VERBOSE
					std::cout << __FUNCTION__ << ": failed because no new updates" << std::endl;
#endif
					return false;
				}
			}

		private:
			value_type _val;

			// See http://msdn.microsoft.com/en-us/library/12a04hfd%28VS.80%29.aspx
			// for information on volatile
			int LFB_VOL _sent;
			int LFB_VOL _received;
	};

// -- inline implementations -- //

/// @}
} // end of namespace util

#endif // INCLUDED_LockFreeBuffer_h_GUID_04578a7b_6d47_4faa_848d_269963fdef2f


