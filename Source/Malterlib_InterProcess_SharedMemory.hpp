// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NInterProcess
{
	inline CSharedMemory::CSharedMemory(CSharedMemory &&_Other)
		: mp_pHandle(_Other.mp_pHandle)
		, mp_pMemory(_Other.mp_pMemory)
	{
		_Other.mp_pHandle = nullptr;
		_Other.mp_pMemory = nullptr;
	}

	inline CSharedMemory &CSharedMemory::operator = (CSharedMemory &&_Other)
	{
		fp_Destroy();
		mp_pHandle = _Other.mp_pHandle;
		mp_pMemory = _Other.mp_pMemory;
		_Other.mp_pHandle = nullptr;
		_Other.mp_pMemory = nullptr;
		return *this;
	}

	inline CSharedMemory::CSharedMemory()
		: mp_pHandle(nullptr)
		, mp_pMemory(nullptr)
	{
	}

	inline CSharedMemory::CSharedMemory(ch8 const *_pName, umint _Size)
		: mp_pHandle(nullptr)
	{
		mp_pHandle = NSys::fg_InterProcess_MemAlloc(_pName, _Size, mp_pMemory);
	}

	inline CSharedMemory::~CSharedMemory()
	{
		fp_Destroy();
	}

	inline void *CSharedMemory::f_GetMem()
	{
		return mp_pMemory;
	}

	inline void const *CSharedMemory::f_GetMem() const
	{
		return mp_pMemory;
	}

	inline CSharedMemory::operator void * () const
	{
		return mp_pMemory;
	}

	inline void *CSharedMemory::f_GetHandle() const
	{
		return mp_pHandle;
	}

	inline void CSharedMemory::fp_Destroy()
	{
		if (mp_pHandle)
			NSys::fg_InterProcess_MemFree(mp_pHandle, mp_pMemory);
	}

	template <typename t_CType>
	TCSharedMemory<t_CType>::TCSharedMemory(ch8 const *_pName)
		: CSharedMemory(_pName, sizeof(t_CType))
	{
	}

	template <typename t_CType>
	TCSharedMemory<t_CType>::TCSharedMemory()
	{
	}

	template <typename t_CType>
	t_CType &TCSharedMemory<t_CType>::f_Get()
	{
		return *((t_CType *)this->f_GetMem());
	}

	template <typename t_CType>
	t_CType const &TCSharedMemory<t_CType>::f_Get() const
	{
		return *((t_CType const *)this->f_GetMem());
	}
}
