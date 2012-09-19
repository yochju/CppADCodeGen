#ifndef CPPAD_CG_LINUX_C_LANG_COMPILE_DYNAMIC_HELPER_INCLUDED
#define	CPPAD_CG_LINUX_C_LANG_COMPILE_DYNAMIC_HELPER_INCLUDED
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2012 Ciengis

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Common Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */
#ifdef __linux__

namespace CppAD {

    template<class Base>
    DynamicLib<Base>* CLangCompileDynamicHelper<Base>::loadDynamicLibrary() {
        return new LinuxDynamicLib<Base > (_libraryName);
    }

}
#endif

#endif