/** @file
	@brief Header

	@date 2012

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_ReceiveBuffer_h_GUID_2d1681f0_0ffe_495d_8ec9_fd730b801721
#define INCLUDED_ReceiveBuffer_h_GUID_2d1681f0_0ffe_495d_8ec9_fd730b801721

// Internal Includes
#include "VectorSimulator.h"
#include <util/booststdint.h>

// Library/third-party includes
#include <boost/array.hpp>
#include <boost/integer.hpp>
//#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

// Standard includes
#include <stdexcept>
#include <algorithm>

namespace util {
	/*
		namespace detail {
			template<typename Values>
			class ReceiveBufferIterator
				: public boost::iterator_facade <
				ReceiveBufferIterator<Values>,
				Values,
					boost::random_access_traversal_tag > {

				public:
					ReceiveBufferIterator()
						: m_elt(NULL) {}

					explicit ReceiveBufferIterator(Values * p)
						: m_elt(p) {}
				private:
					friend class boost::iterator_core_access;


					Values * m_elt;
			};

		} // end of namespace detail
	*/
	template<int SIZE, typename Values = stdint::uint8_t>
	class ReceiveBuffer : public vector_simulator<ReceiveBuffer<SIZE, Values>, Values, typename boost::uint_value_t< SIZE >::least> {
		public:
			typedef ReceiveBuffer<SIZE, Values> type;
			typedef vector_simulator<type, Values, typename boost::uint_value_t< SIZE >::least> base_type;

			typedef Values value_type;
			typedef value_type & reference;
			typedef value_type const & const_reference;
			typedef typename boost::uint_value_t< SIZE >::least size_type;
			typedef boost::array<value_type, SIZE> wrapped_type;
			typedef typename wrapped_type::iterator iterator;
			typedef typename wrapped_type::const_iterator const_iterator;

			enum {
				CAPACITY = SIZE
			};

			ReceiveBuffer()
				: _start(0)
				, _pastEnd(0)
				, _contents()
			{}

			ReceiveBuffer(type const& other)
				: _start(0)
				, _pastEnd(other.size())
				, _contents() {
				idealContentsCopy(other, *this);
//				std::copy(other._contents.begin() + other._start, other._contents.begin() + other._pastEnd, _contents.begin());
			}

			type & operator=(type const& other) {
				if (this == &other) {
					slide_contents_forward(); /// A cleanup no-op
				} else {
					idealContentsCopy(other, *this);
				}
				return *this;
			}

			bool isEmpty() const {
				return _start == _pastEnd;
			}

			size_type size() const {
				return _pastEnd - _start;
			}

			reference operator[](size_type i) {
				/*
				if (i == size()) {
					/// Assume this means they're inserting
					/// @todo is this a smart assumption?
					ensure_space(1);
					increment_end();
				}
				*/

				BOOST_ASSERT_MSG(adjusted_index(i) < size(), "out of range");
				return _contents[adjusted_index(i)];
			}

			const_reference operator[](size_type i) const {
				BOOST_ASSERT_MSG(adjusted_index(i) < size(), "out of range");
				return _contents[adjusted_index(i)];
			}

			void push_back(const_reference x) {
				ensure_space(1);
				_contents[_pastEnd] = x;
				increment_pastEnd();
			}

			iterator begin() {
				return _contents.begin() + _start;
			}

			const_iterator begin() const {
				return _contents.begin() + _start;
			}

			iterator end() {
				return _contents.begin() + _pastEnd;
			}

			const_iterator end() const {
				return _contents.begin() + _pastEnd;
			}

		private:
			friend class vector_simulator_access;

			void opportunistic_reset() {
				if (isEmpty()) {
					_start = 0;
					_pastEnd = 0;
				}
			}

			size_type adjusted_index(size_type i) {
				return _start + i;
			}

			void ensure_space(size_type n) {
				opportunistic_reset();
				if (_pastEnd + n <= CAPACITY) {
					return;
				} else {
					/// Slide back to the front of the array
					BOOST_ASSERT_MSG(size() + n < CAPACITY, "Impossible to ensure that much space");
					slide_contents_forward();
					/*
					std::copy(_contents.begin() + _start, _contents.begin() + _pastEnd, _contents.begin());
					_pastEnd -= _start;
					_start = 0;
					*/
				}
			}

			void slide_contents_forward() {
				idealContentsCopy(*this, *this);
			}

			bool range_check(size_type i) const {
				return i < size();
			}

			void increment_pastEnd() {
				ensure_space(1);
				_pastEnd++;
				BOOST_ASSERT_MSG(_pastEnd <= CAPACITY, "Consuming more space than possible");
			}

			static void idealContentsCopy(type const& source, type & dest) {
				std::copy(source._contents.begin() + source._start, source._contents.begin() + source._pastEnd, dest._contents.begin());
				dest._pastEnd = source.size();
				dest._start = 0;
			}
			size_type _start;
			size_type _pastEnd;
			wrapped_type _contents;


	};


} // end of namespace util

#endif // INCLUDED_ReceiveBuffer_h_GUID_2d1681f0_0ffe_495d_8ec9_fd730b801721
