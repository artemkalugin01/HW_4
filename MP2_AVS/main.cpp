#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <omp.h>

using namespace std;
int lenght = 0;

void Console(int i, int j, int max) {
#pragma omp parallel{
    long total = (lenght - 1) * (lenght);
    long current = i * lenght + j;
    if (max != -2147483647 - 1) {
        auto total = (lenght - 1) * (lenght);
        auto current = i * lenght + j;
        cout << current << "/" << total << "\t current max: " << max << endl;
    } else {
        //cout << current << "/" << total << "\t current max: " << "Not counted" << endl;
    }
}

void UpdateCurrentMax(int &saved_max, int &saved_i, int &saved_j, int max, int i, int j) {
#pragma omp parallel{
    int a = 0;
    if (max > saved_max) {
        saved_max = max;
        saved_i = i;
        saved_j = j;
    }
}

void GetSum(vector<int> arr, int i, int j, int &saved_summ, int &saved_i, int &saved_j) {
    if (i < j) {
        int sum = arr[i];
        bool is_sum = false;
        int counter = i;
        while (counter < j) {
            if (is_sum) {
                sum += arr[counter];
                is_sum = !is_sum;
                counter += 1;
                saved_summ = sum;


            } else {
                sum -= arr[counter];
                is_sum = !is_sum;
                counter += 1;
                saved_summ = sum;

            }
        }
        saved_summ = sum;
        saved_j = j;
        saved_i = i;
    } else {
        saved_summ = INT_MIN;
    }

}

int main() {
    omp_set_num_threads(2);
    int result_sum, saved_max, saved_i, saved_j, Count;
    int ans_sum, ans_i, ans_j;
    ans_sum = INT_MIN;
    ans_i = -1;
    ans_j = -1;

    ifstream fin("input.txt");
    fin >> Count;
    vector<int> mass(Count);
    for (int i = 0; i < Count; ++i) {
        fin >> mass[i];
    }
    lenght = Count;
    if (Count < 10) {
        cout << "несоответствие условию программы" << endl << "Программа завершена.";
        return 1;
    }


    for (int i = 0; i < lenght; ++i) {
        cout << mass[i] << " ";
    }
    cout << endl;


    for (int i = 0; i < Count; ++i) {
        for (int j = 0; j < Count; ++j) {
            GetSum(mass, i, j, std::ref(saved_max), std::ref(saved_i), std::ref(saved_j));

            UpdateCurrentMax(std::ref(ans_sum), std::ref(ans_i), std::ref(ans_j), saved_max, saved_i, saved_j);

            Console(saved_i, saved_j, saved_max);
        }
        cout << endl;

    }

    cout << "\n\n\n" << "Current max: " << ans_sum << endl << "Best i: " << ans_i << endl << "Best j: " << ans_j
         << endl;
    ofstream output("output.txt");
    output << ans_i << " " << ans_j;


    return 0;
}
