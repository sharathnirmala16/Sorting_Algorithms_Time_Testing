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
class BubbleSort;
class SelectionSort;
class InsertionSort;
class QuickSort;

//Function Prototypes
void TestSortingAlgorithms(vector<int> arr, bool trace = false);
void PrintArr(vector<int> arr, string start = "ARRAY: ", string end = newl, string separator = " ");
void PrintTestResults(map<double, string> table);
vector<int> RandomArr(int n);
vector<int> InputArr();

int main()
{
	int opt;
	cout << "Do you want to give a custom array (1) or a randomly generated array (any number)?: ";
	cin >> opt;
	
	vector<int> unsortedArr;
	
	if (opt == 1)
	{
		unsortedArr = InputArr();
	}

	else
	{
		int arraySize;
		cout << "Enter the size of the array to be generated: ";
		cin >> arraySize;
		unsortedArr = RandomArr(arraySize);
	}

	bool trace;
	cout << "Do you want the tracing output (Yes: 1/ No: 0)?: ";
	cin >> trace;
	TestSortingAlgorithms(unsortedArr, trace);

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

	void Sort(int low, int high, bool trace)
	{
		if (low < high && trace == true)
		{
			int mid = low + (high - low) / 2;
			Sort(low, mid, trace);
			Sort(mid + 1, high, trace);

			Merge(low, mid, high);
			PrintArr(arr, "Array: ");
		}

		if (low < high && trace == false)
		{
			int mid = low + (high - low) / 2;
			Sort(low, mid, trace);
			Sort(mid + 1, high, trace);

			Merge(low, mid, high);
		}
	}
};

//Ranked Sort Algorithm
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

	void Sort(bool trace)
	{
		if (trace)
		{
			cout << "Tracing Ranked Sort:\n";
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
				PrintArr(arr, "Array: ");
				PrintArr(ranks, "Ranks: ");
			}

			forl(i, 0, n)
			{
				sortedArr[ranks[i]] = arr[i];
			}

			arr = sortedArr;
		}

		else
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
	}
};

//Bubble Sort Algorithm
class BubbleSort
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

	void Sort(bool trace)
	{
		if (trace)
		{
			cout << "Tracing Bubble Sort:\n";
			int n = arr.size();
			forl(i, 0, n - 1)
			{
				forl(j, 0, n - i - 1)
				{
					if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
				}
				PrintArr(arr, "Array: ");
			}
		}

		else
		{
			int n = arr.size();
			forl(i, 0, n - 1)
			{
				forl(j, 0, n - i - 1)
				{
					if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
};

class SelectionSort
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

	void Sort(bool trace)
	{
		if (trace)
		{
			cout << "Tracing Selection Sort:\n";
			int n = arr.size();
			forl(step, 0, n - 1)
			{
				int minIndex = step;
				forl(i, step + 1, n)
				{
					if (arr[i] < arr[minIndex]) minIndex = i;
				}
				swap(arr[minIndex], arr[step]);
				PrintArr(arr, "Array: ");
			}
		}

		else
		{
			int n = arr.size();
			forl(step, 0, n - 1)
			{
				int minIndex = step;
				forl(i, step + 1, n)
				{
					if (arr[i] < arr[minIndex]) minIndex = i;
				}
				swap(arr[minIndex], arr[step]);
			}
		}
	}
};

class InsertionSort
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

	void Sort(bool trace)
	{
		if (trace)
		{
			cout << "Tracing Insertion Sort:\n";
			int key, j, n = arr.size();
			forl(i, 1, n)
			{
				key = arr[i];
				j = i - 1;

				while (j >= 0 && arr[j] > key)
				{
					arr[j + 1] = arr[j];
					j = j - 1;
				}
				arr[j + 1] = key;
				PrintArr(arr, "Array: ");
			}
		}

		else
		{
			int key, j, n = arr.size();
			forl(i, 1, n)
			{
				key = arr[i];
				j = i - 1;

				while (j >= 0 && arr[j] > key)
				{
					arr[j + 1] = arr[j];
					j = j - 1;
				}
				arr[j + 1] = key;
			}
		}
	}
};

class QuickSort
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

	int partition(int low, int high)
	{
		int pivot = arr[high];
		int i = low - 1;
		
		forl(j, low, high - 1)
		{
			if (arr[j] < pivot)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return ++i;
	}

	void Sort(int low, int high, bool trace)
	{
		if (low < high && trace == true)
		{
			int pi = partition(low, high);

			Sort(low, pi - 1, trace);
			Sort(pi + 1, high, trace);
			PrintArr(arr, "Array: ");
		}

		if (low < high && trace == false)
		{
			int pi = partition(low, high);

			Sort(low, pi - 1, trace);
			Sort(pi + 1, high, trace);
		}
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

void PrintArr(vector<int> arr, string start, string end, string separator)
{
	int n = arr.size();
	cout << start;
	forl(i, 0, n) cout << arr[i] << separator;
	cout << end;
}

vector<int> RandomArr(int n)
{
	srand((int)time(0));
	vector<int> arr(n);
	forl(i, 0, n) arr[i] = rand() * rand() * (1 + (rand() % (2 - 1 + 1)));
	return arr;
}

void TestSortingAlgorithms(vector<int> arr, bool trace)
{
	using chrono::high_resolution_clock;
	using chrono::duration_cast;
	using chrono::duration;
	using chrono::milliseconds;

	map<double, string> table;
	int low = 0, high = arr.size() - 1;

	//Testing MergeSort
	if (trace) cout << "Tracing Merge Sort:\n";
	MergeSort mergeSort;
	mergeSort.SetUnsortedArr(arr);

	auto t1 = high_resolution_clock::now();
	mergeSort.Sort(low, high, trace);
	auto t2 = high_resolution_clock::now();

	duration<double, milli> timeTaken = t2 - t1;
	table[timeTaken.count()] = "Merge Sort";

	//Testing RankedSort
	RankedSort rankedSort;
	rankedSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	rankedSort.Sort(trace);
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Ranked Sort";

	//Testing BubbleSort
	BubbleSort bubbleSort;
	bubbleSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	bubbleSort.Sort(trace);
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Bubble Sort";

	//Testing InsertionSort
	InsertionSort insertionSort;
	insertionSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	insertionSort.Sort(trace);
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Insertion Sort";

	//Testing SelectionSort
	SelectionSort selectionSort;
	selectionSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	selectionSort.Sort(trace);
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Selection Sort";

	//Testing QuickSort
	if (trace) cout << "Tracing Quick Sort:\n";
	QuickSort quickSort;
	quickSort.SetUnsortedArr(arr);

	t1 = high_resolution_clock::now();
	quickSort.Sort(low, high, trace);
	t2 = high_resolution_clock::now();

	timeTaken = t2 - t1;
	table[timeTaken.count()] = "Quick Sort";

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