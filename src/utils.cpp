#include "../include/utils.hpp"

std::vector<int> createVector(int begin, int end){
  std::vector<int> vec(end-begin+1);
  // fills the vector from 1 to N
  std::iota(vec.begin(), vec.end(), begin);
  return vec;
}

void printVector(std::vector<int> vec){
  for (auto i : vec)
    std::cout << i << " ";
  std::cout << std::endl;
}

void printVectord(std::vector<double> vec){
  for (auto i : vec)
    std::cout << i << " ";
  std::cout << std::endl;
}

void print2DVector(const std::vector<std::vector<int>>& vec) {
    for (const auto& row : vec) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> slicing(std::vector<int>& arr, int X, int Y) {
    // Starting and Ending iterators
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
 
    // To store the sliced vector
    std::vector<int> result(Y - X + 1);
 
    // Copy vector using copy function()
    copy(start, end, result.begin());
 
    // Return the final sliced vector
    return result;
}

std::vector<int> cumulative(std::vector<int> oldList) {
  int n = oldList.size();
  std::vector<int> newList(n+1, 0);
 
  // Adding 1st element in the result list
  newList[0] = 0;
  newList[1] = oldList[0];
 
  // Adding current element in the cumulative list
  for (int i = 2; i < n+1; i++)
    newList[i] = oldList[i-1] + newList[i - 1];
 
  return newList;
}



void sortVec3(IntVector3D& vec3) {
    for (auto& vec2 : vec3) {
      std::sort(vec2.begin(), vec2.end());
        for (auto& vec1 : vec2) {
            std::sort(vec1.begin(), vec1.end());
        }
    }
    std::sort(vec3.begin(), vec3.end());
    vec3.erase(std::unique(vec3.begin(), vec3.end()), vec3.end());
}

void displayVec3(const IntVector3D& vec3) {
    for (const auto& vec2 : vec3) {
        for (const auto& vec1 : vec2) {
            for (int num : vec1) {
                std::cout << num << " ";
            }
            std::cout << "| ";
        }
        std::cout << std::endl;
    }
}

IntVector2D permutations(std::vector<int> vector){
    // Sorting the vector to get the initial permutation
    std::sort(vector.begin(), vector.end());

    IntVector2D allPermutations;

    // Finding permutations and storing them in a vector of vectors
    do {
        allPermutations.push_back(vector);
    } while (std::next_permutation(vector.begin(), vector.end()));
    
    return allPermutations;
}

void printPermutations(const IntVector2D& allPermutations){
    // Printing all permutations
    for (const auto& perm : allPermutations) {
        for (int num : perm) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << allPermutations.size() << std::endl;
}

// Main function to generate all permutations of a vector of sum n and length r
void part(int n, std::vector<int>& v, int level, int r, std::vector<std::vector<int>>& result) {
    int first; /* first is before last */

    if (n < 1) return;
    v[level] = n;
    if (level + 1 == r) {
      std::vector<int> temp(v.begin(), v.begin() + r); // Store only the first r elements
      result.push_back(temp); // Store the part in the result vector
      return;
    }

    if (level == 0) {
      first = 1;
    } else {
      first = v[level - 1];
    }

    // first = (level == 0) ? 1 : v[level - 1];

    for (int i = first; i <= n / 2; i++) {
        v[level] = i; /* replace last */
        part(n - i, v, level + 1, r, result);
    }
}

// Function to generate all partitions of a vector of sum n and length r (not necessary with v, level result as input)
std::vector<std::vector<int>> partition(int n, int r) {
  std::vector<int> v(n);
  std::vector<std::vector<int>> result;
  part(n, v, 0, r, result);
  return result;
}

IntVector2D filterVectors(const IntVector2D& vecOfVecs, int threshold) {
  IntVector2D filteredVecs;
  for (const auto& vec : vecOfVecs) {
    int countOnes = 0;
    for (int elem : vec) {
      if (elem == 1) {
	countOnes++;
      }
    }
    
    if (countOnes == 0 || countOnes > threshold) {
      filteredVecs.push_back(vec);
    }
    // if (countOnes > threshold) {
    //   filteredVecs.push_back(vec);
    // }
  }
  
  return filteredVecs;
}
// std::vector<int> vecw(3);

    // // fills the vector from 1 to N
    // std::iota(vecw.begin(), vecw.end(), 1);

    // for (auto i: vecw)
    //   std::cout << i << ' ';
    // std::cout << '\n';
