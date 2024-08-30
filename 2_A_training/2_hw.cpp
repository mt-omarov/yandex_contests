#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <iterator>
#include <algorithm>


class A {
public:
	static void solution() {
		long int n, k, min_B, max_B, b;
		std::cin >> n >> k >> min_B;
		max_B = min_B;
		while (std::cin >> b) {
			if (b > max_B) {
				max_B = b;
			}
			if (b < min_B) {
				min_B = b;
			}
		}
		std::cout << max_B - min_B << '\n';
	}
};


class B {
private:
	// complexity: O((n + 1) * n / 2) –> O(n^2), where n = x.length()
	static std::vector<int> find_starts_of_substrs(const std::string &z, const std::string &x) {
		/*
			1. Compare strings from the end,
			treating each character starting with z[x.length() - 1] 
			as the end of a potential substring.

			2. Save each variant into a vector for further search of the best y:
			   E.g: x = kk, z = kkk. If we took the maximum substring, the answer would be 'k',
			   but the correct answer is ''.

		*/
		std::vector<int> starts;
		int end_z;
		if (z.size() < x.size()) {
			end_z = std::ssize(z) - 1;
		} else {
			end_z = std::ssize(x) - 1;
		}
		for (; end_z >= 0; --end_z) {
			if (z[end_z] != x.back()) {
				continue;
			}
			int start_z = end_z, i = std::ssize(x) - 1;
			while (start_z >= 0 && i >= 0 && z[start_z] == x[i]) {
				--start_z;
				--i;
			}
			if (start_z < 0) {
				starts.push_back(i + 1);
			}
		}
		return starts;
	}

	/* (if the task required to determine the smallest repeating subword)
	static int find_length_of_min_y(const std::string &z, const int &start_z) {
		int start_y = start_z, end_y = start_z, cur_y = start_y;
		while (cur_y < std::ssize(z) && z[cur_y] == z[start_y]) {
			++cur_y;
		}
		if (cur_y == std::ssize(z)) {
			return end_y - start_y + 1;
		}
		end_y = cur_y;
		cur_y = start_y;

		for (int i = end_y + 1; i < std::ssize(z); ++i) {
			if (cur_y > end_y) {
				cur_y = start_y;
			}
			if (z[i] == z[cur_y]) {
				++cur_y;
			} else {
				cur_y = start_y;
				end_y = i;
			}
		}

		return end_y - start_y + 1; // return length
	}
	*/

	// discard all repetitions of string x at the beginning start_z
	static int find_start_z(const std::string &z, const int &start_z, const std::string &x) {
		int cur_x = 0;
		int new_start_z = start_z, i;
		for (i = start_z; i < std::ssize(z); ++i) {
			if (cur_x == std::ssize(x)) {
				cur_x = 0;
				new_start_z = i;
			}
			if (x[cur_x] == z[i]) {
				++cur_x;
			} else {
				return new_start_z;
			}
		}

		if (start_z == std::ssize(z) || (cur_x > 0 && i > 0 && x[cur_x - 1] == z[i - 1] && i - new_start_z == std::ssize(x))) {
			return i;
		} else {
			return new_start_z;
		}
	}


public:
	static void solution() {
		std::string x, z;
		std::cin >> x >> z;
		
		int start_y = 0, length_y = std::ssize(z);
		const auto starts = find_starts_of_substrs(z, x);

		if (starts.empty()) {
			// length_y = find_length_of_min_y(z, start_y);
			std::cout << z.substr(start_y, length_y) << '\n';
			return;
		}

		for (const auto &start_x : starts) {
			int start_z = std::ssize(x) - start_x;
			int new_start_z = find_start_z(z, start_z, x);
			if (new_start_z == std::ssize(z)) {	
				start_y = 0;
				length_y = 0;
				break;
			}

			// int new_length_y = find_length_of_min_y(z, new_start_z);
			int new_length_y = std::ssize(z) - new_start_z;
			if (new_length_y < length_y) {
				length_y = new_length_y;
				start_y = new_start_z;
			}
		}

		std::cout << z.substr(start_y, length_y) << '\n';
	}
};


class C {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::map<int, std::unordered_set<int>> cols_in_rows;
		int row, col;
		while (std::cin >> row >> col) {
			if (!cols_in_rows.contains(row)) { 
				cols_in_rows.insert({ row, std::unordered_set<int>() });
			}
			cols_in_rows[row].insert(col);
		}

		int p = 0;
		if (cols_in_rows.size() == 1) {
			p = (cols_in_rows.begin()->second.size()) * 2 + 2;
			std::cout << p << '\n';
			return;
		}

		for (auto current_row = cols_in_rows.cbegin(); current_row != cols_in_rows.cend(); ++current_row) {
			int number_cells_adjacent_to_prev_row = 0;
			for (const auto &col : current_row->second) {
				if (current_row == cols_in_rows.cbegin() || !std::prev(current_row)->second.contains(col)) {
					++p;
				} else {
					++number_cells_adjacent_to_prev_row;
				}

				if (!current_row->second.contains(col - 1)) {
					++p;
				}

				if (!current_row->second.contains(col + 1)) {
					++p;
				}
			}
			if (current_row != cols_in_rows.cbegin()) {
				p += (std::ssize(std::prev(current_row)->second) - number_cells_adjacent_to_prev_row);
			}
		}
		p += cols_in_rows.crbegin()->second.size();

		std::cout << p << '\n';
	}
};


class D {
public:
	static void solution() {
		int n;
		std::cin >> n;
		std::vector ropes(n, 0);

		for (int l, i = 0; i < n; ++i) {
			std::cin >> l;
			ropes[i] = l;
		}

		std::sort(ropes.begin(), ropes.end());
		int s = 0;
		for (int i = 0; i < n - 1; ++i) {
			s += ropes[i];
		}

		if (ropes[n - 1] <= s) {
			std::cout << s + ropes[n - 1] << '\n';
		} else {
			std::cout << ropes[n - 1] - s << '\n';
		}
	}
};


int main() {
	B::solution();
}