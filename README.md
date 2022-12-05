# Stable Diffusion NCNN

**This is a public fork from [EdVince/Stable-Diffusion-NCNN](https://github.com/EdVince/Stable-Diffusion-NCNN)**.
All the credit goes to [EdVince](https://github.com/EdVince).
As I cannot push LFS object to a public fork, I make this repo standalone.

Features appended:
1. remove OpenCV dependency
2. reduce memory usage from 7 GB to 5.5 GB
3. enable 4X super resolution from [Real-ESRGAN](https://github.com/xinntao/Real-ESRGAN)
4. header-only


## Quick introduction
1. Checkout the [readme from EdVince's repo](https://github.com/EdVince/Stable-Diffusion-NCNN/blob/main/README.md) for implementation details.
2. Download and extract the assets from the replease of this repo, the layout should looks like:

```
YOUREXECUTABLE
assets
├── AutoencoderKL-fp16.bin
├── AutoencoderKL-fp16.param
├── FrozenCLIPEmbedder-fp16.bin
├── FrozenCLIPEmbedder-fp16.param
├── log_sigmas.bin
├── RealESRGAN_x4plus_anime_6B.fp32-sim-sim-opt.bin
├── RealESRGAN_x4plus_anime_6B.fp32-sim-sim-opt.param
├── UNetModel-fp16.bin
├── UNetModel-fp16.param
└── vocab.txt
```

## Example usage:

Copy `stable_diffusion.hpp` and the downloaded `assets` to your working directory, and the C++ interface is:

```cpp
inline void stable_diffusion( std::string positive_prompt = std::string{}, std::string output_png_path = std::string{}, int step = 30, int seed = 42, std::string negative_prompt = std::string{} )
```

**Example usage**

Source code:

```cpp
// test.cpp
#include "./stable_diffusion.hpp"
#include <string>

int main ()
{
    std::string positive_prompt = "floating hair, portrait, ((loli)), ((one girl)), cute face, hidden hands, asymmetrical bangs, beautiful detailed eyes, eye shadow, hair ornament, ribbons, bowties, buttons, pleated skirt, (((masterpiece))), ((best quality)), colorful";
    std::string output_png_path = "./output.png";
    stable_diffusion( std::string positive_prompt, std::string output_png_path );
    return 0;
}
```

Compile and link command
```bash
g++ -o test test.cpp -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra `pkg-config --cflags --libs opencv4` -lncnn -lstdc++ -pthread -Wl,--gc-sections -flto -fopt-info-vec-optimized
```


## Build

This project only relies on [ncnn](https://github.com/Tencent/ncnn). For Archlinux users, [ncnn-git](https://aur.archlinux.org/packages/ncnn-git) package from AUR is sufficient. For others, please install it manually.

Example usage:
```bash
git clone https://github.com/fengwang/Stable-Diffusion-NCNN.git
cd Stable-Diffusion-NCNN
g++ -o test test.cpp -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra `pkg-config --cflags --libs opencv4` -lncnn -lstdc++ -pthread -Wl,--gc-sections -flto -fopt-info-vec-optimized
```

However, you need **5.5 GB** memory to run.


### Linking to NCNN

If **ncnn** is not installed in the standard paths (such as `/usr/include/ncnn` and `/usr/lib/libncnn.so`, please update the makefile to comply. For example:

Update CXXFLAGS

```
#CXXFLAGS := -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra
CXXFLAGS := -funsafe-math-optimizations -Ofast -flto=auto  -funroll-all-loops -pipe -march=native -std=c++20 -Wall -Wextra `pkg-config --cflags ncnn`
```

Update LFLAGS:

```
#LFLAGS := -lncnn -lstdc++ -pthread -Wl,--gc-sections -flto -fopt-info-vec-optimized
LFLAGS := `pkg-config --libs ncnn` -lstdc++ -pthread -Wl,--gc-sections -flto -fopt-info-vec-optimized
```


## TODO
1. provide a GUI
2. provide a python binding (?)


## 9 Examples

Generating using the default `positive_prompt` and default `negative_prompt` with different seed in 20 steps


### seed = 1

![1](./resources/result_1.png)
### seed = 2

![2](./resources/result_2.png)
### seed = 3

![3](./resources/result_3.png)
### seed = 4

![4](./resources/result_4.png)
### seed = 5

![5](./resources/result_5.png)
### seed = 6

![6](./resources/result_6.png)
### seed = 7

![7](./resources/result_7.png)
### seed = 8

![8](./resources/result_8.png)
### seed = 9

![9](./resources/result_9.png)
