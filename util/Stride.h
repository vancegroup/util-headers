/**	@file	Stride.h
	@brief	A class for handling "do this every n times"

	@date
	2009-2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/
#pragma once
#ifndef INCLUDED_Stride_h_GUID_eaa50b9c_e526_4656_89dc_99008d82447d
#define INCLUDED_Stride_h_GUID_eaa50b9c_e526_4656_89dc_99008d82447d

// Local includes
// - none

// Library includes
// - none

// Standard includes
// - none

namespace util {

/// @addtogroup Other Other Utility Classes
/// @{

/// Handle the task of "do this every n times" in an easy way.
class Stride {
	public:
		Stride(const unsigned int n) :
			_stride(n),
			_step(0) { }

		void advance() {
			_step = (_step + 1) % _stride;
		}

		Stride operator++() {
			Stride temp = *this;
			advance();
			return temp;
		}

		Stride & operator++(int) {
			advance();
			return *this;
		}

		operator bool() const {
			return _step == 0;
		}

	private:
		unsigned int _stride;
		unsigned int _step;
};

/// @}

} // end of util namespace

#endif // INCLUDED_Stride_h_GUID_eaa50b9c_e526_4656_89dc_99008d82447d

