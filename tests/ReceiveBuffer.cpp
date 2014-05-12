/**
	@author
	Ryan Pavlik ( <rpavlik@iastate.edu> http://academic.cleardefinition.com/ ),
	Iowa State University
	Virtual Reality Applications Center and
	Human-Computer Interaction Graduate Program
*/

#define BOOST_TEST_MODULE ReceiveBuffer

// Internal Includes
#include <util/ReceiveBuffer.h>

// Library/third-party includes
#include <BoostTestTargetConfig.h>

// Standard includes
#include <iostream>

using namespace boost::unit_test;

using util::ReceiveBuffer;

BOOST_AUTO_TEST_CASE(ConstructionDefault) {
	BOOST_CHECK_NO_THROW(ReceiveBuffer<25>());
}

BOOST_AUTO_TEST_CASE(ConstructionCopy) {
	ReceiveBuffer<25> a;

	BOOST_CHECK_NO_THROW(ReceiveBuffer<25>(a));
}

BOOST_AUTO_TEST_CASE(PushBackSingle) {
	ReceiveBuffer<25> a;

	char valueToInsert = 0;
	BOOST_REQUIRE_NO_THROW(a.push_back(valueToInsert));
	BOOST_CHECK_EQUAL(a.size(), 1);
	BOOST_CHECK_EQUAL(a[0], valueToInsert);
	BOOST_CHECK(!a.empty());
}

BOOST_AUTO_TEST_CASE(CopyPopFront) {
	std::string text("This is a test.");
	const unsigned int len = text.size();

	ReceiveBuffer<50, char> a(text.begin(), text.end());

	BOOST_CHECK_EQUAL(a.size(), len);
	for (unsigned int i = 0; i < len; ++i) {
		std::cout << int(i) << ":  " << a[i] << " , " << text[i] << std::endl;
		BOOST_CHECK_EQUAL(a[i], text[i]);
	}
	BOOST_CHECK_EQUAL(a.size(), len);
	for (unsigned int i = 0; i < len; ++i) {
		BOOST_CHECK_EQUAL(a.front(), text[i]);
		BOOST_CHECK_EQUAL(a.pop_front(), text[i]);
	}
	BOOST_CHECK_EQUAL(a.size(), 0);
}

BOOST_AUTO_TEST_CASE(CopyPopBack) {
	std::string text("This is a test.");
	const int len = text.size();

	ReceiveBuffer<50, char> a(text.begin(), text.end());

	BOOST_CHECK_EQUAL(a.size(), len);
	for (int i = len - 1; i >= 0; --i) {
		std::cout << int(i) << ":  " << a[i] << " , " << text[i] << std::endl;
		BOOST_CHECK_EQUAL(a[i], text[i]);
		BOOST_CHECK_EQUAL(a.back(), text[i]);
		BOOST_CHECK_EQUAL(a.pop_back(), text[i]);
	}
	BOOST_CHECK_EQUAL(a.size(), 0);
}

BOOST_AUTO_TEST_CASE(Slide) {
	std::string foobar("foobar");
	ReceiveBuffer<7, char> a(foobar.begin(), foobar.end());

	BOOST_CHECK_EQUAL(a.size(), foobar.size());

	a.pop_front(3);
	BOOST_CHECK_EQUAL(a.size(), 3);

	// This triggers a slide.
	a = a;
	BOOST_CHECK_EQUAL(a.size(), 3);

	for (int i = 0; i < 3; ++i) {
		BOOST_CHECK_EQUAL(a[i], foobar[i + 3]);
	}

	for (int i = 0; i < 3; ++i) {
		BOOST_CHECK_EQUAL(a.front(), foobar[i + 3]);
		BOOST_CHECK_EQUAL(a.pop_front(), foobar[i + 3]);
	}

	BOOST_CHECK_EQUAL(a.size(), 0);
}


BOOST_AUTO_TEST_CASE(SlideAppend) {
	std::string foobar("foobar");
	std::string baz("baz");
	std::string barbaz("barbaz");

	ReceiveBuffer<6, char> a(foobar.begin(), foobar.end());
	BOOST_CHECK_EQUAL(a.size(), foobar.size());

	typedef ReceiveBuffer<6, char>::iterator iterator;
	iterator begin = a.begin();
	iterator end = a.end();

	a.pop_front(3);
	BOOST_CHECK_GT(a.begin(), begin);
	BOOST_CHECK_EQUAL(a.end(), end);
	BOOST_CHECK_EQUAL(a.size(), 3);

	/// This will trigger a slide
	a.push_back(baz.begin(), baz.end());

	BOOST_CHECK_EQUAL(a.size(), 6);
	BOOST_CHECK_EQUAL(a.begin(), begin);
	BOOST_CHECK_EQUAL(a.end(), end);

	for (int i = 0; i < 6; ++i) {
		BOOST_CHECK_EQUAL(a[i], barbaz[i]);
	}

	for (int i = 0; i < 6; ++i) {
		BOOST_CHECK_EQUAL(a.front(), barbaz[i]);
		BOOST_CHECK_EQUAL(a.pop_front(), barbaz[i]);
	}

	BOOST_CHECK_EQUAL(a.size(), 0);
}

BOOST_AUTO_TEST_CASE(EraseFront) {
	std::string foobar("foobar");

	ReceiveBuffer<7, char> a(foobar.begin(), foobar.end());
	ReceiveBuffer<7, char> b(foobar.begin(), foobar.end());
	a.erase(a.begin());
	b.pop_front();
	for (int i = 0; i < 5; ++i) {
		BOOST_CHECK_EQUAL(a[i], b[i]);
		BOOST_CHECK_EQUAL(a[i], foobar[i + 1]);
	}
}

BOOST_AUTO_TEST_CASE(EraseTwoFront) {
	std::string foobar("foobar");

	ReceiveBuffer<7, char> a(foobar.begin(), foobar.end());
	ReceiveBuffer<7, char> b(foobar.begin(), foobar.end());
	a.erase(a.begin(), a.begin() + 2);
	b.pop_front(2);
	for (int i = 0; i < 4; ++i) {
		BOOST_CHECK_EQUAL(a[i], b[i]);
		BOOST_CHECK_EQUAL(a[i], foobar[i + 2]);
	}
}

BOOST_AUTO_TEST_CASE(EraseBack) {
	std::string foobar("foobar");

	ReceiveBuffer<7, char> a(foobar.begin(), foobar.end());
	ReceiveBuffer<7, char> b(foobar.begin(), foobar.end());
	a.erase(a.end() - 1);
	b.pop_back();
	for (int i = 0; i < 5; ++i) {
		BOOST_CHECK_EQUAL(a[i], b[i]);
		BOOST_CHECK_EQUAL(a[i], foobar[i]);
	}
}

BOOST_AUTO_TEST_CASE(EraseTwoBack) {
	std::string foobar("foobar");

	ReceiveBuffer<7, char> a(foobar.begin(), foobar.end());
	ReceiveBuffer<7, char> b(foobar.begin(), foobar.end());
	a.erase(a.end() - 2, a.end());
	b.pop_back(2);
	for (int i = 0; i < 4; ++i) {
		BOOST_CHECK_EQUAL(a[i], b[i]);
		BOOST_CHECK_EQUAL(a[i], foobar[i]);
	}
}

