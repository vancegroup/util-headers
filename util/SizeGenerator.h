/**	@file	SizeGenerator.h
	@brief	Utility header for a "generator" object simulating two nested loops.

	@date	2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_SizeGenerator_h_GUID_46b0d167_fb36_4c0a_bacd_134533ccb6a5
#define INCLUDED_SizeGenerator_h_GUID_46b0d167_fb36_4c0a_bacd_134533ccb6a5

// Local includes
// - none

// Library includes
// - none

// Standard includes
#include <iostream>
#include <iomanip>

namespace util {

/// @addtogroup Other Other Utility Classes
/// @{

	class SizeGenerator {
		public:
			SizeGenerator(unsigned int min, unsigned int max, unsigned int step) :
				_min(min),
				_max(max),
				_step(step),
				_rows(min),
				_cols(min) {}

			bool loop() {
				if (_rows > _max) {
					return false;
				} else if (_cols > _max) {
					_cols = _min;
					_rows += _step;
				} else {
					_cols += _step;
				}
				return true;
			}

			void print() const {
				std::cout << std::setw(6) << "Rows:" << std::setw(6) << _rows;
				std::cout << std::setw(6) << "Cols:" << std::setw(6) << _cols;
				std::cout << std::endl;
			}

			unsigned int rows() const {
				return _rows;
			}

			unsigned int cols() const {
				return _cols;
			}
		private:
			unsigned int _min;
			unsigned int _max;
			unsigned int _step;
			unsigned int _rows;
			unsigned int _cols;
	};

/// @}
}

#endif // INCLUDED_SizeGenerator_h_GUID_46b0d167_fb36_4c0a_bacd_134533ccb6a5

