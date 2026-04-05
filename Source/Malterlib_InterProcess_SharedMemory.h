// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NInterProcess
{
	class CSharedMemory
	{
		void *m_pHandle;
		void *m_pMemory;
		CSharedMemory(CSharedMemory const &);
		CSharedMemory &operator = (CSharedMemory const &);
		void fp_Destroy()
		{
			if (m_pHandle)
				NSys::fg_InterProcess_MemFree(m_pHandle, m_pMemory);
		}
	public:
		CSharedMemory(CSharedMemory &&_Other)
			: m_pHandle(_Other.m_pHandle)
			, m_pMemory(_Other.m_pMemory)
		{
			_Other.m_pHandle = nullptr;
			_Other.m_pMemory = nullptr;
		}
		CSharedMemory &operator = (CSharedMemory &&_Other)
		{
			fp_Destroy();
			m_pHandle = _Other.m_pHandle;
			m_pMemory = _Other.m_pMemory;
			_Other.m_pHandle = nullptr;
			_Other.m_pMemory = nullptr;
			return *this;
		}
		CSharedMemory()
			: m_pHandle(nullptr)
			, m_pMemory(nullptr)
		{
		}
		CSharedMemory(ch8 const *_pName, umint _Size)
			: m_pHandle(nullptr)
		{
			m_pHandle = NSys::fg_InterProcess_MemAlloc(_pName, _Size, m_pMemory);
		}
		~CSharedMemory()
		{
			fp_Destroy();
		}

		void *f_GetMem()
		{
			return m_pMemory;
		}

		void const *f_GetMem() const
		{
			return m_pMemory;
		}

		operator void *() const
		{
			return m_pMemory;
		}

		void *f_GetHandle() const
		{
			return m_pHandle;
		}
	};

	template <typename t_CType>
	class TCSharedMemory : protected CSharedMemory
	{
	public:
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
