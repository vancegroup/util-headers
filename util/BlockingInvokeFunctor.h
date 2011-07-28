/** @file
	@brief Template class providing a blocking cross-thread invoke functor.

	@date 2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_BlockingInvokeFunctor_h_GUID_88ab16bd_5660_4691_9180_0aa698caa0ce
#define INCLUDED_BlockingInvokeFunctor_h_GUID_88ab16bd_5660_4691_9180_0aa698caa0ce

// Internal Includes
// - none

// Library/third-party includes
#include <boost/function.hpp>

// Standard includes
// - none


namespace util {

	/**	@brief Template class providing a blocking cross-thread invoke functor.

		That is, you have some way of making another thread execute a functor,
		and you'd like to do that _and_ wait until that functor is executed
		before continuing in your initial thread.

		@tparam SyncType some class providing a "block" and "unblock" method -
			implementations using VPR are provided.
		@tparam RetType return type of your nullary function pointer/functor
			to wrap.
	*/
	template<typename SyncType, typename RetType>
	class BlockingInvokeFunctor {
		protected:
			boost::function<RetType()> _function;
			SyncType * _sync;
			bool _creator;
		public:
			/// Construct a functor wrapper.
			BlockingInvokeFunctor(boost::function<RetType()> func) :
				_function(func),
				_sync(new SyncType),
				_creator(true) {}

			/// Copy constructor.
			BlockingInvokeFunctor(BlockingInvokeFunctor const& other) :
				_function(other._function),
				_sync(other._sync),
				_creator(false) {}

			/// Destructor.
			~BlockingInvokeFunctor() {
				if (_creator && _sync) {
					// This is the original thread's copy of the functor,
					// and it hasn't blocked!
					assert(!_sync);
					delete _sync;
					_sync = NULL;
				}
			}

			/// Call from the "creating" thread, after sending this functor
			/// to the receiving thread, to block until the receiving thread
			/// has executed this functor.
			void blockUntilCompletion() {
				_sync->block();
				delete _sync;
				_sync = NULL;
			}

			/// Function call operator: invokes the contained functor then
			/// unblocks
			RetType operator()() {
				RetType ret = _function();
				_sync->unblock();
				return ret;
			}

	};

	/// Partial specialization for void return types - essentially the same as above
	template<typename SyncType>
	class BlockingInvokeFunctor<SyncType, void> {
		protected:
			boost::function<void()> _function;
			SyncType * _sync;
			bool _creator;
		public:
			/// Construct a functor wrapper.
			BlockingInvokeFunctor(boost::function<void()> func) :
				_function(func),
				_sync(new SyncType),
				_creator(true) {}

			/// Copy constructor.
			BlockingInvokeFunctor(BlockingInvokeFunctor const& other) :
				_function(other._function),
				_sync(other._sync),
				_creator(false) {}

			/// Destructor.
			~BlockingInvokeFunctor() {
				if (_creator && _sync) {
					// This is the original thread's copy of the functor,
					// and it hasn't blocked!
					assert(!_sync);
					delete _sync;
					_sync = NULL;
				}
			}

			void blockUntilCompletion() {
				_sync->block();
				delete _sync;
				_sync = NULL;
			}

			void operator()() {
				_function();
				_sync->unblock();
			}
	};
} // end of util namespace

#endif // INCLUDED_BlockingInvokeFunctor_h_GUID_88ab16bd_5660_4691_9180_0aa698caa0ce
