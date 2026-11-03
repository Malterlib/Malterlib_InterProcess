// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NInterProcess
{
	struct CSharedMemory
	{
		CSharedMemory(CSharedMemory &&_Other);
		CSharedMemory &operator = (CSharedMemory &&_Other);
		CSharedMemory();
		CSharedMemory(ch8 const *_pName, umint _Size);
		~CSharedMemory();
		void *f_GetMem();
		void const *f_GetMem() const;
		operator void * () const;
		void *f_GetHandle() const;

	private:
		void *mp_pHandle;
		void *mp_pMemory;
		CSharedMemory(CSharedMemory const &_Other);
		CSharedMemory &operator = (CSharedMemory const &_Other);
		void fp_Destroy();
	};

	template <typename t_CType>
	struct TCSharedMemory : protected CSharedMemory
	{
		using CSharedMemory::f_GetHandle;
		TCSharedMemory(ch8 const *_pName);
		TCSharedMemory();
		t_CType &f_Get();
		t_CType const &f_Get() const;
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NInterProcess;
#endif

#include "Malterlib_InterProcess_SharedMemory.hpp"
