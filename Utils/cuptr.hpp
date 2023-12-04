#pragma once

#include "helper_cuda.h"
#include "cuda_runtime.h"
#include "hostptr.hpp"
#include <iostream>


using namespace std;

template <typename T>
class CuPtr{
public:
    CuPtr(): m_Size(0), m_Ptr(nullptr){}
    CuPtr(size_t size, bool bZeroInit=true){
        m_Size = size;
        m_Bytes = size * sizeof(T);
        checkCudaErrors(cudaMalloc(&m_Ptr, m_Bytes));
        if(bZeroInit){
            checkCudaErrors(cudaMemset(m_Ptr, 0, m_Bytes));
        }
    }
    CuPtr(const T *p, size_t size){
        m_Size = size;
        m_Bytes = size * sizeof(T);
        checkCudaErrors(cudaMalloc(&m_Ptr, m_Bytes));
        checkCudaErrors(cudaMemcpy(m_Ptr, p, m_Bytes, cudaMemcpyHostToDevice));
    }
    CuPtr(HostPtr<T>& hp){
        m_Size = hp.getSize();
        m_Bytes = m_Size * sizeof(T);
        checkCudaErrors(cudaMalloc(&m_Ptr, m_Bytes));
        checkCudaErrors(cudaMemcpy(m_Ptr, hp, m_Bytes, cudaMemcpyHostToDevice));
    }
    void Reset(HostPtr<T>& hp){
        if(m_Size > 0){
            checkCudaErrors(cudaFree(m_Ptr));
            m_Ptr = 0;
        }
        m_Size = hp.getSize();
        m_Bytes = m_Size * sizeof(T);
        checkCudaErrors(cudaMalloc(&m_Ptr, m_Bytes));
        checkCudaErrors(cudaMemcpy(m_Ptr, hp, m_Bytes, cudaMemcpyHostToDevice));
    }
    void SetZeros(){
        if(m_Size > 0){
             checkCudaErrors(cudaMemset(m_Ptr, 0, m_Bytes));
        }
        else{
            std::cerr << "ERR! CuPtr::SetZeros() called by uninitiallized pointer!!!" << std::endl;
        }
    }
    void ToHostPtr(HostPtr<T>& hp) const{
        hp.Resize(m_Size);
        checkCudaErrors(cudaMemcpy(hp.GetPtr(), m_Ptr, m_Bytes, cudaMemcpyDeviceToHost));
    }
    T* GetPtr(){
        return m_Ptr;
    }
    const T* GetPtrConst() const{
        return (const T*)m_Ptr;
    }
    ~CuPtr(){
        if(m_Size > 0){
            checkCudaErrors(cudaFree(m_Ptr));
            m_Ptr = 0;
        }
    }

private:
    T *m_Ptr;
    size_t m_Size;      // number of eles, not bytes
    size_t m_Bytes;     // num of bytes
};