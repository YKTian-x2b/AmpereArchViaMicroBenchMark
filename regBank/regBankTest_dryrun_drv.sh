fatbinary -64 --cicc-cmdline="-ftz=0 -prec_div=1 -prec_sqrt=1 -fmad=1 " "--image3=kind=elf,sm=86,file=regBankTest.sm_86.cubin" "--image3=kind=ptx,sm=86,file=regBankTest.ptx" --embedded-fatbin="regBankTest.fatbin.c" 
rm regBankTest.fatbin
gcc -D__CUDA_ARCH__=860 -D__CUDA_ARCH_LIST__=860 -c -x c++  -DCUDA_DOUBLE_MATH_FUNCTIONS -I"/opt/kaiProjects/GEMM_kai/Utils" "-I/usr/local/cuda-12.1/bin/../targets/x86_64-linux/include"   -m64 "regBankTest.cudafe1.cpp" -o "regBankTest.o" 
nvlink -m64 --arch=sm_86 --register-link-binaries="regBankTest_dlink.reg.c"  -L"/usr/local/cuda/lib64" -lcuda   "-L/usr/local/cuda-12.1/bin/../targets/x86_64-linux/lib/stubs" "-L/usr/local/cuda-12.1/bin/../targets/x86_64-linux/lib" -cpu-arch=X86_64 "regBankTest.o"  -lcudadevrt  -o "regBankTest_dlink.sm_86.cubin" --host-ccbin "gcc"
fatbinary -64 --cicc-cmdline="-ftz=0 -prec_div=1 -prec_sqrt=1 -fmad=1 " -link "--image3=kind=elf,sm=86,file=regBankTest_dlink.sm_86.cubin" --embedded-fatbin="regBankTest_dlink.fatbin.c" 
rm regBankTest_dlink.fatbin
gcc -D__CUDA_ARCH_LIST__=860 -c -x c++ -DFATBINFILE="\"regBankTest_dlink.fatbin.c\"" -DREGISTERLINKBINARYFILE="\"regBankTest_dlink.reg.c\"" -I. -D__NV_EXTRA_INITIALIZATION= -D__NV_EXTRA_FINALIZATION= -D__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__  -I"/opt/kaiProjects/GEMM_kai/Utils" "-I/usr/local/cuda-12.1/bin/../targets/x86_64-linux/include"    -D__CUDACC_VER_MAJOR__=12 -D__CUDACC_VER_MINOR__=1 -D__CUDACC_VER_BUILD__=105 -D__CUDA_API_VER_MAJOR__=12 -D__CUDA_API_VER_MINOR__=1 -D__NVCC_DIAG_PRAGMA_SUPPORT__=1 -m64 "/usr/local/cuda-12.1/bin/crt/link.stub" -o "regBankTest_dlink.o" 
g++ -D__CUDA_ARCH_LIST__=860 -m64 -Wl,--start-group "regBankTest_dlink.o" "regBankTest.o" -L"/usr/local/cuda/lib64" -lcuda   "-L/usr/local/cuda-12.1/bin/../targets/x86_64-linux/lib/stubs" "-L/usr/local/cuda-12.1/bin/../targets/x86_64-linux/lib"  -lcudadevrt  -lcudart_static  -lrt -lpthread  -ldl  -Wl,--end-group -o "res/regBankTest" 
