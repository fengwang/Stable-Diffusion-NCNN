#ifndef FNBXWWCFGKJITOKYXRMKNCJASNTJMUSUVRVIVADDNNHPXPCEVEYRYVBKQJBNABBDVUBDPUWTU
#define FNBXWWCFGKJITOKYXRMKNCJASNTJMUSUVRVIVADDNNHPXPCEVEYRYVBKQJBNABBDVUBDPUWTU

#include <ncnn/net.h>

struct Esr4x
{
    ncnn::Net net;

    Esr4x()
    {
        net.opt.use_vulkan_compute = false;
        net.opt.use_winograd_convolution = false;
        net.opt.use_sgemm_convolution = false;
        net.opt.use_fp16_packed = false;
        net.opt.use_fp16_storage = false;
        net.opt.use_fp16_arithmetic = false;
        net.opt.use_packing_layout = true;
        net.load_param( "assets/RealESRGAN_x4plus_anime_6B.fp32-sim-sim-opt.param" );
        net.load_model( "assets/RealESRGAN_x4plus_anime_6B.fp32-sim-sim-opt.bin" );
    }

    ncnn::Mat inference( ncnn::Mat& input )
    {
        ncnn::Extractor ex = net.create_extractor();
        ex.set_light_mode( true );
        {
            constexpr float mean[] = {0.0f, 0.0f, 0.0f};
            constexpr float norm[] = {1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f};
            input.substract_mean_normalize( mean, norm );
        }
        ex.input( "data", input );
        ncnn::Mat ans;
        ex.extract( "output", ans );
        {
            constexpr float mean[] = {0.0f, 0.0f, 0.0f};
            constexpr float norm[] = {255.0f, 255.0f, 255.0f};
            ans.substract_mean_normalize( mean, norm );
        }
        return ans;
    }

}; // struct Esr4x

#endif//FNBXWWCFGKJITOKYXRMKNCJASNTJMUSUVRVIVADDNNHPXPCEVEYRYVBKQJBNABBDVUBDPUWTU

