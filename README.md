# Image Processing Library

A C++ library for basic image processing and geometric shape rendering.

## 📚 Documentation
You can find the full API documentation, generated with Doxygen, at the link below:

👉 **[View Online Documentation](https://<username>.github.io/<nume-proiect>/html/index.html)**

---

## 🛠 Project Structure
* `main.cpp` - Entry point demonstrating the library's usage.
* `classes/` - Core library source files and headers.
    * `Image.h/.cpp` - Main image class.
    * `ImageProcessing.h/.cpp` - Filters (Gamma, Convolution, etc.).
    * `Drawing.h/.cpp` - Shape rendering module.
    * `Point.h`, `Size.h`, `Rectangle.h` - Geometric primitives.
* `docs/` - Auto-generated Doxygen documentation.

## 🚀 Getting Started
### Prerequisites
* C++ Compiler (GCC/Clang)
* Doxygen (for generating documentation)

### Compilation
To compile the project with all classes, run:
```bash
g++ main.cpp classes/*.cpp -o image_proc