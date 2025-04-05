# Multi-Layer Perceptron (MLP) from Scratch

## Objective

This project aims to enhance my skills in **C++**, **GPU programming**, and **deep learning** by implementing a **Multi-Layer Perceptron (MLP)** from scratch. The goal is to gain a deeper understanding of how MLPs work and to develop an extendable architecture that could later be integrated into a **Convolutional Neural Network (CNN)**.

## Approach

- **MLP Implementation**: Develop a fully customizable MLP in C++.
- **Dataset**: Use the **MNIST** dataset for evaluation, as it is widely known and provides a solid benchmark.
- **Comparison**: Train an equivalent MLP using **TensorFlow** in Python to compare performance and accuracy.

## Future Enhancements

- Extend the MLP for **CNN** integration.
- Develop **GPU-based matrix multiplication** for improved performance with larger datasets.
- Explore different **activation functions** and **training techniques**.

## Why This Project?

- **Deepen understanding** of neural networks at a fundamental level.
- Improve **C++** and **GPU programming** proficiency.
- Build a foundation for more complex deep learning architectures.

## Results

- **MY_MLP**: 94.95% accuracy
- **TensorFlow MLP**: 97.9% accuracy

## Getting Started

### Prerequisites

Make sure you have the following installed:

- **C++ compiler** (e.g., `g++`)
- **CMake** (for building the project)

### Installation

1. **Clone the repository**:

   ```bash
   git clone git@github.com:LPierre0/MY_MLP.git
   cd my_mlp
    ```

2. **Build the project**
    ```
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the program**
    ```
    ./neural
    ```

4. **Comparaison with tensorflow**

Check the MLP.ipynb file store in src/notebooks