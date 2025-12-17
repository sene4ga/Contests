#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& segments, int left, int mid,
           int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<std::pair<int, int>> l_segments(n1);
  std::vector<std::pair<int, int>> r_segments(n2);
  for (int i = 0; i < n1; i++) {
    l_segments[i] = segments[left + i];
  }
  for (int i = 0; i < n2; i++) {
    r_segments[i] = segments[mid + 1 + i];
  }
  int i = 0;
  int j = 0;
  int k = left;
  while (i < n1 && j < n2) {
    if (l_segments[i].first < r_segments[j].first ||
        (l_segments[i].first == r_segments[j].first &&
         l_segments[i].second < r_segments[j].second)) {
      segments[k] = l_segments[i];
      i++;
    } else {
      segments[k] = r_segments[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    segments[k] = l_segments[i];
    i++;
    k++;
  }
  while (j < n2) {
    segments[k] = r_segments[j];
    j++;
    k++;
  }
}

void MergeSort(std::vector<std::pair<int, int>>& segments, int left,
               int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    MergeSort(segments, left, mid);
    MergeSort(segments, mid + 1, right);
    Merge(segments, left, mid, right);
  }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> segments(n);

  for (int i = 0; i < n; i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }
  MergeSort(segments, 0, n - 1);
  std::vector<std::pair<int, int>> res;
  int current_l = segments[0].first;
  int current_r = segments[0].second;
  for (int i = 1; i < n; i++) {
    int l = segments[i].first;
    int r = segments[i].second;
    if (l <= current_r) {
      if (r > current_r) {
        current_r = r;
      }
    } else {
      res.push_back(std::make_pair(current_l, current_r));
      current_l = l;
      current_r = r;
    }
  }

  res.push_back(std::make_pair(current_l, current_r));

  std::cout << res.size() << std::endl;
  for (size_t i = 0; i < res.size(); i++) {
    std::cout << res[i].first << ' ' << res[i].second << std::endl;
  }
}
