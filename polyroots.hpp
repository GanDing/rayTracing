// Fall 2018

/* //-------------------------------------------------------------------------
//
// CS488 -- Introduction to Computer Graphics
//
// polyroots.hpp/polyroots.cpp
//
// Utility functions to solve low-order polynomial equations efficiently
// and robustly.  Very useful when writing ray-object intersection tests.
// You don't need these functions in Assignment 3.
//
//------------------------------------------------------------------------- */

#ifndef CS488_POLYROOTS_HPP
#define CS488_POLYROOTS_HPP

#include <stdlib.h>

size_t quadraticRoots(float A, float B, float C, float roots[2]);
size_t cubicRoots(float A, float B, float C, float roots[3]);
size_t quarticRoots(float A, float B, float C, float D, float roots[4]);

#endif /* CS488_POLYROOTS_HPP */

/*
 * Copyright (c) 1990, Graphics and AI Laboratory, University of Washington
 * Copying, use and development for non-commercial purposes permitted.
 *                  All rights for commercial use reserved.
 */
