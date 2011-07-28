/**
	@file
	@brief Contains an OSG utility function to search a scenegraph

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program

	@author
	Based on code from:
	http://www.openscenegraph.org/projects/osg/wiki/Support/Tutorials/FindingNodes

*/

//          Copyright Iowa State University 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_osgFindNamedNode_h_GUID_981f9445_6d58_462f_8452_6937dfac9a52
#define INCLUDED_osgFindNamedNode_h_GUID_981f9445_6d58_462f_8452_6937dfac9a52

// Internal Includes
// - none

// Library/third-party includes
#include <osg/Node>
#include <osg/Group>

// Standard includes
#include <string>

namespace util {

/// @addtogroup FreeFunctions Free Functions
/// @{

/// Search a scenegraph and return the first node found with the given name.
	inline osg::Node* findNamedNode(osg::Node* currNode, std::string modelName) {
		osg::Group* currGroup;
		osg::Node* foundNode;

		// check to see if we have a valid (non-NULL) node.
		// if we do have a null node, return NULL.
		if (!currNode) {
			return NULL;
		}

		// We have a valid node, check to see if this is the node we
		// are looking for. If so, return the current node.
		if (currNode->getName() == modelName) {
			return currNode;
		}

		// We have a valid node, but not the one we are looking for.
		// Check to see if it has children (non-leaf node). If the node
		// has children, check each of the child nodes by recursive call.
		// If one of the recursive calls returns a non-null value we have
		// found the correct node, so return this node.
		// If we check all of the children and have not found the node,
		// return NULL
		currGroup = currNode->asGroup(); // returns NULL if not a group.
		if (currGroup) {
			for (unsigned int i = 0 ; i < currGroup->getNumChildren(); i ++) {
				foundNode = findNamedNode(currGroup->getChild(i), modelName);
				if (foundNode) {
					return foundNode;    // found a match!
				}
			}
			return NULL; // We have checked each child node - no match found.
		} else {
			return NULL; // leaf node, no match
		}
	}

} // end of namespace util

/// @}

#endif // INCLUDED_osgFindNamedNode_h_GUID_981f9445_6d58_462f_8452_6937dfac9a52

