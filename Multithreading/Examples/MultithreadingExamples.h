#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class MultithreadingExamples
{
public:
    // Task 1: Returns a boolean.
    static bool is_prime(int n)
    {
        if (n <= 1) return false;

        for (int i = 2; i * i <= n; ++i)
        {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Task 2: Returns a double.
    static double calculate_average(const std::vector<double>& numbers)
    {
        if (numbers.empty()) return 0.0;
        return std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
    }

    // Task 3: Returns void.
    static void print_message(const std::string& msg, int delay_ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        std::cout << "Async message: " << msg << std::endl;
    }

    // Task 4: Returns an int.
    static int find_max_element(const std::vector<int>& data)
    {
        return *std::max_element(data.begin(), data.end());
    }

    // Task 5: Returns a std::pair.
    static std::pair<int, int> find_min_max(const std::vector<int>& data)
    {
        auto minmax = std::minmax_element(data.begin(), data.end());
        return {*minmax.first, *minmax.second};
    }

    // Task 6: Returns a vector.
    static std::vector<int> generate_fibonacci(int count)
    {
        std::cout << "Generating Fibonacci sequence of count " << count << "..." << std::endl;
        std::vector<int> result;
        if (count > 0) result.push_back(0);
        if (count > 1) result.push_back(1);
        for (int i = 2; i < count; ++i)
        {
            result.push_back(result[i - 1] + result[i - 2]);
        }

        std::cout << "Fibonacci sequence of count " << count << " complete." << std::endl;

        return result;
    }

    // Task 7: Returns a string.
    static std::string reverse_string(const std::string& s)
    {
        std::string reversed = s;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    // Task 8: Returns an int and uses a const reference parameter.
    static int count_vowels(const std::string& text)
    {
        int count = 0;
        std::string vowels = "aeiouAEIOU";
        for (char c : text)
        {
            if (vowels.find(c) != std::string::npos)
            {
                count++;
            }
        }
        return count;
    }

    // Task 9: Returns a double.
    static double power_of(double base, int exponent)
    {
        return std::pow(base, exponent);
    }

    // Task 10: Returns an int.
    static int factorial(int n)
    {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    }

    // ======================================================================
    // 5 New Long-Running CPU-Bound Tasks
    // ======================================================================

    // Task 11: Calculates Pi using a high-precision formula (e.g., Chudnovsky).
    static long double calculate_pi_chudnovsky(int iterations)
    {
        std::cout << "Starting Pi calculation with " << iterations << " iterations..." << std::endl;

        long double pi = 0.0;
        // This is a simplified, non-functional example to represent a long-running calculation.
        // A real implementation would use a big number library.
        long double term = 1.0;
        for (int k = 0; k < iterations; ++k)
        {
            term = term * (k * 2 + 1) / (k + 1);
            pi += term;
        }
        std::cout << "Pi calculation with " << iterations << " iterations complete." << std::endl;
        return pi;
    }

    // Task 12: Simulates a brute-force key search.
    static std::string find_password_brute_force(const std::string& target_password, int max_length)
    {
        std::string charset = "abcdefghijklmnopqrstuvwxyz";
        // This is a simplified search for demonstration.
        long long count = 0;
        std::cout << "Starting brute-force search..." << std::endl;
        for (long long i = 0; i < 1000000000LL; ++i)
        {
            // Mock checking a combination
            if (i % 100000000 == 0)
            {
                std::cout << "Checked " << i << " combinations..." << std::endl;
            }
            if (std::to_string(i) == target_password)
            {
                return target_password;
            }
        }
        return "Password not found.";
    }

    // Task 13: Calculates a large Mandelbrot set.
    static int mandelbrot_iterations(double real, double imag, int max_iterations)
    {
        double z_real = 0.0;
        double z_imag = 0.0;
        int iterations = 0;
        while (z_real * z_real + z_imag * z_imag < 4.0 && iterations < max_iterations)
        {
            double temp_real = z_real * z_real - z_imag * z_imag + real;
            z_imag = 2.0 * z_real * z_imag + imag;
            z_real = temp_real;
            iterations++;
        }
        return iterations;
    }

    // Task 14: Simulates a cryptographic hash calculation with high difficulty.
    static std::string find_cryptographic_nonce(const std::string& data, int difficulty)
    {
        std::string nonce = "00000000000000000000000000000000"; // Mock hash
        // Simulate a long search for a valid nonce.
        for (long long i = 0; i < 500000000LL; ++i)
        {
            // Mock work
            if (i % 50000000 == 0)
            {
                std::cout << "Cryptographic search progress: " << i / 50000000.0 * 100 << "%" << std::endl;
            }
        }
        return nonce;
    }

    // Task 15: Performs large matrix multiplication.
    static std::vector<std::vector<int>> multiply_matrices(const std::vector<std::vector<int>>& A,
                                                           const std::vector<std::vector<int>>& B)
    {
        if (A.empty() || A[0].size() != B.size())
        {
            return {};
        }
        size_t rows_A = A.size();
        size_t cols_A = A[0].size();
        size_t cols_B = B[0].size();

        std::vector<std::vector<int>> result(rows_A, std::vector<int>(cols_B, 0));

        std::cout << "Starting large matrix multiplication..." << std::endl;

        for (size_t i = 0; i < rows_A; ++i)
        {
            for (size_t j = 0; j < cols_B; ++j)
            {
                for (size_t k = 0; k < cols_A; ++k)
                {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        std::cout << "Matrix multiplication complete." << std::endl;
        return result;
    }
};