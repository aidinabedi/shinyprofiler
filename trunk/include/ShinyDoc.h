/*
The zlib/libpng License

Copyright (c) 2007 Aidin Abedi (http://shinyprofiler.sourceforge.net)

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that
       you wrote the original software. If you use this software in a product,
       an acknowledgment in the product documentation would be appreciated but is
       not required.

    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SHINY_PROFILER // do not include this file


//-----------------------------------------------------------------------------
/*! \mainpage

\section Introduction
Goto the documentation here: \ref ShinyDoc.h

\n
\subsection sub1 What is Shiny?

Shiny is a low overhead, well documented and lightning fast C++ profiler. Easy to use on existing projects, no extensive surgery, just have fun with it. Nicely formatted output provides call tree (call graph), flat profile and is simple to custom display.

\n
\subsection sub-1 What is this document?

\ref ShinyDoc.h is a complete description of all the Shiny macros. Macro is a preprocessor directive that provides a mechanism for token replacement in your source code. Shiny uses macros to simplify interface and remain powerful. If the preprocessor SHINY_PROFILER is defined as FALSE all Shiny macros are ignored unless specified otherwise.

\n
\subsection sub2 Where can I download Shiny?

\htmlonly
<a href="https://sourceforge.net/project/showfiles.php?group_id=208504" >Browse All Files</a>
\endhtmlonly

\n
\subsection sub3 Why did you create Shiny?

I was working on a graphics engine and I wanted to see the fruit of my optimizations and growth to each critical part. I needed something accurate, adapted to my main-loop & display and disgusting fast.

\n
\subsection sub4 What's the difference between other profilers?

Most profilers are external tools and can't adapt to the way your project is designed. The rest aren't really powerful enough. Shiny can adapt to your code flow and your display by your choice. Optimized to the bone, delivers both call tree/graph and flat profile and is so easy to use you'll never look at another profiler again.

\n
\subsection sub5 What features does Shiny support?

Where are some key features:
-    Lightning fast and accurate profiling.
-    Self-initialization: no explicit starting point.
-    Ridiculously easy and minimal interface.
-    Nicely formatted output with customizable display.
-    Call-tree with recursion and child-to-parent relationship timing.
-    Smooth averages support for main-loop projects, typically games.
-    Static combinded with internal pool memory manager for negligible presence.
-    Platform-independent clean source code without GPL restrictions.
-    Well documentation and example rich.


\n
\subsection sub6 How to switch Shiny on and off?

Shiny is turned on or off at compile time. Define the pre-processor SHINY_PROFILER to TRUE or FALSE to enable or disable, before including header Shiny.h. Shiny can also be enabled or disabled in ShinyConfig.h. Default is on.

\n
\subsection sub7 Does Shiny support C language?

No. I currently have no future plans to support C, although it is easy to adapt Shiny for C without touching the interface.

\n
\subsection sub8 Is Shiny thread-safe?

Not yet.

\n
\subsection sub9 Why is profile data zero?

PROFILER_UPDATE must be called before outputting profile data.

\n
\subsection sub10 How to output latest profile data instead of averages?

Set damping to zero when calling PROFILER_UPDATE.
In code: PROFILER_UPDATE(0);

\n
\subsection sub11 Why is profile data "hit" count a floating-point?

Shiny uses the exponential moving average to calculate floating-point values for the latest profile data values. This can be customized by the damping parameter for PROFILER_UPDATE.

\n
\subsection sub12 Why is some profile data leaping seconds back or forward in time?

Your platform has broken support for multi-core or multi-processor high-performance timing. You can solve this in three ways in Windows:
-    (Recommended) Download the fix for this from Microsoft website.
-    Call SetProcessAffinityMask or SetThreadAffinityMask at start of program to lock your thread/process to a specific CPU.
-    (Not Recommended) Use timeGetTime instead of QueryPerformanceCounter in the Shiny source code.

*/

//-----------------------------------------------------------------------------
//! Profile the caller function
/*!
This will create and begin a profile with the caller function name until end of block. Call this in the beginning of your function.

\note Must only be called at most once per function.

\code
//Exmaple Code:

void foobar() {
	PROFILE_FUNC(); // beginning of your function

	// some code
}
\endcode

\see
PROFILE_CODE
PROFILE_BLOCK
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_FUNC()


//-----------------------------------------------------------------------------
//! Profile and execute the specified code
/*! 
This will create and begin a profile, execute code, and end profile. PROFILE_CODE is typically used when you want to profile a function call without touching the function source code or profiling every call.

\note Any return value from the executed code will be lost.

\param Code to be executed and profiled.

\code
//Exmaple Code:

void foobar() {
	int x, y, z;

	// some code

	PROFILE_CODE(x = y + z); // profile code line: x = y + z;
}
\endcode

\see
PROFILE_FUNC
PROFILE_BLOCK
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_CODE(Code)


//-----------------------------------------------------------------------------
//! Profile the caller block
/*! 
This will create and begin a profile with the specified name until end of block. Call this in the beginning of your code block (function, for-loop, if-statment, etc).

\note Must only be called at most once per code block.

\param Name of profile to be created. Name is an identifier (not a string) and uses C++ naming rules.

\code
//Exmaple Code:

void foobar() {
	// unprofiled code
	{
		// unprofiled code

		PROFILE_BLOCK(CuteName);

		// profiled code identified with name "CuteName"
	}
	// unprofiled code
}
\endcode

\see
PROFILE_FUNC
PROFILE_CODE
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_BLOCK(Name)


//-----------------------------------------------------------------------------
//! Profile until PROFILE_END
/*! 
This will create and begin a profile with the specified name until PROFILE_END is called. Call PROFILE_END to end profile.

\note When the profile is finished program must call PROFILE_END.

\param Name of profile to be created. Name is an identifier (not a string) and uses C++ naming rules.

\code
//Exmaple Code:

void foobar() {
	// unprofiled code
	
	PROFILE_BEGIN(CuteName);

	// profiled code identified with name "CuteName"

	PROFILE_END();

	// unprofiled code
}
\endcode

\see
PROFILE_FUNC
PROFILE_CODE
PROFILE_BLOKC
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_BEGIN(Name)


//-----------------------------------------------------------------------------
//! End current profile
/*! 
This will end the profile last called. Call this after PROFILE_BEGIN or PROFILE_SHARED_BEGIN.

\note If no current profile is running any call to PROFILE_END is ignored.

\code
//Exmaple Code:

void foobar() {
	// unprofiled code
	
	PROFILE_BEGIN(CuteName);

	// profiled code identified with name "CuteName"

	PROFILE_END();

	// unprofiled code
}
\endcode

\see
PROFILE_BEGIN
PROFILE_SHARED_BEGIN
*/

#define PROFILE_END()


//-----------------------------------------------------------------------------
//! Create a shared profile.
/*! 
Creates a shared profile with the specified name. Add this outside of any function or class block and use the same profile in multiple areas inside the same source file. Call PROFILE_SHARED_BLOCK or PROFILE_SHARED_BEGIN with name to use profile.

\note PROFILE_SHARED_GLOBAL or PROFILE_SHARED_MEMBER can be used to expand profile for multiple source files.  If profile is declared in a class or namespace the name in PROFILE_SHARED_DEFINE prefix format class::name where class is an identifier name.

\param Name of profile to be created. Name is an identifier (not a string) and uses C++ naming rules.


\code
//Exmaple Code:

PROFILE_SHARED_DEFINE(myprofile)

function ()

\endcode

\see
PROFILE_SHARED_EXTERN
PROFILE_SHARED_STATIC
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_SHARED_DEFINE()


//-----------------------------------------------------------------------------
//! short
/*! 
{Specialisation offered by the function A}

\note Must only be called at most once per function

\param {details of 1st parameters used}

\param {details of 2nd parameters used}

\param {etc...}

\return {details of any return values}

\code
//Exmaple Code:
{working example}
\endcode

\see
PROFILE_CODE
PROFILE_BLOCK
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_()


//-----------------------------------------------------------------------------
//! short
/*! 
{Specialisation offered by the function A}

\note Must only be called at most once per function

\param {details of 1st parameters used}

\param {details of 2nd parameters used}

\param {etc...}

\return {details of any return values}

\code
//Exmaple Code:
{working example}
\endcode

\see
PROFILE_CODE
PROFILE_BLOCK
PROFILE_BEGIN
PROFILE_UPDATE_ALL
PROFILE_OUTPUT_ALL
*/

#define PROFILE_()

//-----------------------------------------------------------------------------


#endif
