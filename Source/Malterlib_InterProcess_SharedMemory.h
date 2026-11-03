// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NInterProcess
{
	struct CSharedMemory
	{
		CSharedMemory(CSharedMemory &&_Other)
			: mp_pHandle(_Other.mp_pHandle)
			, mp_pMemory(_Other.mp_pMemory)
		{
			_Other.mp_pHandle = nullptr;
			_Other.mp_pMemory = nullptr;
		}

		CSharedMemory &operator = (CSharedMemory &&_Other)
		{
			fp_Destroy();
			mp_pHandle = _Other.mp_pHandle;
			mp_pMemory = _Other.mp_pMemory;
			_Other.mp_pHandle = nullptr;
			_Other.mp_pMemory = nullptr;
			return *this;
		}

		CSharedMemory()
			: mp_pHandle(nullptr)
			, mp_pMemory(nullptr)
		{
		}

		CSharedMemory(ch8 const *_pName, umint _Size)
			: mp_pHandle(nullptr)
		{
			mp_pHandle = NSys::fg_InterProcess_MemAlloc(_pName, _Size, mp_pMemory);
		}

		~CSharedMemory()
		{
			fp_Destroy();
		}

		void *f_GetMem()
		{
			return mp_pMemory;
		}

		void const *f_GetMem() const
		{
			return mp_pMemory;
		}

		operator void * () const
		{
			return mp_pMemory;
		}

		void *f_GetHandle() const
		{
			return mp_pHandle;
		}

	private:
		void *mp_pHandle;
		void *mp_pMemory;
		CSharedMemory(CSharedMemory const &_Other);
		CSharedMemory &operator = (CSharedMemory const &_Other);
		void fp_Destroy()
		{
			if (mp_pHandle)
				NSys::fg_InterProcess_MemFree(mp_pHandle, mp_pMemory);
		}
	};

	template <typename t_CType>
	struct TCSharedMemory : protected CSharedMemory
	{
		using CSharedMemory::f_GetHandle;
		TCSharedMemory(ch8 const *_pName)
			: CSharedMemory(_pName, sizeof(t_CType))
		{
		}

		TCSharedMemory()
		{
		}

		t_CType &f_Get()
		{
			return *((t_CType *)this->f_GetMem());
		}

		t_CType const &f_Get() const
		{
			return *((t_CType const *)this->f_GetMem());
		}
	};
}

#ifndef DMibPNoShortCuts
using namespace NMib::NInterProcess;
#endif
