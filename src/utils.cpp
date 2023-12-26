#include "../include/utils.hpp"

std::vector<int> createVector(int begin, int end){
  std::vector<int> vec(end-begin+1);
  // fills the vector from 1 to N
  std::iota(vec.begin(), vec.end(), begin);
  return vec;
}


template<typename T>
void printVector(const T& t) {
    for (const auto& elem : t) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template void printVector(const std::vector<int>& t);
template void printVector(const std::vector<double>& t);

template<typename T>
void printVector2D(const T& vec) {
    for (const auto& row : vec) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

template void printVector2D(const std::vector<std::vector<int>>& t);
template void printVector2D(const std::vector<std::vector<double>>& t);

template<typename T>
void printVector3D(const T& vec3) {
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

template void printVector3D(const std::vector<std::vector<std::vector<int>>>& t);
template void printVector3D(const std::vector<std::vector<std::vector<double>>>& t);

template<typename T>
void printVector4D(const T& vec4) {
    for (const auto& vec3 : vec4) {
        for (const auto& vec2 : vec3) {
            for (const auto& vec1 : vec2) {
                for (const auto& num : vec1) {
                    std::cout << num << " ";
                }
                std::cout << "| ";
            }
            std::cout << std::endl;
        }
        std::cout << "--------" << std::endl; // Separate each 3D slice
    }
}

template void printVector4D(const std::vector<std::vector<std::vector<std::vector<int>>>>& t);
template void printVector4D(const std::vector<std::vector<std::vector<std::vector<double>>>>& t);


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


void sortVec3_lexi(IntVector3D& vec3) {
    for (auto& vec2 : vec3) {
        for (auto& vec1 : vec2) {
            std::sort(vec1.begin(), vec1.end());
        }
        std::sort(vec2.begin(), vec2.end());
    }

    std::sort(vec3.begin(), vec3.end(), [](const auto& a, const auto& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    });

    vec3.erase(std::unique(vec3.begin(), vec3.end()), vec3.end());
}


IntVector2D flattenVec3ToVec2(const IntVector3D& vec3) {
  IntVector2D flattenedVec2;
  for (const auto& vec2 : vec3) {
    for (const auto& vec1 : vec2) {
      // Merge the inner vectors into a single vector
      flattenedVec2.push_back(vec1);
    }
  }
  return flattenedVec2;
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

// IntVector2D pathConfig(int paths, int nleaves, int n_ones){
//   return filterVectors(partition(paths, nleaves),n_ones);
// }

// IntVector2D pathConfigSplits(int paths, int nleaves, int n_ones){
//   IntVector2D paths_config_splits;
//   IntVector2D paths_config = pathConfig(paths, nleaves, n_ones);
//   for (int i = 0; i < paths_config.size(); i++){
//     std::vector<int> paths_split = cumulative(paths_config[i]);			
//     paths_config_splits.push_back(paths_split);
//   }
//   return paths_config_splits;
// }


// Function to generate all path configurarions on n leaves of the total number of nodes on the paths
IntVector3D leafPaths(int n_paths, int n_leaves, int total_path_nodes, int n_ones){
    // different configuratios for possible number of paths for each leaf from nleaves
    std::vector<std::vector<int>> paths_config = filterVectors(partition(n_paths, n_leaves),n_ones);
    // std::vector<std::vector<int>> paths_config = filterVectors(partition(total_path_nodes, n_leaves),n_ones);
    // std::vector<std::vector<int>> paths_config = filterVectors(partition(total_path_nodes, n_paths),n_ones);
    
    // splitting configurartions of the paths for each leaf
    std::vector<std::vector<int>> paths_config_splits;
    for (int i = 0; i < paths_config.size(); i++){
      std::vector<int> paths_split = cumulative(paths_config[i]);			
      paths_config_splits.push_back(paths_split);
    }

    // different configuratios for number of nodes for each path
    IntVector2D path_nodes = filterVectors(partition(total_path_nodes, n_paths),0);
    // permutations of different configuratios for number of nodes for each path
    IntVector3D nodes_paths_perm_3d;
    for (int i = 0; i < path_nodes.size(); i++){
      IntVector2D perm = permutations(path_nodes[i]);
      nodes_paths_perm_3d.push_back(perm);
    }
    
    // flatten the 3d vector to 2d
    IntVector2D nodes_paths_perm_2d = flattenVec3ToVec2(nodes_paths_perm_3d);
    
    // filter and slice the permutations to get the ones that are valid
    IntVector3D leaf_paths;
    
    for (int i = 0; i < paths_config_splits.size(); i++){
      std::vector<int> paths_config_split = paths_config_splits[i];
      for (int j = 0; j < nodes_paths_perm_2d.size(); j++ ){
	IntVector single_permutation = nodes_paths_perm_2d[j];
	IntVector2D leaf_paths_perm;	
	for (int k = 0; k < paths_config_split.size()-1; k++ ){
	  // slice the permutation into the leaf paths
	  IntVector spl = slicing(single_permutation, paths_config_split[k], paths_config_split[k+1]-1);
	  leaf_paths_perm.push_back(spl);
	}
	leaf_paths.push_back(leaf_paths_perm);
      }
    }
    sortVec3(leaf_paths);
    return leaf_paths;
}

// Function to generate all path configurarions on n leaves of the total number of nodes on the paths
IntVector3D findAllPaths(int V, int L, int V_central, int L_central, int n_ones){
  // Number of vertices on the paths from the central tree
  int V_paths = V - V_central; 
  // different configuratios for possible number of paths for each leaf from nleaves
  IntVector2D P_distr = partition(L, L_central);
  IntVector2D P_distr_1 = filterVectors(partition(L, L_central),n_ones);  
  std::vector<std::vector<int>> paths_config = filterVectors(partition(L, L_central),n_ones);
  
  // splitting configurartions of the paths for each leaf
  std::vector<std::vector<int>> paths_config_splits;
  for (int i = 0; i < paths_config.size(); i++){
    std::vector<int> paths_split = cumulative(paths_config[i]);			
    paths_config_splits.push_back(paths_split);
  }
  
  // different configuratios for the number of vertices for each path
  IntVector2D V_path = filterVectors(partition(V_paths, L),0);
  // permutations of different configuratios for number of nodes for each path
  IntVector3D nodes_paths_perm_3d;
  for (int i = 0; i < V_path.size(); i++){
    IntVector2D perm = permutations(V_path[i]);
    nodes_paths_perm_3d.push_back(perm);
  }
  
  // flatten the 3d vector to 2d
  IntVector2D nodes_paths_perm_2d = flattenVec3ToVec2(nodes_paths_perm_3d);
  
  // filter and slice the permutations to get the ones that are valid
  IntVector3D leaf_paths;
  
  for (int i = 0; i < paths_config_splits.size(); i++){
    std::vector<int> paths_config_split = paths_config_splits[i];
    for (int j = 0; j < nodes_paths_perm_2d.size(); j++ ){
      IntVector single_permutation = nodes_paths_perm_2d[j];
      IntVector2D leaf_paths_perm;	
      for (int k = 0; k < paths_config_split.size()-1; k++ ){
	// slice the permutation into the leaf paths
	IntVector spl = slicing(single_permutation, paths_config_split[k], paths_config_split[k+1]-1);
	leaf_paths_perm.push_back(spl);
      }
      leaf_paths.push_back(leaf_paths_perm);
    }
  }
  sortVec3_lexi(leaf_paths);
  return leaf_paths;
}



void createDirectory(std::string foldername) {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string directoryPath = mainDir + "/"+foldername;
  // Check if the directory already exists
  if (!fs::exists(directoryPath)) {
    // Create the directory
    if (fs::create_directory(directoryPath)) {
      std::cout << "Directory created successfully!" << std::endl;
    } else {
      std::cout << "Failed to create directory!" << std::endl;
    }
  } else {
    std::cout << "Directory already exists!" << std::endl;
  }
}

void deleteFilesInFolder(std::string foldername) {
  fs::path currentPath = fs::current_path();
  std::string pathAsString = currentPath.string();
  std::string mainDir = pathAsString + "/tex/tikz";
  std::cout << "Current directory: " << currentPath << std::endl;
  std::string directoryPath = mainDir + "/"+foldername;
  try {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.path())) {
	fs::remove(entry.path());
	std::cout << "Deleted: " << entry.path().string() << std::endl;
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
// std::vector<int> vecw(3);

    // // fills the vector from 1 to N
    // std::iota(vecw.begin(), vecw.end(), 1);

    // for (auto i: vecw)
    //   std::cout << i << ' ';
    // std::cout << '\n';
