/** @file
	@brief Header

	@versioninfo@

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
#include <boost/fusion/mpl.hpp> // mpl to fusion link
#include <boost/fusion/include/as_vector.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

// Standard includes
// - none






namespace util {
	namespace transmission {
		namespace detail {
			using namespace boost::mpl;
			namespace fusion = boost::fusion;

			template<typename MPLTypesVector>
			struct MessageDescription {
				typedef MPLTypesVector types;
				typedef typename fusion::result_of::as_vector<types>::type fusion_vec_type;
				typedef typename transform_view<types, sizeof_<_> >::type sizeof_view;

				enum {
					message_size = (accumulate
					< types
					, int_<0>
					, plus<_1, sizeof_<_2> >
					>::type::value)
				};

				template<BOOST_PP_ENUM_PARAMS(3, typename T)>
				static fusion_vec_type create(BOOST_PP_ENUM_BINARY_PARAMS(3,  T, a)) {
					return fusion_vec_type(BOOST_PP_ENUM_PARAMS(3, a));
				}

			};
		} // end of namespace detail

		using detail::MessageDescription;

	} // end of namespace transmission

} // end of namespace util


#endif // INCLUDED_TupleTransmission_h_GUID_f23b361a_3baf_4051_acbd_d0ed9b4fcf31
