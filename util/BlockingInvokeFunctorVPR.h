/** @file BlockingInvokeFunctorVPR.h
	@brief

	@date 2011

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

#pragma once
#ifndef INCLUDED_BlockingInvokeFunctorVPR_h_GUID_a2f76b13_a280_4cbf_a0bd_594135c1aa0f
#define INCLUDED_BlockingInvokeFunctorVPR_h_GUID_a2f76b13_a280_4cbf_a0bd_594135c1aa0f

// Internal Includes
// - none

// Library/third-party includes
#include <vpr/Thread/Thread.h>
#include <vpr/Sync/Semaphore.h>

// Standard includes
// - none

namespace util {
	/// A SyncType for the BlockingInvokeFunctor that uses VPR semaphores.
	class VPRInvokeFunctorSync {
		private:
			vpr::Semaphore s;
		public:
			VPRInvokeFunctorSync() : s(0) {}
			void block() {
				s.acquire();
			}
			void unblock() {
				s.release();
			}

	};

	/// A SyncType for the BlockingInvokeFunctor that uses a busy-wait
	/// with VPR yield, and only a bool flag (no system synchronization calls)
	class VPRInvokeFunctorFlagSync {
		private:
			bool f;
		public:
			VPRInvokeFunctorFlagSync() : f(false) {}

			void block() {
				while (!f) {
					vpr::Thread::yield();
				}
			}
			void unblock() {
				f = true;
			}
	};


} // end of namespace util

#endif // INCLUDED_BlockingInvokeFunctorVPR_h_GUID_a2f76b13_a280_4cbf_a0bd_594135c1aa0f
