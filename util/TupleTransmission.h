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
#ifndef INCLUDED_TupleTransmission_h_GUID_f23b361a_3baf_4051_acbd_d0ed9b4fcf31
#define INCLUDED_TupleTransmission_h_GUID_f23b361a_3baf_4051_acbd_d0ed9b4fcf31

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/vector.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/transform_view.hpp>

// Standard includes
// - none






namespace util {
	namespace transmission {
		namespace detail {
			using namespace boost::mpl;
			template<typename Types>
			struct MessageDescription {
				typedef Types types;
				typedef typename transform_view<Types, sizeof_<_> >::type sizeof_view;

				enum {
					message_size = (accumulate < types
					, int_<0>
					, plus<_1, sizeof_<_2> >
					>::type::value)
				};

			};
		} // end of namespace detail

		using detail::MessageDescription;

	} // end of namespace transmission

} // end of namespace util


#endif // INCLUDED_TupleTransmission_h_GUID_f23b361a_3baf_4051_acbd_d0ed9b4fcf31
