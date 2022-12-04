# Stable Diffusion NCNN

**This is a public fork from [EdVince/Stable-Diffusion-NCNN](https://github.com/EdVince/Stable-Diffusion-NCNN)**.
All the credit goes to [EdVince](https://github.com/EdVince).
As I cannot push LFS object to a public fork, I make this repo standalone.

Features appended:
1. remove OpenCV dependency
2. reduce memory usage from 7 GB to 5.5 GB
3. enable 4X super resolution from [Real-ESRGAN](https://github.com/xinntao/Real-ESRGAN)


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

The C++ interface:

```cpp
void sd( std::string positive_prompt=std::string{}, std::string output_png_path=std::string{}, std::string negative_prompt=std::string{}, int step=30, int seed=42 );
```

The default parameters for the above interface can be found from [here](https://github.com/fengwang/Stable-Diffusion-NCNN/blob/56a00bb197dc66dc74ceb69334b09a3d184cbd72/src/stable_diffusion.cpp#L381) on.
Example usage can be found from file src/main.cpp.

## Build

This project only relies on [ncnn](https://github.com/Tencent/ncnn). If **ncnn** has been installed on your system, you can safely execute `make` to build this project. For Archlinux users, [ncnn-git](https://aur.archlinux.org/packages/ncnn-git) package from AUR is sufficient. For others, please install it manually.

```bash
git clone https://github.com/fengwang/Stable-Diffusion-NCNN.git
cd Stable-Diffusion-NCNN
make
./bin/stablencnn
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
1. integrate super-resolution model in the pipeline
2. provide a GUI
3. provide a python binding (?)


## 99 Examples

Generating using the default `positive_prompt` and default `negative_prompt` with different seed


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
### seed = 10

![10](./resources/result_10.png)
### seed = 11

![11](./resources/result_11.png)
### seed = 12

![12](./resources/result_12.png)
### seed = 13

![13](./resources/result_13.png)
### seed = 14

![14](./resources/result_14.png)
### seed = 15

![15](./resources/result_15.png)
### seed = 16

![16](./resources/result_16.png)
### seed = 17

![17](./resources/result_17.png)
### seed = 18

![18](./resources/result_18.png)
### seed = 19

![19](./resources/result_19.png)
### seed = 20

![20](./resources/result_20.png)
### seed = 21

![21](./resources/result_21.png)
### seed = 22

![22](./resources/result_22.png)
### seed = 23

![23](./resources/result_23.png)
### seed = 24

![24](./resources/result_24.png)
### seed = 25

![25](./resources/result_25.png)
### seed = 26

![26](./resources/result_26.png)
### seed = 27

![27](./resources/result_27.png)
### seed = 28

![28](./resources/result_28.png)
### seed = 29

![29](./resources/result_29.png)
### seed = 30

![30](./resources/result_30.png)
### seed = 31

![31](./resources/result_31.png)
### seed = 32

![32](./resources/result_32.png)
### seed = 33

![33](./resources/result_33.png)
### seed = 34

![34](./resources/result_34.png)
### seed = 35

![35](./resources/result_35.png)
### seed = 36

![36](./resources/result_36.png)
### seed = 37

![37](./resources/result_37.png)
### seed = 38

![38](./resources/result_38.png)
### seed = 39

![39](./resources/result_39.png)
### seed = 40

![40](./resources/result_40.png)
### seed = 41

![41](./resources/result_41.png)
### seed = 42

![42](./resources/result_42.png)
### seed = 43

![43](./resources/result_43.png)
### seed = 44

![44](./resources/result_44.png)
### seed = 45

![45](./resources/result_45.png)
### seed = 46

![46](./resources/result_46.png)
### seed = 47

![47](./resources/result_47.png)
### seed = 48

![48](./resources/result_48.png)
### seed = 49

![49](./resources/result_49.png)
### seed = 50

![50](./resources/result_50.png)
### seed = 51

![51](./resources/result_51.png)
### seed = 52

![52](./resources/result_52.png)
### seed = 53

![53](./resources/result_53.png)
### seed = 54

![54](./resources/result_54.png)
### seed = 55

![55](./resources/result_55.png)
### seed = 56

![56](./resources/result_56.png)
### seed = 57

![57](./resources/result_57.png)
### seed = 58

![58](./resources/result_58.png)
### seed = 59

![59](./resources/result_59.png)
### seed = 60

![60](./resources/result_60.png)
### seed = 61

![61](./resources/result_61.png)
### seed = 62

![62](./resources/result_62.png)
### seed = 63

![63](./resources/result_63.png)
### seed = 64

![64](./resources/result_64.png)
### seed = 65

![65](./resources/result_65.png)
### seed = 66

![66](./resources/result_66.png)
### seed = 67

![67](./resources/result_67.png)
### seed = 68

![68](./resources/result_68.png)
### seed = 69

![69](./resources/result_69.png)
### seed = 70

![70](./resources/result_70.png)
### seed = 71

![71](./resources/result_71.png)
### seed = 72

![72](./resources/result_72.png)
### seed = 73

![73](./resources/result_73.png)
### seed = 74

![74](./resources/result_74.png)
### seed = 75

![75](./resources/result_75.png)
### seed = 76

![76](./resources/result_76.png)
### seed = 77

![77](./resources/result_77.png)
### seed = 78

![78](./resources/result_78.png)
### seed = 79

![79](./resources/result_79.png)
### seed = 80

![80](./resources/result_80.png)
### seed = 81

![81](./resources/result_81.png)
### seed = 82

![82](./resources/result_82.png)
### seed = 83

![83](./resources/result_83.png)
### seed = 84

![84](./resources/result_84.png)
### seed = 85

![85](./resources/result_85.png)
### seed = 86

![86](./resources/result_86.png)
### seed = 87

![87](./resources/result_87.png)
### seed = 88

![88](./resources/result_88.png)
### seed = 89

![89](./resources/result_89.png)
### seed = 90

![90](./resources/result_90.png)
### seed = 91

![91](./resources/result_91.png)
### seed = 92

![92](./resources/result_92.png)
### seed = 93

![93](./resources/result_93.png)
### seed = 94

![94](./resources/result_94.png)
### seed = 95

![95](./resources/result_95.png)
### seed = 96

![96](./resources/result_96.png)
### seed = 97

![97](./resources/result_97.png)
### seed = 98

![98](./resources/result_98.png)
### seed = 99

![99](./resources/result_99.png)
