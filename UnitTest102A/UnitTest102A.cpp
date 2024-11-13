#include "pch.h"
#include "CppUnitTest.h"
#include "../10.2.A/10.2.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1023B
{
	TEST_CLASS(UnitTest1023B)

	{
	public:

		TEST_METHOD(TestSortAndBinarySearch)
		{
			const int n = 3;
			Student students[n] = {
				{"Itre", 2, KN, 4, 4, 5},
				{"Prag", 3, KN, 5, 3, 4},
				{"Sokal", 1, KN, 3, 5, 5}
			};


			sort_students(students, n);

			Assert::AreEqual(std::string("Itre"), students[0].prizv);
			Assert::AreEqual(2, students[0].kurs);
			Assert::AreEqual(5, students[0].mark_informatics);

			Assert::AreEqual(std::string("Sokal"), students[1].prizv);
			Assert::AreEqual(1, students[1].kurs);
			Assert::AreEqual(5, students[1].mark_informatics);

			Assert::AreEqual(std::string("Prag"), students[2].prizv);
			Assert::AreEqual(3, students[2].kurs);
			Assert::AreEqual(4, students[2].mark_informatics);

			int index = binary_search_student(students, n, "Itre", 2, 5);
			Assert::AreEqual(-1, index); 

			index = binary_search_student(students, n, "Prag", 3, 4);
			Assert::AreEqual(-1, index); 

			index = binary_search_student(students, n, "Sokal", 1, 5);
			Assert::AreEqual(1, index);

			
			index = binary_search_student(students, n, "Apanas", 2, 5);
			Assert::AreEqual(-1, index); 
		}
	};
}
