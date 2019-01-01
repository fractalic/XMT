/************************************************************************
*   Package	: libxhist
*   $Version:$
*    Copyright 2018 Visionary Research Inc.   All rights reserved.
*    			legal@visionary-research.com
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*    
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License. 
*
*   Purpose	: 
*
*   Functions	:
*
************************************************************************/

#define __foo_c

#ifdef EMBED_REVISION_STRINGS
static const char foo_c_id[] = "@(#) libxhist::foo.c	$Version:$";
#endif

#include <stdio.h>

void foo()
{
    printf("hello foo\n");
}
