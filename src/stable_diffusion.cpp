#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <map>
#include <cmath>
#include <ncnn/net.h>
#include "./prompt_slover.h"
#include "./decoder_slover.h"
#include "./diffusion_slover.h"
#include "./esr4x.hpp"
#include "./save_png.hpp"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cstdint>
#include <numeric>
#include <cstdio>


void sd( std::string positive_prompt = std::string{}, std::string output_png_path = std::string{}, std::string negative_prompt = std::string{}, int step = 30, int seed = 42 )
{
    if ( positive_prompt.empty() )
        positive_prompt =
            "floating hair, portrait, ((loli)), ((one girl)), cute face, hidden hands, asymmetrical bangs, beautiful detailed eyes, eye shaw, hair ornament, ribbons, bowties, buttons, pleated skirt, (((masterpiece))), ((best quality)), colorful";

    if ( negative_prompt.empty() )
        negative_prompt =
            "sleeveless, amputeebad feetbad handsbad duplicate, bad anatomy, bad anatomy disfigured malformed mutated, bad feet, bad hands, bad legs, blurry, bodysuit, cloned face, cropped, deformed, disfigured, dismemberment, error, extra arms, extra digit, extra digits, extra feet, extra fingers, extra legs, extra limbs, fewer digits, full, fused fingers, futa, gross proportions, hermaphrodite, jpeg artifacts, latex, leather, long body, long neck, low quality, lowres, malformed hands, malformed limbs, missing arms, missing fingers, missing legs, morbid, mutated hands, mutated hands and fingers, mutilated, normal quality, ((nsfw)), out of frame,  signature, text, text font ui, too many fingers, trannsexual, trans, ugly, username, watermark, worst quality, yaoi, wall, or, bed, desk, tail, butt_plug, zettai_ryouiki, thick_thighs, wide_hips, thick_thighs, (((skirt_lift))), undressing, naked, nude, tattoo, sofa, on_sofa, chair, on_chair,multiple breasts, (((mutated hands and fingers))), ((long body)), (((mutation, poorly drawn))) , black-white, bad anatomy, liquid body, liquid tongue, disfigured, malformed, mutated, anatomical nonsense, text font ui, error, malformed hands, long neck, blurred, lowers, lowres, bad anatomy, bad proportions, bad shaw, uncoordinated body, unnatural body, fused breasts, bad breasts, huge breasts, poorly drawn breasts, extra breasts, liquid breasts, heavy breasts, missing breasts, huge haunch, huge thighs, huge calf, bad hands, fused hand, missing hand, disappearing arms, disappearing thigh, disappearing calf, disappearing legs, fused ears, bad ears, poorly drawn ears, extra ears, liquid ears, heavy ears, missing ears, fused animal ears, bad animal ears, poorly drawn animal ears, extra animal ears, liquid animal ears, heavy animal ears, missing animal ears, text, ui, error, missing fingers, missing limb, fused fingers, one hand with more than 5 fingers, one hand with less than 5 fingers, one hand with more than 5 digit, one hand with less than 5 digit, extra digit, fewer digits, fused digit, missing digit, bad digit, liquid digit, colorful tongue, black tongue, cropped, watermark, username, blurry, JPEG artifacts, signature, 3D, 3D game, 3D game scene, 3D character, malformed feet, extra feet, bad feet, poorly drawn feet, fused feet, missing feet, extra shoes, bad shoes, fused shoes, more than two shoes, poorly drawn shoes, bad gloves, poorly drawn gloves, fused gloves, bad cum, poorly drawn cum, fused cum, bad hairs, poorly drawn hairs, fused hairs, big muscles, ugly, bad face, fused face, poorly drawn face, cloned face, big face, long face, bad eyes, fused eyes poorly drawn eyes, extra eyes, malformed limbs, more than 2 nipples, missing nipples, different nipples, fused nipples, bad nipples, poorly drawn nipples, black nipples, colorful nipples, gross proportions. short arm, (((((missing arms))))), missing thighs, missing calf, missing legs, mutation, duplicate, morbid, mutilated, poorly drawn hands, more than 1 left hand, more than 1 right hand, deformed, (blurry), disfigured, missing legs, extra arms, extra thighs, more than 2 thighs, extra calf, fused calf, extra legs, bad knee, extra knee, more than 2 legs, bad tails, bad mouth, fused mouth, poorly drawn mouth, bad tongue, tongue within mouth, too long tongue, black tongue, big mouth, cracked mouth, bad mouth, dirty face, dirty teeth, dirty pantie, fused pantie, poorly drawn pantie, fused cloth, poorly drawn cloth, bad pantie, yellow teeth, thick lips, bad cameltoe, colorful cameltoe, bad asshole, poorly drawn asshole, fused asshole, missing asshole, bad anus, bad pussy, bad crotch, bad crotch seam, fused anus, fused pussy, fused anus, fused crotch, poorly drawn crotch, fused seam, poorly drawn anus, poorly drawn pussy, poorly drawn crotch, poorly drawn crotch seam, bad thigh gap, missing thigh gap, fused thigh gap, liquid thigh gap, poorly drawn thigh gap, poorly drawn anus, bad collarbone, fused collarbone, missing collarbone, liquid collarbone, strong girl, obesity, worst quality, low quality, normal quality, liquid tentacles, bad tentacles, poorly drawn tentacles, split tentacles, fused tentacles, missing clit, bad clit, fused clit, colorful clit, black clit, liquid clit, QR code, bar code, censored, safety panties, safety knickers, beard, furry ,pony, pubic hair, mosaic, excrement, faeces, shit, futa, testis, shoes, glasses, ((((eyewear))))";

    if ( output_png_path.empty() )
        output_png_path = std::string{"./result_"} + std::to_string( step ) + std::string{"_"} + std::to_string( seed ) + std::string{".png"};
    std::cout << "----------------[start]------------------" << std::endl;
    std::cout << "positive_prompt: " << positive_prompt << std::endl;
    std::cout << "output_png_path: " << output_png_path << std::endl;
    std::cout << "negative_prompt: " << negative_prompt << std::endl;
    std::cout << "step: " << step << std::endl;
    std::cout << "seed: " << seed << std::endl;
    std::cout << "----------------[prompt]------------------" << std::endl;
    ncnn::Mat cond;
    ncnn::Mat uncond;
    {
        PromptSlover prompt_slover;
        cond = prompt_slover.get_conditioning( positive_prompt );
        uncond = prompt_slover.get_conditioning( negative_prompt );
    }
    std::cout << "----------------[diffusion]---------------" << std::endl;
    ncnn::Mat sample;
    {
        DiffusionSlover diffusion_slover;
        sample = diffusion_slover.sampler( seed, step, cond, uncond );
    }
    std::cout << "----------------[decode]------------------" << std::endl;
    ncnn::Mat x_samples_ddim;
    {
        DecodeSlover decode_slover;
        x_samples_ddim = decode_slover.decode( sample );
    }
    std::cout << "----------------[4x]--------------------" << std::endl;
    {
        Esr4x esr4x;
        x_samples_ddim = esr4x.inference( x_samples_ddim );
    }
    std::cout << "----------------[save]--------------------" << std::endl;
    {
        std::vector<std::uint8_t> buffer;
        //buffer.resize( 512 * 512 * 3 );
        buffer.resize( 4*512 * 4*512 * 3 );
        x_samples_ddim.to_pixels( buffer.data(), ncnn::Mat::PIXEL_RGB );
        save_png( buffer.data(), 4*512, 4*512, 0, output_png_path.c_str() );
    }
    std::cout << "----------------[close]-------------------" << std::endl;
}

