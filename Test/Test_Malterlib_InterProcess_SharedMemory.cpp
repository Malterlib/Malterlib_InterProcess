// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/InterProcess/SharedMemory>

namespace
{
	using namespace NMib::NTest;

	class CMemory_Tests : public CTest
	{
	public:

		CMemory_Tests()
		{
		}

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				[[maybe_unused]] void *pMemory;
				NMib::NInterProcess::CSharedMemory SharedMem;
				try
				{
					SharedMem = NMib::NInterProcess::CSharedMemory("Global\\MalterlibSharedMemoryTest", 1024);
					pMemory = SharedMem;
				}
				catch (NMib::NException::CException const &)
				{
					try
					{
						SharedMem = NMib::NInterProcess::CSharedMemory("Local\\MalterlibSharedMemoryTest", 1024);
						pMemory = SharedMem;
					}
					catch (NMib::NException::CException const &)
					{
					}
				}
			};
		}
	};

	DMibTestRegister(CMemory_Tests, Malterlib::InterProcess);

}

