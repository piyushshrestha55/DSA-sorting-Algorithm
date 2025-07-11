#include<iostream>
#include <cstdlib> // to randomaize the array elements
#include<ctime> // For using time(0)
#include <chrono> // To determine the time searching the element
#include<algorithm>// To swap the array in different positions
using namespace std;
using namespace std::chrono;

//Binary Search
void binarySearch(int arr[],int left,int right, int target){
  while (left <= right)
  {
    int mid = left + (right-left)/2;
    if(arr[mid] == target){
      cout<<"The element is found at index "<<mid<<endl;
      return;
    }
    else if (arr[mid] < target)
    {
      left = mid + 1;
    }
    else{
      right = mid-1;
    }

  }
  cout<<"The element is not found."<<endl;; // For not found cases
}

//Exponential Search
void exponentialSearch(int arr[],int n , int target){
  if(n == 0){
    cout<<"The element is not found."<<endl;//for not found cases
    return;
  }
  else if(arr[0] == target){
    cout<<"The element is found at index 0."<<endl;
    return;
  }

  int i = 1;
  while (i < n && arr[i] < target)
  {
    i *= 2;
  }
  int left = i/2;
  int right = min(i,n-1);
  while (left <= right)
  {
    int mid = left + (right-left)/2;
    if(arr[mid] == target){
      cout<<"The element is found at index "<<mid<<endl;
      return;
    }
    else if (arr[mid] < target)
    {
      left = mid + 1;
    }
    else{
      right = mid-1;
    }

  }
  cout<<"The element is not found"<<endl;; //for not found cases

}

//Function for Getting random numbers to insert in n size array
void getRandomNumbers(int arr[],int n){
  srand(time(0));
  for(int i=0;i<n;i++){
      arr[i]=rand()%100;
  }
}


//Displaying the array elements
void displayArray(int arr[],int n){
  for(int i=0;i<n;i++){
      cout<<arr[i]<<" ";
  }
  cout<<endl;
}

//For Quick sort
int partition(int arr[], int low, int high) {
    // Median-of-three pivot selection
    int mid = low + (high - low) / 2;

    // Find median of arr[low], arr[mid], arr[high]
    if (arr[mid] < arr[low])
        swap(arr[mid], arr[low]);
    if (arr[high] < arr[low])
        swap(arr[high], arr[low]);
    if (arr[high] < arr[mid])
        swap(arr[high], arr[mid]);

    // Now arr[mid] is median — use as pivot
    swap(arr[mid], arr[high]);
    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int p = partition(arr, low, high);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
  }
}

//Merge Sort
void merge(int arr[], int left, int mid, int right){
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];

  for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main(){
  int n, target;
  cout<<"Enter the size of array you want:";
  cin>>n;
  int* arr = new int[n];
  int* arrMerge = new int[n];

  getRandomNumbers(arr, n);

// Clone into arr and arrMerge
  for (int i = 0; i < n; i++) {
      arrMerge[i] = arr[i];
  }

  cout<<"Unsorted Array:\n";
  displayArray(arr , n);

  // Start time
  auto quickStart = high_resolution_clock::now();
  //Quick Sort
  quickSort(arr , 0 , n-1);
  // End time
  auto quickStop = high_resolution_clock::now();

  // Duration in microseconds
  auto quickDuration = duration_cast<microseconds>(quickStop - quickStart);

  //sorting the array using quick sort
  cout<<"After quick sort:\n";
  displayArray(arr , n);
  cout<<"Time Taken by quick sorting : "<<quickDuration.count()<<" microseconds"<<endl;

  //start time
  auto mergeStart = high_resolution_clock::now();
  //Merge Sort
  mergeSort(arrMerge , 0 , n-1);
  //end time
  auto mergeStop = high_resolution_clock::now();

  //duration in ms
  auto mergeDuration = duration_cast<microseconds>(mergeStop - mergeStart);


  cout<<"After using merge sort:\n";
  displayArray(arrMerge , n);
  cout<<"Time Taken by merge sorting : "<<mergeDuration.count()<<" microseconds"<<endl;
  // Checking which sort is faster
  cout << (quickDuration < mergeDuration ? "Quick Sort was faster\n" : "Merge Sort was faster\n");

  cout << "\nEnter the number to be searched: ";
  cin >> target;
  cout<<endl;
  // Start time
  auto binaryStart = high_resolution_clock::now();
  //Binary Search
  binarySearch(arr , 0 , n-1 , target);

  // End time
  auto binaryStop = high_resolution_clock::now();

  // Duration in microseconds
  auto binaryDuration = duration_cast<microseconds>(binaryStop - binaryStart);

  cout<<"Time taken  by binary searching : "<< binaryDuration.count() <<" microseconds \n";

  //Exponential Searching.
  // Start time
  auto exponentialStart = high_resolution_clock::now();
  exponentialSearch(arrMerge ,n, target);

  // End time
  auto exponentialStop = high_resolution_clock::now();

  // Duration in microseconds
  auto exponentialDuration = duration_cast<microseconds>(exponentialStop - exponentialStart);

  cout<<"Time taken  by exponential searching : "<< exponentialDuration.count() <<" microseconds \n";
  //Checking which selection algorithm is faster
  cout << (binaryDuration < exponentialDuration ? "Binary Search was faster.\n" : "Exponential Search was faster.\n");
  return 0;
}
