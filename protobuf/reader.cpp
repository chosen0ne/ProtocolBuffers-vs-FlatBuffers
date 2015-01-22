/**
 * 
 * @file    reader
 * @author  chosen0ne(louzhenlin86@126.com)
 * @date    2015/01/19 17:51:36
 */

#include "protos/Sample.pb.h"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd, size;
    char buf[1024];

    fd = open("buf", O_RDONLY);
    if (fd == -1) {
        std::cout << "failed to open" << std::endl;
        return -1;
    }


    while (true) {
        int rlen = read(fd, &size, sizeof(size));
        if (rlen == -1) {
            std::cout << "failed to read" << std::endl;
            return -1;
        } else if (rlen == 0) {
            std::cout << "fin" << std::endl;
            break;
        }

        rlen = read(fd, buf, size);
        if (rlen == -1) {
            std::cout << "failed to read" << std::endl;
            return -1;
        }

        Sample::Sample sample;
        if (!sample.ParseFromArray(buf, size)) {
            std::cout << "failed to parse" << std::endl;
            return -1;
        }

        //std::cout << "sample=id:" << sample.id() << ", name:"
            //<< sample.name().c_str() << ", ip:" << sample.ip()
            //<< ", addr size:" << sample.addr_list_size() << std::endl;
    }

    return 0;
}
