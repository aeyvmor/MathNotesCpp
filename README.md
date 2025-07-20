# AI Math Notes (C++ Edition)

## 📖 Overview

This is a smart digital math notebook, inspired by Apple's Math Notes. It lets you handwrite math equations on a canvas, and then uses an AI to recognize and solve them in real-time.

This application is built with C++ and the Qt 6 framework for the user interface. It uses Google's Gemini AI to understand the handwriting and provide the answers.

**This project is a work in progress.**

## ✨ Features

*   **Handwritten Equation Recognition**: Draw equations with your mouse.
*   **Real-time AI Solving**: Get answers to your equations instantly.
*   **Handwritten-Style Answers**: The result is displayed in a font that matches the handwritten feel.
*   **Basic Controls**: Undo and Clear the canvas.

## 🛠️ Tech Stack

*   **Language**: C++
*   **GUI Framework**: Qt 6
*   **AI Model**: Google Gemini 2.5 Pro
*   **Build System**: CMake

## 🚀 Getting Started

### Prerequisites

*   A C++ compiler (like MinGW on Windows)
*   CMake
*   Qt 6 SDK
*   A Google Gemini API Key

### Building the Project

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/MathNotesCpp.git
    cd MathNotesCpp
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake to configure the project:**
    *   Replace `C:\path\to\Qt6` with the path to your Qt 6 installation.
    ```bash
    cmake .. -DCMAKE_PREFIX_PATH=C:\path\to\Qt6
    ```

4.  **Compile the code:**
    ```bash
    cmake --build .
    ```

### Running the Application

1.  **Set your API Key:**
    *   You need to set an environment variable with your Gemini API key.
    *   **On Windows (PowerShell):** `$env:GEMINI_API_KEY="YOUR_API_KEY_HERE"`

2.  **Run the executable:**
    *   You can find `MathNotesCpp.exe` inside the `build` directory.

## 🔮 Future Features

Here are some ideas for future improvements:

*   **Save and Load**: Save your notes to a file and open them later.
*   **LaTeX Export**: Convert your handwritten equations into LaTeX code.
*   **Graph Plotting**: Automatically plot the graphs of any functions you write.
*   **Web Version**: Compile the app to WebAssembly to run it in a browser.

## 🙏 Acknowledgements

*   This project was inspired by the original Python version created by **Ayush Pai**.
*   The handwritten font is "Caveat" from Google Fonts.
