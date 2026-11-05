// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NInterProcess
{
	struct CSharedMemory
	{
		CSharedMemory(CSharedMemory &&_Other);
		CSharedMemory();
		CSharedMemory(ch8 const *_pName, umint _Size);
		~CSharedMemory();

		CSharedMemory &operator = (CSharedMemory &&_Other);
		void *f_GetMem();
		void const *f_GetMem() const;
		operator void * () const;
		void *f_GetHandle() const;

	private:
		CSharedMemory(CSharedMemory const &_Other);

		CSharedMemory &operator = (CSharedMemory const &_Other);
		void fp_Destroy();

		void *mp_pHandle;
		void *mp_pMemory;
	};

	template <typename t_CType>
	struct TCSharedMemory : protected CSharedMemory
	{
		TCSharedMemory(ch8 const *_pName);
		TCSharedMemory();

		using CSharedMemory::f_GetHandle;
		t_CType &f_Get();
		t_CType const &f_Get() const;
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NInterProcess;
#endif

#include "Malterlib_InterProcess_SharedMemory.hpp"
