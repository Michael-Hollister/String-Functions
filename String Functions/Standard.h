/*******************************************************************
* Copyright (c) 2012, Michael Hollister                            *
*                                                                  *
* This source code is subject to the terms of The MIT License.     *
* If a copy of The MIT License was not distributed with this file, *
* you can obtain one at http://opensource.org/licenses/MIT.        *
*******************************************************************/

#pragma once
#ifndef STANDARD_H
#define STANDARD_H

// DBPro namespace declrations.

namespace DBPro
{
	enum ArrayType
	{
		// "Real" datatype was 4?
		Integer,Float,String,Boolean,Word = 5,Dword,DoubleFloat,DoubleInteger
	};
}

#endif // STANDARD_H
