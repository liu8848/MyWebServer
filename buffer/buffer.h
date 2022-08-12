#ifndef BUFFER_H
#define BUFFER_H

#include<cstring>
#include<iostream>
#include<unistd.h>
#include<sys/uio.h>
#include<vector>
#include<atomic>
#include<assert.h>

class Buffer
{
public:
    Buffer(int initBuffSize=1024);
    ~Buffer()=default;

    size_t WriteableBytes() const;      //当前还可写的缓冲区字节数
    size_t ReadableBytes() const;       //当前可读的缓冲区字节数
    size_t PrependableBytes() const;    //当前已读取位置

    const char* Peek() const;           //当前读取到的字符
    void EnureWriteable(size_t len);    //确保缓冲区有足够长度供写，不足则分配新空间
    void HasWritten(size_t len);

    void Retrieve(size_t len);          //更新已读取位置
    void RetrieveUntil(const char*end);

    void RetrieveAll();
    std::string RetrieveAllToStr();

    const char*BeginWriteConst() const;
    char*BeginWrite();                  //返回可开始写的位置

    void Append(const std::string&str);
    void Append(const char*str,size_t len);
    void Append(const void*data,size_t len);
    void Append(const Buffer&buff);

    ssize_t ReadFd(int fd,int*Errno);
    ssize_t WriteFd(int fd,int*Errno);

private:
    char*BeginPtr_();
    const char*BeginPtr_() const;
    void MakeSpace_(size_t len);        

    std::vector<char> buffer_;
    std::atomic<std::size_t> readPos_;
    std::atomic<std::size_t> writePos_;
};


#endif