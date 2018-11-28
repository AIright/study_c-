//
// Created by alright on 23/11/18.
//

#ifndef STUDY_C_AVERAGETEMPERATURE_H
#define STUDY_C_AVERAGETEMPERATURE_H

#include <iostream>
#include <vector>

using namespace std;

int average_temperature() {
    int n;
    cin >> n;
    vector<int> temperatures(n);
    int64_t sum = 0;
    for (int& temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum / n;

    vector<int> above_average_indices;
    for (int i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            above_average_indices.push_back(i);
        }
    }

    cout << above_average_indices.size() << endl;
    for (int i : above_average_indices) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

#endif //STUDY_C_AVERAGETEMPERATURE_H