#!/bin/sh
grep --only-matching "BOOST_AUTO_TEST_CASE[(][^)]*[)]" $1 | sed -e 's/BOOST_AUTO_TEST_CASE[(]//g' -e 's/[)]//g'
