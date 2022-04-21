#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>
using namespace std;

//Custom definitions
#define newl "\n"
#define forl(i, a, n) for(int i = a; i < n; i++)

//Class Prototypes
class MergeSort;
class RankedSort;

//Function Prototypes
void TestSortingAlgorithms(vector<int> arr);
void PrintArr(vector<int> arr, string start = "ARRAY: ", string end = newl);
void PrintTestResults(map<double, string> table);
vector<int> RandomArr(int n);
vector<int> InputArr();

int main()
{
	int opt;
	cout << "Do you want to give a custom array (1) or a randomly generated array (any number)?: ";
	cin >> opt;
	
	vector<int> unsortedArr;
	
	if (opt == 1) unsortedArr = InputArr();
	else
	{
		int arraySize;
		cout << "Enter the size of the array to be generated: ";
		cin >> arraySize;
		unsortedArr = RandomArr(arraySize);
	}
	
	TestSortingAlgorithms(unsortedArr);
	PrintArr(unsortedArr, "Unsorted Array:\n");

	return 0;
}

//Merge Sort Algorithm
class MergeSort
{
private:
	vector<int> arr;
public:
	void SetUnsortedArr(vector<int> unsortedArr)
	{
		arr = unsortedArr;
	}

	vector<int> GetArr()
	{
		return arr;
	}

	void Merge(int low, int mid, int high)
	{
		int n1 = mid - low + 1;
		int n2 = high - mid;

		vector<int> a(n1), b(n2);

		forl(i, 0, n1) a[i] = arr[low + i];
		forl(i, 0, n2) b[i] = arr[mid + 1 + i];

		int i = 0;
		int j = 0;
		int k = low;

		while (i < n1 && j < n2)
		{
			if (a[i] < b[j])
			{
				arr[k] = a[i];
				i++;
			}
			else
			{
				arr[k] = b[j];
				j++;
			}
			k++;
		}

		while (i < n1)
		{
			arr[k] = a[i];
			i++; k++;
		}

		while (j < n2)
		{
			arr[k] = b[j];
			j++; k++;
		}
	}

	void Sort(int low, int high)
	{
		if (low < high)
		{
			int mid = low + (high - low) / 2;
			Sort(low, mid);
			Sort(mid + 1, high);

			Merge(low, mid, high);
		}
	}
};

class RankedSort
{
private:
	vector<int> arr;
public:
	void SetUnsortedArr(vector<int> unsortedArr)
	{
		arr = unsortedArr;
	}

	vector<int> GetArr()
	{
		return arr;
	}

	void Sort()
	{
		int n = arr.size();
		vector<int> ranks(n, 0);
		vector<int> sortedArr(n);
		forl(i, 1, n)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (arr[i] >= arr[j]) ranks[i]++;
				else ranks[j]++;
			}
		}

		forl(i, 0, n)
		{
			sortedArr[ranks[i]] = arr[i];
		}

		arr = sortedArr;
	}
};

vector<int> InputArr()
{
	cout << "Enter the size of the Array: " << newl;
	int n;
	cin >> n;

	vector<int> arr(n);
	forl(i, 0, n) cin >> arr[i];

	return arr;
}

void PrintArr(vector<int> arr, string start, string end)
{
	int n = arr.size();
	cout << start;
	forl(i, 0, n) cout << arr[i] << " ";
	cout << end;
}

vector<int> RandomArr(int n)
{
	srand((int)time(0));
	vector<int> arr(n);
	forl(i, 0, n) arr[i] = rand() * rand() * (1 + (rand() % (2 - 1 + 1)));
	return arr;
}

void TestSortingAlgorithms(vector<int> arr)
{
	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	using chrono::duration;
	using chrono::milliseconds;

	map<double, string> table;
	int low = 0, high = arr.size() - 1;

	//Testing MergeSort
	MergeSort mergeSort;
	mergeSort.SetUnsortedArr(arr);

	auto t1 = high_resolution_clock::now();
	mergeSort.Sort(low, high);
	auto t2 = high_resolution_clock::now();

	duration<double, milli> timeTaken = t2 - t1;
	table[timeTaken.count()] = "Merge Sort";

	//Testing RankedSort
	RankedSort rankedSort;
	rankedSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	rankedSort.Sort();
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Ranked Sort";

	//Testing std::sort()
	vector<int> unsortedArr = arr;
	t1 = high_resolution_clock::now();
	sort(unsortedArr.begin(), unsortedArr.end());
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "C++ STL sort()";

	//Printing Results
	PrintTestResults(table);
}

void PrintTestResults(map<double, string> table)
{
	cout << newl;
	forl(i, 0, 25) cout << '-';
	cout << "RESULTS";
	forl(i, 0, 25) cout << '-';
	cout << newl << newl;

	for (auto row : table) cout << row.second << " = " << row.first << "ms\n";
	
	cout << newl;
	forl(i, 0, 57) cout << '-';
	cout << newl;
}