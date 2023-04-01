#include <iostream>
#include <vector>
#include <string>
#include <list>

// Fibonacci(n)
// f(0) = 0, f(1) = 1
// f(2) = f(0) + f(1)

int64_t fibonacci(int n)
{
	if (n == 0)
	{
		return 0;
	}

	// 1. 0 ~ n 까지의 배열
	std::vector<int64_t> table(n + 1);          // 0번 인덱스 ~ n번 인덱스
   
	// 2. 초기화 (base case)
	table[1] = 1;

	// 3. 영향을 전파
	for (int i = 0; i <= n; i++)
	{
		if (i + 1 <= n)
		{
			table[i + 1] += table[i];
		}
		if (i + 2 <= n)
		{
			table[i + 2] += table[i];
		}
	}

	return table[n];
}
// Time Complexity : O(n)
// Space Complexity : O(n)

//-------------------------------------------------------------------------------------------

// 경로 찾기
// m행 n열이 있을 때, 좌상단에서 출발해서 우하단으로 이동할 수 있는 경우의 수
// 오른쪽, 아래로만 이동 가능

int64_t FindWays(int m, int n)
{   
	// 1. 0 ~ m행, 0 ~ n열을 std::vector로

	// std::vector (2, 1)
	// = {1, 1}
	std::vector<std::vector<int>> table( m + 1, std::vector<int>(n + 1) );  // (크기, 원소의 값)
	// 원소가 std::vector<int>이고 크기가 n + 1개인 배열을 원소로 가지는 배열


	// 2. base case 채우기
	table[1][1] = 1;

	// 3. 영향력 전파
	for (int row = 0; row <= m; row++)
	{
		for (int col = 0; col <= n; col++)
		{
			if (row + 1 <= m)
			{
				table[row + 1][col] += table[row][col];
			}
			if (col + 1 <= n)
			{
				table[row][col + 1] += table[row][col];
			} 
		}
	}

	return table[m][n];
}
// Time Complexity : O(m * n)
// Space Complexity : O(m * n)          배열의 크기 m행 n열

//----------------------------------------------------------------------------------------------------
using int_vector = std::vector<int>;

bool DecisionAccum(int sum, const int_vector& numbers)
{
	// 1. 배열 만들기
	std::vector<bool> table(sum + 1, bool{});

	// 2. 풀 수 있는 base case
	table[0] = true;

	// 3. 영향 펼치기
	for (int i = 0; i <= sum; i++)
	{
		if (table[i] == false)
		{
			continue;
		}

		for (auto e : numbers)
		{
			if (i + e <= sum)
			{
				table[i + e] = true;        // table[i + e] = table[i] 와 같음
			}
		}
	}

	return table[sum];
}
// m = sum, n = numbers갯수
// Time Complexity : O(m * n)
// Space Complexity : O(m)
//-------------------------------------------------------------------------------------------------


std::shared_ptr<int_vector> CombinationAccum(int sum, const int_vector& numbers)
{
	// 1. 배열 만들기
	std::vector<std::shared_ptr<int_vector>> table(sum + 1, nullptr);

	// 2. base case
	table[0] = std::make_shared<int_vector>(0);         // table[0]에 {}을 넣음

	// 3. 영향 펼치기
	for (int i = 0; i <= sum; i++)
	{
		if (table[i] != nullptr)
		{
			for (auto e : numbers)
			{
				/* 복사생성자
				int_vector v1;
				int_vector v2(v1);

				int_vector* v1;
				int_vector* v2 = new int_vector(*v1);
				*/
				if (i + e <= sum)
				{
					table[i + e] = std::make_shared<int_vector>(*table[i]);     // <주의!> 복사 후 대입
					table[i + e]->push_back(e);
				}
			}
		}
	}

	return table[sum];
}
// m = sum, n = numbers갯수
// Time Complexity : O(m ^ 2 * n)
// Space Complexity : O(m ^ 2)
//-----------------------------------------------------------------------------------------------------------


std::shared_ptr<int_vector> OptimizationAccum(int sum, const int_vector& numbers)
{
	// 1. 배열 만들기
	std::vector<std::shared_ptr<int_vector>> table(sum + 1, nullptr);
	
	// 2. base case
	table[0] = std::make_shared<int_vector>(0);

	// 3. 영향 펼치기
	for (int i = 0; i <= sum; i++)
	{
		if (table[i] != nullptr)
		{
			for (auto e : numbers)
			{
				if (i + e <= sum)
				{
					if (table[i + e] == nullptr || table[i + e]->size() > (table[i]->size() + 1))
					{ // 더 짧은 것을 추가해야하는데, 사이즈 비교 시, push_back을 할 예정이기 때문에 +1 해야함
						table[i + e] = std::make_shared<int_vector>(*table[i]);
						table[i + e]->push_back(e);
					}
				}
			}
		}
	}

	return table[sum];
}
// m = sum, n = numbers갯수
// Time Complexity : O(m ^ 2 * n)
// Space Complexity : O(m ^ 2)
//--------------------------------------------------------------------------------------------

using string_vector = std::vector<std::string>;

bool DecisionGenerate(const std::string target, const string_vector& stringList)
{
	// 1. 배열 만들기
	std::vector<bool> table(target.length() + 1, false);

	// 2. base case
	table[0] = true;

	// 3. 영향 펼치기
	for (int i = 0; i <= target.length(); i++)
	{
		if (table[i])
		{
			for (auto e : stringList)
			{
				if (target.substr(i, e.length()) == e)      // substr = 부분문자열   (i부터 시작해 length만큼)
				{
					if (i + e.length() <= target.length())
					{
						table[i + e.length()] = true;
					}
				}      
			}
		}
	}

	return table[target.length()];
}
// m = target.length(), n = stringlist 원소갯수
// Time Complexity : O(m ^ 2 * n)
// Space Complexity : O(m)
//--------------------------------------------------------------------------------------------

int CombinationGenerate(const std::string target, const string_vector& stringList)
{
	// 1. 배열 만들기
	int_vector table(target.length() + 1, 0);

	// 2. base case
	table[0] = 1;

	// 3. 영향 펼치기
	for (int i = 0; i <= target.length(); i++)
	{
		if (table[i] > 0)
		{
			for (auto e : stringList)
			{
				if (target.substr(i, e.length()) == e)
				{
					if (i + e.length() <= target.length())
					{
						table[i + e.length()] += table[i];
					}
				}
			}
		}
	}

	return table[target.length()];
}
// m = target.length(), n = stringlist 원소갯수
// Time Complexity : O(m ^ 2 * n)
// Space Complexity : O(m)
// DecisionGenerate 와 동일
//------------------------------------------------------------------------------------------------------

// std::vector<std::list<std::list<std::string>>> table
using string_list = std::list<std::string>;
using result = std::list<string_list>;

result CombinationGenerateAll(const std::string target, const string_list& stringList)
{
	// 1. 배열 만들기
	std::vector<result> table(target.length() + 1);

	// 2. base case
	table[0] = { {} };          // 유니폼 초기화식 안쓰면, table[0] = result { {} };

	// 3. 영향 펼치기
	for (int i = 0; i <= target.length(); i++)
	{
		if (table[i].size() > 0)
		{
			for (auto e : stringList)
			{
				if (target.substr(i, e.length()) == e)
				{
					for (auto e2 : table[i])
					{
						e2.push_back(e);

						table[i + e.length()].push_back(e2);
					}
				}
			}
		}
	}

	return table[target.length()];
}
// m = target.length(), n = stringlist 원소갯수
// Time Complexity : O(n ^ m)				// for (auto e2 : table[i])의 최악의 경우의 수
											//  = target이 "aaaaa", list가 "a" = m 만큼
											//	마치 n을 m번 늘어놓는 느낌이다.

// Space Complexity : O(m ^ 2)				// list<list<string>>
											// m개의 배열을 m만큼 최대 존재
//------------------------------------------------------------------------------------------------------

void Print(std::shared_ptr<int_vector> v)
{
	std::cout << "{";
	if (v)
	{
		for (auto e : *v)
		{
			std::cout << e << ", ";
		}
	}
	std::cout << "}" << std::endl;
}

void Print(const result& r)				// 이차 배열을 출력하는 코드
{
	std::cout << "{" << std::endl;

	for (auto e1 : r)
	{
		std::cout << "\t{ ";
		for (auto e2 : e1)
		{
			std::cout << e2 << ", ";
		}
		std::cout << "}," << std::endl;
	}

	std::cout << "}" << std::endl;
}

int main()
{
	std::cout << fibonacci(50) << std::endl;
	// n의 크기가 커져도 전혀 문제없다.
	// 위의 heap을 이용한 코드가 이미 Dynamic Programming이다!

	std::cout << FindWays(20, 20) << std::endl;

	std::cout << DecisionAccum(8, { 2, 3, 5 }) << std::endl;

	Print(CombinationAccum(8, { 2, 3, 5 }));
	Print(OptimizationAccum(8, { 2, 3, 5 }));

	std::cout << DecisionGenerate("abcdef", { "ab", "abc", "cd", "def", "abcd" }) << std::endl;
	std::cout << CombinationGenerate("abcdef", { "ab","a", "b", "c", "abc", "cd", "def", "abcd"}) << std::endl;
   
	Print(CombinationGenerateAll("abcdef", { "ab","a", "b", "c", "abc", "cd", "def", "abcd" }));
}
